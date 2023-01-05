#include	"A94B114.h"
#include	"func_def.h"
#include  "MotorPara.h"

unsigned char MTP_Programming_Staus;

void I2C_Parameter_syllergy(void)
{
	unsigned char status = 0;
	//MTP_Read();
	i2c_devicew(0xF1, 0x2B);
	delaytime(100);
	status = Syllergy_MTP_Verify();
	if(status == OK)
		return;
	i2c_devicew(EECtrl_Base_address, 0xC0);
	delaytime(100);
	i2c_devicew(0xF1, 0x2B);
	delaytime(100);
	//Write Motor Para
	MTP_Write();	
	//--------
	i2c_devicew(DecCtrl_Base_address, 0xB6);
	delaytime(100);
	i2c_devicew(EECtrl_Base_address, 0xD0);
	delaytime(10000);
	//wait for 36msec
	do{
		MTP_Programming_Staus = i2c_devicer(EECtrl_Base_address);		
		MTP_Programming_Staus = (MTP_Programming_Staus & 0x10);
	}while(MTP_Programming_Staus);
	status = 0;
	//MTP_Read();
	status = Syllergy_MTP_Verify();
	if(status == OK)
	{
		/*i2c_devicew(EECtrl_Base_address, 0x00);
		delaytime(100);
		i2c_devicew(DecCtrl_Base_address, 0x00);
		delaytime(100);*/
		return;
	}
	else
	{
		I2C_Parameter_syllergy();
	}
	//P2IO = 0xF4;
	//Refresh I2c /*registerdata  */
	/*
	i2c_devicew(EECtrl_Base_address, 0x40);
	i2c_devicew(DecCtrl_Base_address, 0xB6);
	i2c_devicew(EECtrl_Base_address, 0x20);
	
	// wait 10msec
	do{
		MTP_Refreshing_Staus = i2c_devicer(EECtrl_Base_address);		
		MTP_Refreshing_Staus = (MTP_Refreshing_Staus & 0x20);
	}while(MTP_Programming_Staus);*/
}

void i2c_devicew(unsigned char i2c_base,unsigned char i2c_s)
{
	i2c_start();
	i2c_send(0x68);
	i2c_send(i2c_base);
	i2c_send(i2c_s);
  i2c_stop();
	delaytime(1000);
}

unsigned char i2c_devicer(unsigned char i2c_base)
{
	unsigned char i2c_s;
	i2c_start();
	i2c_send(0x68);
	i2c_send(i2c_base);
	i2c_stop();
	i2c_start();
	i2c_send(0x69);
	i2c_s = i2c_get();
	i2c_nack();
	i2c_stop();
	return(i2c_s);
}


void i2c_start(void)
{  
	//GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_OD_HIZ_SLOW);
	P2IO |= (1<<1);
	P2PU |= (1<<1);
	delaytime(100);
	//GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
	P2 |= (1<<1);
	//GPIO_WriteHigh(GPIOC, GPIO_PIN_5);
	P2 |= (1<<0);
	delaytime(100);
	//GPIO_WriteLow(GPIOC, GPIO_PIN_4);
	P2 &= ~(1<<1);
	delaytime(100);
	//GPIO_WriteLow(GPIOC, GPIO_PIN_5);
	P2 &= ~(1<<0);
	delaytime(100);
}

void i2c_stop(void)
{
	//GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_OD_HIZ_SLOW);
	P2IO |= (1<<1);
	P2PU |= (1<<1);
	delaytime(100);
	//GPIO_WriteLow(GPIOC, GPIO_PIN_4);
	P2 &= ~(1<<1);
	delaytime(100);
	//GPIO_WriteHigh(GPIOC, GPIO_PIN_5);
	P2 |= (1<<0);
	delaytime(100);
	//GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
	P2 |= (1<<1);
}

void i2c_ack(void)
{
	//GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_OD_HIZ_SLOW);
	P2IO |= (1<<1);
	P2PU |= (1<<1);
	delaytime(100);
	//GPIO_WriteLow(GPIOC, GPIO_PIN_4);
	P2 &= ~(1<<1);
	//GPIO_WriteHigh(GPIOC, GPIO_PIN_5);
	P2 |= (1<<0);
	delaytime(100);
	//GPIO_WriteLow(GPIOC, GPIO_PIN_5);
	P2 &= ~(1<<0);
}

void i2c_nack(void)
{
	//GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_OD_HIZ_SLOW);
	P2IO |= (1<<1);
	P2PU |= (1<<1);
	delaytime(100);
	//GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
	P2 |= (1<<1);
	//GPIO_WriteHigh(GPIOC, GPIO_PIN_5);
	P2 |= (1<<0);
	delaytime(100);
	//GPIO_WriteLow(GPIOC, GPIO_PIN_5);
	P2 &= ~(1<<0);
}

/******************************************************************************************
function to sent 8 bits to the I2C device for writing
******************************************************************************************/

void i2c_send(int a)
{
	int i=0x80,j;
	//GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_OD_HIZ_SLOW);
	P2IO |= (1<<1);
	P2PU |= (1<<1);
	delaytime(100);
	
	for(j=0x08;j>0x00;j--)
	{
		if((a & i) != 0x00)
			//GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
			P2 |= (1<<1);
		else
			//GPIO_WriteLow(GPIOC, GPIO_PIN_4);
			P2 &= ~(1<<1);
		
		//GPIO_WriteHigh(GPIOC, GPIO_PIN_5);
		P2 |= (1<<0);
		delaytime(100);
		//GPIO_WriteLow(GPIOC, GPIO_PIN_5);
		P2 &= ~(1<<0);
		delaytime(100);
		i = i>>1;
	}
	//GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
	P2 |= (1<<1);
	//GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT);
	P2IO &= ~(1<<1);
	delaytime(100);
	//GPIO_WriteHigh(GPIOC, GPIO_PIN_5);
	P2 |= (1<<0);
	delaytime(100);
	//GPIO_WriteLow(GPIOC, GPIO_PIN_5);
	P2 &= ~(1<<0);
	delaytime(100);
}

/******************************************************************************************
function to receive 8 bits from the I2C device
******************************************************************************************/

int	i2c_get(void)
{
	int a=0,temp1,b;
	//GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT);
	P2IO &= ~(1<<1);
	delaytime(100);
	for(temp1=0x08;temp1>0x00;temp1--)
	{
		delaytime(100);
		//GPIO_WriteHigh(GPIOC, GPIO_PIN_5);
		P2 |= (1<<0);
	//	while(!scl)
	//		;
		delaytime(100);
		a = a << 0x01;
		b = (P2 & 0x02);//GPIO_ReadInputPin(GPIOC, GPIO_PIN_4);
		if(b)
			a = a | 0x01;
		else
			a = a | 0X00;
		//GPIO_WriteLow(GPIOC, GPIO_PIN_5);
		P2 &= ~(1<<0);
	}
	//GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_OD_HIZ_SLOW);
	P2IO |= (1<<1);
	P2PU |= (1<<1);
	delaytime(100);
	//GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
	P2 |= (1<<1);
	delaytime(100);
	//GPIO_WriteHigh(GPIOC, GPIO_PIN_5);
	P2 |= (1<<0);
	delaytime(100);
	//GPIO_WriteLow(GPIOC, GPIO_PIN_5);
	P2 &= ~(1<<0);
	delaytime(100);
	return(a);
}

void delaytime(unsigned int ch)
{
	unsigned int i=0;
	for(i=0;i<ch;i++)
	{
		//for(j=0;j<ch;j++);
	}
}

void MTP_Write(void)
{
	i2c_devicew(MotorPara1_Base_address, MotorPara1_Value);
	delaytime(100);
	i2c_devicew(MotorPara2_Base_address, MotorPara2_Value);
	delaytime(100);
	i2c_devicew(MotorPara3_Base_address, MotorPara3_Value);
	delaytime(100);
	i2c_devicew(MotorPara4_Base_address, MotorPara4_Value);
	delaytime(100);
	i2c_devicew(MotorPara5_Base_address, MotorPara5_Value);
	delaytime(100);
	
	i2c_devicew(SysOpt0_Base_address, SysOpt0_Value);
	delaytime(100);
	i2c_devicew(SysOpt1_Base_address, SysOpt1_Value);
	delaytime(100);
	i2c_devicew(SysOpt2_Base_address, SysOpt2_Value);
	delaytime(100);
	i2c_devicew(SysOpt3_Base_address, SysOpt3_Value);
	delaytime(100);
	i2c_devicew(SysOpt4_Base_address, SysOpt4_Value);
	delaytime(100);
	i2c_devicew(SysOpt5_Base_address, SysOpt5_Value);
	delaytime(100);
	i2c_devicew(SysOpt6_Base_address, SysOpt6_Value);
	delaytime(100);
	i2c_devicew(SysOpt7_Base_address, SysOpt7_Value);
	delaytime(100);
	i2c_devicew(SysOpt8_Base_address, SysOpt8_Value);
	delaytime(100);
	i2c_devicew(SysOpt9_Base_address, SysOpt9_Value);
	delaytime(100);
	i2c_devicew(SysOpt10_Base_address, SysOpt10_Value);
	delaytime(100);
	i2c_devicew(SysOpt11_Base_address, SysOpt11_Value);
	delaytime(100);
	i2c_devicew(SysOpt12_Base_address, SysOpt12_Value);
	delaytime(100);
	i2c_devicew(SysOpt13_Base_address, SysOpt13_Value);
	delaytime(100);
	i2c_devicew(SysOpt14_Base_address, SysOpt14_Value);
	delaytime(100);
	
}
unsigned char dummy1;
unsigned char Syllergy_MTP_Verify(void)
{
	unsigned char Motor_MTP_Para[20]= {MotorPara1_Value,MotorPara2_Value,MotorPara3_Value,MotorPara4_Value,MotorPara5_Value,
	SysOpt0_Value,SysOpt1_Value,SysOpt2_Value,SysOpt3_Value,SysOpt4_Value,SysOpt5_Value,SysOpt6_Value,SysOpt7_Value,SysOpt8_Value,
	SysOpt9_Value,SysOpt10_Value,SysOpt11_Value,SysOpt12_Value,SysOpt13_Value,SysOpt14_Value};
	unsigned char i=0,dummy,temp;
	//unsigned char dataArray[20];
	for(i=0;i<=19;i++)
	{
		dummy1 = i2c_devicer(32+i);
		if(i <= 18)
		{
			if(dummy1 != Motor_MTP_Para[i])
				return NOK;
		}
		else
		{
			dummy1 = dummy1 & 0xF0;
			temp = Motor_MTP_Para[i]&0xF0;
			if(dummy1 != temp)
				return NOK;
		}
	}
	return OK;
}


void I2C_Motor_Start(void)
{
	i2c_devicew(OverRide_Base_address, 0x80);
	i2c_devicew(speedCtrl_Base_address, FAN_OFF_VALUE);		
}

void i2c_speed(unsigned char ch)
{
	unsigned char temp;
	P2IO |= 0x03;
	P2PU |= 0x03;    	// pullup
	P2 |= 0X03;
	i2c_devicew(speedCtrl_Base_address, ch);
	do{
		temp = i2c_devicer(speedCtrl_Base_address);
	}while(temp != ch);	
	P2IO &= ~0x03;
	P2PU &= ~0X03;
}
//GPIO_PIN_4  ---------  SDA
//GPIO_PIN_5  -----------SCL

