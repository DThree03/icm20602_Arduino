#ifndef	_ICM_20602_H_
#define _ICM_20602_H_

#include "config/register.h"
#include "Arduino.h"
#include <Wire.h>

typedef void (*voidFuncPtr)(void);

class icm20602
{
	public:
		icm20602_dev  default_mode;
		unsigned char I2CAddress;
		float temp;
		
		icm20602(unsigned char ad0pinvalue);
		int begin(void);
		void enable_Interrupt(int pin, voidFuncPtr handler, int modex, unsigned char sentitive);
		bool icm20602_read_accel(float *p_x, float *p_y, float *p_z);
		bool icm20602_read_gyro(float *p_x, float *p_y, float *p_z);
		unsigned char getIntStatus(void);
		float getTemp(void);
		//void update(void);
	private:
		void getdefaulSetup(void);
		void ChipReset(void);
		float get_accel_sensitivity(icm20602_accel_g accel_g);
		float get_gyro_sensitivity(icm20602_gyro_dps gyro_dps);
		void i2c_write_byte(unsigned char reg, unsigned char dataz);
		unsigned char i2c_read_byte(unsigned char reg);
		void i2c_read_buffer(unsigned char reg, unsigned char *buff, unsigned char lenght);
		
};

#endif