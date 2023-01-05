// R/W Parameters
#define speedCtrl_Base_address					0x00
#define OverRide_Base_address						0x01
#define DecCtrl_Base_address						0x02
#define EECtrl_Base_address							0x03

// Read Only
#define Status_Base_address							0x10
#define MotorSpeed1_Base_address				0x11
#define MotorSpeed2_Base_address				0x12
#define MotorPeriod1_Base_address				0x13
#define MotorOeriod2_Base_address				0x14
#define MotorKt1_Base_address						0x15
#define MotorKt2_Base_address						0x16
#define SupplyVoltage_Base_address			0x17
#define FaultCode_Base_address					0x18

// MTP
#define MotorPara1_Base_address					0x20
#define MotorPara2_Base_address					0x21
#define MotorPara3_Base_address					0x22
#define MotorPara4_Base_address					0x23
#define MotorPara5_Base_address					0x24
#define SysOpt0_Base_address						0x25
#define SysOpt1_Base_address						0x26
#define SysOpt2_Base_address						0x27
#define SysOpt3_Base_address						0x28
#define SysOpt4_Base_address						0x29
#define SysOpt5_Base_address						0x2A
#define SysOpt6_Base_address						0x2B
#define SysOpt7_Base_address						0x2C
#define SysOpt8_Base_address						0x2D
#define SysOpt9_Base_address						0x2E	

//  expert MTP 
#define SysOpt10_Base_address						0x2F
#define SysOpt11_Base_address						0x30
#define SysOpt12_Base_address						0x31
#define SysOpt13_Base_address						0x32
#define SysOpt14_Base_address						0x33



// R/W Parameters
#define speedCtrl_Value									0x00
#define OverRide_Value									0x01
#define DecCtrl_Value										0x02
#define EECtrl_Value										0x03

// Read Only
#define Status_Value										0x10
#define MotorSpeed1_Value								0x11
#define MotorSpeed2_Value								0x12
#define MotorPeriod1_Value							0x13
#define MotorOeriod2_Value							0x14
#define MotorKt1_Value									0x15
#define MotorKt2_Value									0x16
#define SupplyVoltage_Value							0x17
#define FaultCode_Value									0x18

// MTP : ESKO_NEW MOTOR TUNING_29.9.2022 //


#define MotorPara1_Value								0x0C//0x07
#define MotorPara2_Value								0X01//0x81
#define MotorPara3_Value								0XC0//0x66
#define MotorPara4_Value								0x2E
#define MotorPara5_Value								0x90 //90
#define SysOpt0_Value										0X80//0x00
#define SysOpt1_Value										0X70//0x70
#define SysOpt2_Value										0x18
#define SysOpt3_Value										0X66//0xA5
#define SysOpt4_Value										0x62
#define SysOpt5_Value										0xCF
#define SysOpt6_Value										0X88//0x88
#define SysOpt7_Value										0X2A//0xE6	
#define SysOpt8_Value										0X04//0x14
#define SysOpt9_Value										0X7F//0x7F	

//  expert MTP 
#define SysOpt10_Value									0X02//0x18
#define SysOpt11_Value									0xFF
#define SysOpt12_Value									0XEB//FF OK 0xEB
#define SysOpt13_Value									0X26//0x2A
#define SysOpt14_Value									0X73//0x72


#define OK				1
#define NOK				0




void i2c_devicew(unsigned char i2c_base,unsigned char i2c_s);
unsigned char i2c_devicer(unsigned char i2c_base);
void i2c_start(void);
void i2c_stop(void);
void i2c_ack(void);
void i2c_nack(void);
void i2c_send(int a);
int	i2c_get(void);
void delaytime(unsigned int ch);
void I2C_Parameter_syllergy(void);
void MTP_Read(void);
void MTP_Write(void);
unsigned char Syllergy_MTP_Verify(void);
void I2C_Motor_Start(void);