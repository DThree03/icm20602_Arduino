#define REG_XG_OFFS_TC_H 		0x04
#define REG_XG_OFFS_TC_L 		0x05
#define REG_YG_OFFS_TC_H 		0x07
#define REG_YG_OFFS_TC_L 		0x08
#define REG_ZG_OFFS_TC_H 		0x0A
#define REG_ZG_OFFS_TC_L 		0x0B
#define REG_SELF_TEST_X_ACCEL 	0x0D
#define REG_SELF_TEST_Y_ACCEL 	0x0E
#define REG_SELF_TEST_Z_ACCEL 	0x0F
#define REG_XG_OFFS_USRH 		0x13
#define REG_XG_OFFS_USRL 		0x14
#define REG_YG_OFFS_USRH 		0x15
#define REG_YG_OFFS_USRL 		0x16
#define REG_ZG_OFFS_USRH 		0x17
#define REG_ZG_OFFS_USRL 		0x18
#define REG_SMPLRT_DIV 			0x19
#define REG_CONFIG 				0x1A
#define REG_GYRO_CONFIG 		0x1B
#define REG_ACCEL_CONFIG 		0x1C
#define REG_ACCEL_CONFIG_2 		0x1D
#define REG_LP_MODE_CFG 		0x1E
#define REG_ACCEL_WOM_X_THR 	0x20
#define REG_ACCEL_WOM_Y_THR 	0x21
#define REG_ACCEL_WOM_Z_THR 	0x22
#define REG_FIFO_EN 			0x23
#define REG_FSYNC_INT 			0x36
#define REG_INT_PIN_CFG 		0x37
#define REG_INT_ENABLE 			0x38
#define REG_FIFO_WM_INT_STATUS 	0x39
#define REG_INT_STATUS 			0x3A
#define REG_ACCEL_XOUT_H 		0x3B
#define REG_ACCEL_XOUT_L 		0x3C
#define REG_ACCEL_YOUT_H 		0x3D
#define REG_ACCEL_YOUT_L 		0x3E
#define REG_ACCEL_ZOUT_H 		0x3F
#define REG_ACCEL_ZOUT_L 		0x40
#define REG_TEMP_OUT_H 			0x41
#define REG_TEMP_OUT_L 			0x42
#define REG_GYRO_XOUT_H 		0x43
#define REG_GYRO_XOUT_L 		0x44
#define REG_GYRO_YOUT_H 		0x45
#define REG_GYRO_YOUT_L 		0x46
#define REG_GYRO_ZOUT_H 		0x47
#define REG_GYRO_ZOUT_L 		0x48
#define REG_SELF_TEST_X_GYRO 	0x50
#define REG_SELF_TEST_Y_GYRO 	0x51
#define REG_SELF_TEST_Z_GYRO 	0x52
#define REG_FIFO_WM_TH1 		0x60
#define REG_FIFO_WM_TH2 		0x61
#define REG_SIGNAL_PATH_RESET 	0x68
#define REG_ACCEL_INTEL_CTRL 	0x69
#define REG_USER_CTRL 			0x6A
#define REG_PWR_MGMT_1 			0x6B
#define REG_PWR_MGMT_2 			0x6C
#define REG_I2C_IF 				0x70
#define REG_FIFO_COUNTH 		0x72
#define REG_FIFO_COUNTL 		0x73
#define REG_FIFO_R_W 			0x74
#define REG_WHO_AM_I 			0x75
#define REG_XA_OFFSET_H 		0x77
#define REG_XA_OFFSET_L 		0x78
#define REG_YA_OFFSET_H 		0x7A
#define REG_YA_OFFSET_L 		0x7B
#define REG_ZA_OFFSET_H 		0x7D
#define REG_ZA_OFFSET_L 		0x7E

#define REG_WHO_AM_I_CONST 		0x12
#define CHIP_RESET_CONST   		0x80

enum icm20602_accel_dlpf {
  ICM20602_ACCEL_DLPF_218_1_HZ = 0, // data clocked at 1kHz
  ICM20602_ACCEL_DLPF_99_HZ = 2, // data clocked at 1kHz
  ICM20602_ACCEL_DLPF_44_8_HZ = 3, // data clocked at 1kHz
  ICM20602_ACCEL_DLPF_21_2_HZ = 4, // data clocked at 1kHz
  ICM20602_ACCEL_DLPF_10_2_HZ = 5, // data clocked at 1kHz
  ICM20602_ACCEL_DLPF_5_1_HZ = 6, // data clocked at 1kHz
  ICM20602_ACCEL_DLPF_420_HZ = 7, // data clocked at 1kHz
  ICM20602_ACCEL_DLPF_BYPASS_1046_HZ, // no filter, data clocked at 4kHz
};
enum icm20602_accel_g {
  ICM20602_ACCEL_RANGE_2G = 0,
  ICM20602_ACCEL_RANGE_4G = 1,
  ICM20602_ACCEL_RANGE_8G = 2,
  ICM20602_ACCEL_RANGE_16G = 3,
};
enum icm20602_gyro_dlpf {
  ICM20602_GYRO_DLPF_250_HZ = 0, // data clocked at 8kHz
  ICM20602_GYRO_DLPF_176_HZ = 1, // data clocked at 1kHz
  ICM20602_GYRO_DLPF_92_HZ = 2, // data clocked at 1kHz
  ICM20602_GYRO_DLPF_41_HZ = 3, // data clocked at 1kHz
  ICM20602_GYRO_DLPF_20_HZ = 4, // data clocked at 1kHz
  ICM20602_GYRO_DLPF_10_HZ = 5, // data clocked at 1kHz
  ICM20602_GYRO_DLPF_5_HZ = 6, // data clocked at 1kHz
  ICM20602_GYRO_DLPF_3281_HZ = 7, // data clocked at 8kHz
  ICM20602_GYRO_DLPF_BYPASS_3281_HZ, // no filter, data clocked at 32kHz
  ICM20602_GYRO_DLPF_BYPASS_8173_HZ, // no filter, data clocked at 32kHz
};
enum icm20602_gyro_dps {
  ICM20602_GYRO_RANGE_250_DPS = 0,
  ICM20602_GYRO_RANGE_500_DPS = 1,
  ICM20602_GYRO_RANGE_1000_DPS = 2,
  ICM20602_GYRO_RANGE_2000_DPS = 3,
};
struct icm20602_dev{
  icm20602_gyro_dlpf gyro_dlpf;
  icm20602_gyro_dps  gyro_dps;
  icm20602_accel_dlpf accel_dlpf;
  icm20602_accel_g accel_g;
};
typedef union regPWR_MGMT_1 {
  struct
  {
    unsigned DEVICE_RESET   :1;
    unsigned SLEEP          :1;
    unsigned CYCLE          :1;
    unsigned GYRO_STADBY    :1;
    unsigned TEMP_DIS	   :1;
    unsigned CLKSEL		   :3;
  } bits;
  unsigned char regByte;
} regPWR_MGMT_1_t;
typedef union regINT_PIN_CFG {
  struct
  {
    unsigned INT_LEVEL	   :1;
    unsigned INT_OPEN       :1;
    unsigned LATCH_INT_EN   :1;
    unsigned INT_RD_CLR	   :1;
    unsigned FSY_INT_LV	   :1;
    unsigned FSY_INT_EN	   :1;
	unsigned RESV		   :2;
  } bits;
  unsigned char regByte;
} regINT_PIN_CFG_t;
