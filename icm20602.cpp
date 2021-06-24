/*
	ICM20602 Arduino Library for Arduino or ESP module.
	Author: DThree03
*/

/*
  TODO:
  - Switch and config MODE: Sleep mode,...
  - Read data use FIFO
  - 
  - 
*/

#include "icm20602.h"

void icm20602::getdefaulSetup(void)
{
   default_mode.accel_dlpf = ICM20602_ACCEL_DLPF_BYPASS_1046_HZ;
   default_mode.accel_g = ICM20602_ACCEL_RANGE_2G;
   default_mode.gyro_dlpf = ICM20602_GYRO_DLPF_20_HZ;
   default_mode.gyro_dps = ICM20602_GYRO_RANGE_500_DPS;
}
float icm20602::get_accel_sensitivity(icm20602_accel_g accel_g)
{
	float f = 0.0;

	switch (accel_g) {
		case (ICM20602_ACCEL_RANGE_2G):
			f = 16384.0;
			break;
		case (ICM20602_ACCEL_RANGE_4G):
			f = 8192.0;
			break;
		case (ICM20602_ACCEL_RANGE_8G):
			f = 4096.0;
			break;
		case (ICM20602_ACCEL_RANGE_16G):
			f = 2048.0;
			break;
	}
  return f;
}
float icm20602::get_gyro_sensitivity(icm20602_gyro_dps gyro_dps)
{
	float f = 0;

	switch (gyro_dps) {
		case (ICM20602_GYRO_RANGE_250_DPS):
			f = 131.0;
			break;
		case (ICM20602_GYRO_RANGE_500_DPS):
			f = 65.5;
			break;
		case (ICM20602_GYRO_RANGE_1000_DPS):
			f = 32.8;
			break;
		case (ICM20602_GYRO_RANGE_2000_DPS):
			f = 16.4;
			break;
	}
	return f;
}

icm20602::icm20602(unsigned char ad0pinvalue)
{
	I2CAddress = 0x68|ad0pinvalue;
}
/*
@Summary
	Config seting byte for device
@Description
 General Procedure:
	1. reset chip
	2. set clock for PLL for optimum performance as documented in datasheet
	3. place accelerometer and gyroscope into standby
	4. disable fifo
	5. configure chip
	6. enable accelerometer and gyroscope
@Preconditions
	The begin must be call in setup funtion
@Returns
	0: Chip communication error
	1: Chip config OK
@Param
	mode (unsigned char): running begin mode

@Example 
	icm20602 ACC;
	void setup(){
		ACC.begin();
		
	}	
*/
int icm20602::begin(void)
{
	Wire.begin();
	getdefaulSetup();
	if(i2c_read_byte(REG_WHO_AM_I)!=REG_WHO_AM_I_CONST){
		
		Serial.println("Chip communication error!");
		return 0;
	}
	//  1. reset chip
	ChipReset();
	//  2. set clock for PLL for optimum performance as documented in datasheet
	i2c_write_byte(REG_PWR_MGMT_1, 0x01);
	//  3. place accelerometer and gyroscope into standby
	i2c_write_byte(REG_PWR_MGMT_2, 0x3F);
	//  4. disable fifo
	i2c_write_byte(REG_USER_CTRL, 0x00);
	//  5. configure chip
		//Acc config
	if(default_mode.accel_dlpf == ICM20602_ACCEL_DLPF_BYPASS_1046_HZ){
		i2c_write_byte(REG_ACCEL_CONFIG_2, 0x09);
	}
	else{
		i2c_write_byte(REG_ACCEL_CONFIG_2, default_mode.accel_dlpf);
	}
	i2c_write_byte(REG_ACCEL_CONFIG, default_mode.accel_g<<3);
		//Gyro config
	if(default_mode.gyro_dlpf == ICM20602_GYRO_DLPF_BYPASS_3281_HZ){
		i2c_write_byte(REG_CONFIG, 0x00);
		i2c_write_byte(REG_GYRO_CONFIG, (default_mode.gyro_dps<<3)|0x02);
	}
	else if(default_mode.gyro_dlpf == ICM20602_GYRO_DLPF_BYPASS_8173_HZ){
		i2c_write_byte(REG_CONFIG, 0x00);
		i2c_write_byte(REG_GYRO_CONFIG, (default_mode.gyro_dps<<3)|0x01);
	}	
	else{
		i2c_write_byte(REG_CONFIG, default_mode.gyro_dlpf);
		i2c_write_byte(REG_GYRO_CONFIG, default_mode.gyro_dps<<3);
	}
		//Enable FIFO if request	for both acc 0x08 and gyro 0x10
		i2c_write_byte(REG_FIFO_EN, 0x18);
		//Set frequence of wakeup = 1kHz/(1 + SMPLRT_DIV) (3.9 - 500Hz)
		i2c_write_byte(REG_SMPLRT_DIV, 0x09);	//100Hz
		//Enable Acc 0x07 & gyro 0x38
		i2c_write_byte(REG_PWR_MGMT_2, 0x00);
	return 1;
}
void icm20602::enable_Interrupt(int pin, voidFuncPtr handler, int modex, unsigned char sentitive)
{
	regINT_PIN_CFG_t intval;
	intval.regByte = 0;
	if(modex == FALLING){
		pinMode(pin, INPUT_PULLUP);
		intval.bits.INT_LEVEL = 1;
		intval.bits.INT_OPEN  = 1;
	}
	else if(modex == RISING){
		pinMode(pin, INPUT_PULLDOWN);
	}
	attachInterrupt(pin, handler, modex);
	intval.bits.LATCH_INT_EN = 1;		//INT pin level held until interrupt status is cleared
	intval.bits.INT_RD_CLR  = 0;		//Interrupt status is cleared only by reading INT_STATUS register
	i2c_write_byte(REG_INT_PIN_CFG, intval.regByte);
	i2c_write_byte(REG_INT_ENABLE, 0xE0);
	i2c_write_byte(REG_ACCEL_INTEL_CTRL, 0xC0);
	
	i2c_write_byte(REG_ACCEL_WOM_X_THR, sentitive);
	i2c_write_byte(REG_ACCEL_WOM_Y_THR, sentitive);
	i2c_write_byte(REG_ACCEL_WOM_Z_THR, sentitive);
}
bool icm20602::icm20602_read_accel(float *p_x, float *p_y, float *p_z)
{
	float accel_sensitivity;
	unsigned int x, y, z;
	unsigned char buff[8] = {0};
	
	accel_sensitivity = get_accel_sensitivity(default_mode.accel_g);
	if(i2c_read_byte(REG_INT_STATUS)|0x01){
		i2c_read_buffer(REG_ACCEL_XOUT_H, buff, 8);
		x = (buff[0]<<8)|buff[1];
		y = (buff[2]<<8)|buff[3];
		z = (buff[4]<<8)|buff[5];
		temp = ((buff[4]<<8)|buff[5])/326.8 + 12;
		
		*p_x = ((float) x) / accel_sensitivity;
		*p_y = ((float) y) / accel_sensitivity;
		*p_z = ((float) z) / accel_sensitivity;
		return true;
	}
	return false;
	
}
bool icm20602::icm20602_read_gyro(float *p_x, float *p_y, float *p_z)
{
	float gyro_sensitivity;
	unsigned int x, y, z;
	unsigned char buff[6] = {0};
	
	gyro_sensitivity = get_gyro_sensitivity(default_mode.gyro_dps);
	if(i2c_read_byte(REG_INT_STATUS)|0x01){
		i2c_read_buffer(REG_GYRO_XOUT_H, buff, 6);
		x = (buff[0]<<8)|buff[1];
		y = (buff[2]<<8)|buff[3];
		z = (buff[4]<<8)|buff[5];
		
		*p_x = ((float) x) / gyro_sensitivity;
		*p_y = ((float) y) / gyro_sensitivity;
		*p_z = ((float) z) / gyro_sensitivity;
		return true;
	}
	return false;
}
unsigned char icm20602::getIntStatus(void)
{
	return i2c_read_byte(REG_INT_STATUS);
}
float icm20602::getTemp(void)
{
	return temp;
}
void icm20602::ChipReset(void)
{
	i2c_write_byte(REG_PWR_MGMT_1, CHIP_RESET_CONST);
	delay(1000);
}

/*
@Summary
	write a byte via I2C
@Description
	write a byte to a register

@Returns
	
@Param
	reg (unsigned char): register want to read data

@Example 
		
*/
void icm20602::i2c_write_byte(unsigned char reg, unsigned char dataz)
{
	Wire.beginTransmission(I2CAddress);
	Wire.write(reg); 
	Wire.write(dataz);
	Wire.endTransmission();
}
unsigned char icm20602::i2c_read_byte(unsigned char reg)
{
  unsigned char c;
  Wire.beginTransmission(I2CAddress);
  Wire.write(reg); 
  Wire.endTransmission();

  Wire.requestFrom(I2CAddress, (unsigned char)1);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    c = Wire.read(); // receive a byte as character
  }
  Wire.endTransmission();
  return c;
}
void icm20602::i2c_read_buffer(unsigned char reg, unsigned char *buff, unsigned char lenght){
  int i = 0;
  Wire.beginTransmission(I2CAddress);
  Wire.write(reg); 
  Wire.endTransmission();

  Wire.requestFrom(I2CAddress, lenght);    // request 6 bytes from slave device #8

  while (Wire.available()) {
    buff[i] = Wire.read(); 
    i++;
  }
  Wire.endTransmission();
}
