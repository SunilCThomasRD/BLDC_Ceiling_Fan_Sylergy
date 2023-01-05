#include	"A94B114.h"
#include	"func_def.h"
//#include  "MotorPara.h"

extern unsigned char TimerStartFlag,SleepTimerCompleteFlag_1hr,SleepTimerStartFlag_1hr;
extern unsigned int TimerHrsValue,General_Counter;
extern unsigned char Command,LED_blink_Counter,LED_blink_Status;
extern long SleepTimerCounter_1hr;
extern struct RemoteStatus RemoteData;

//void i2c_speed(unsigned char);
//unsigned char temp = 0;
void fan_power_off(void)
{	
	/*T2BDRH = 0x00;  	// duty High
	T2BDRL = 0x00;  	// duty Low
	T2CRH |= 0x80;  	// enable counter*/
	//i2c_devicew(speedCtrl_Base_address, FAN_OFF_VALUE);	
	//I2C_Motor_Start();
	i2c_speed(FAN_OFF_VALUE);
}

void fan_power_on(void)
{
	if(RemoteData.Power == 1)
	{
		LED_blink_Counter = 2+(3*(RemoteData.Light));
		LED_blink_Status = 1;
		fan_power_off();
		//i2c_speed(FAN_OFF_VALUE);
		RemoteData.Power = 0;
		if(RemoteData.FanSpeed == 0)
		{
			RemoteData.FanSpeed = 5;
		}
		if(RemoteData.Timer_Hrs != REMOTE_TIMER_OFF)
		{
			TimerStartFlag = 0;
			General_Counter = 0;
			TimerHrsValue = 0;
			RemoteData.Timer_Hrs = REMOTE_TIMER_OFF;	
		}
		if(RemoteData.Sleep)
		{
			SleepTimerStartFlag_1hr = 0;
			SleepTimerCompleteFlag_1hr = 0;
			SleepTimerCounter_1hr = 0;
			RemoteData.Sleep = 0;
		}
		//fan_power = 0;
		Command = 0;
	}
	else
	{
		switch(RemoteData.FanSpeed)
		{
			case 0:
				//operation
				fan_power_off();
				//i2c_speed(FAN_OFF_VALUE);
				break;
			case 1:
				//operation
				fanSpeed1();
				break;
			case 2:
				//operation
				fanSpeed2();
				break;
			case 3:
				//operation
				fanSpeed3();
				break;
			case 4:
				//operation
				fanSpeed4();
				break;
			case 5:
				//operation
				fanSpeed5();
				break;
			case 6:
				//operation
				fanSpeed6();
				break;
			case 7:
				//operation
				fanSpeed_BOOST();
				break;
			default:
				//operation
				//not possible
				break;
		}
		RemoteData.Power = 1;
		Command = 0;
	}	
}

void fanSpeed1(void)		// 45% duty cycle
{
		LED_blink_Counter = 2+(3*(RemoteData.Light));
		LED_blink_Status = 1;
		/*T2BDRH = 0x02;  	// duty High
		T2BDRL = 0x58;  	// duty Low
		T2CRH = 0xB2;  	// enable counter*/
		//i2c_devicew(speedCtrl_Base_address, FAN_SPEED1_VALUE);
		i2c_speed(FAN_SPEED1_VALUE);
		RemoteData.FanSpeed = 1;
		RemoteData.Power = 1;
		
}

void fanSpeed2(void)		// 55% duty cycle
{
		LED_blink_Counter = 4+(3*(RemoteData.Light));
		LED_blink_Status = 1;
		/*T2BDRH = 0x02;  	// duty High
		T2BDRL = 0xDE;  	// duty Low
		T2CRH = 0xB2;  	// enable counter*/
		//i2c_devicew(speedCtrl_Base_address, FAN_SPEED2_VALUE);	
		i2c_speed(FAN_SPEED2_VALUE);
		RemoteData.FanSpeed = 2;
		RemoteData.Power = 1;
	
}

void fanSpeed3(void)		// 65% duty cycle
{
		LED_blink_Counter = 6+(3*(RemoteData.Light));
		LED_blink_Status = 1;
		/*T2BDRH = 0x03;  	// duty High
		T2BDRL = 0x63;  	// duty Low
		T2CRH = 0xB2;  	// enable counter*/
		//i2c_devicew(speedCtrl_Base_address, FAN_SPEED3_VALUE);
		i2c_speed(FAN_SPEED3_VALUE);	
		RemoteData.FanSpeed = 3;
		RemoteData.Power = 1;
		
}

void fanSpeed4(void)		// 75% duty cycle
{
		LED_blink_Counter = 8+(3*(RemoteData.Light));
		LED_blink_Status = 1;
		/*T2BDRH = 0x03;  	// duty High
		T2BDRL = 0xE8;  	// duty Low
		T2CRH = 0xB2;  	// enable counter*/
		//i2c_devicew(speedCtrl_Base_address, FAN_SPEED4_VALUE);
		i2c_speed(FAN_SPEED4_VALUE);
		RemoteData.FanSpeed = 4;
		RemoteData.Power = 1;
	
}

void fanSpeed5(void)		// 80% duty cycle
{
		LED_blink_Counter = 10+(3*(RemoteData.Light));
		LED_blink_Status = 1;
		/*T2BDRH = 0x04;  	// duty High
		T2BDRL = 0x2B;  	// duty Low
		T2CRH = 0xB2;  	// enable counter*/
		//i2c_devicew(speedCtrl_Base_address, FAN_SPEED5_VALUE);
		i2c_speed(FAN_SPEED5_VALUE);
		RemoteData.FanSpeed = 5;
		RemoteData.Power = 1;
}

void fanSpeed6(void)
{
		LED_blink_Counter = 12+(3*(RemoteData.Light));
		LED_blink_Status = 1;
		/*T2BDRH = 0x04;  	// duty High
		T2BDRL = 0x2B;  	// duty Low
		T2CRH = 0xB2;  	// enable counter*/
		//i2c_devicew(speedCtrl_Base_address, FAN_SPEED5_VALUE);
		i2c_speed(FAN_SPEED6_VALUE);
		RemoteData.FanSpeed = 6;
		RemoteData.Power = 1;
}

void fanSpeed_BOOST(void)		// 85% duty cycle
{		
		LED_blink_Counter = 2+(3*(RemoteData.Light));
		LED_blink_Status = 1;
		/*T2BDRH = 0x04;  	// duty High
		T2BDRL = 0x6D;  	// duty Low
		T2CRH = 0xB2;  	// enable counter*/
		//i2c_devicew(speedCtrl_Base_address, FAN_BOOST_VALUE);	
		i2c_speed(FAN_BOOST_VALUE);
		RemoteData.FanSpeed = 7;
		RemoteData.Power = 1;

}

void Timer_Hrs_process(unsigned char Timer)
{
	if(Timer == REMOTE_TIMER_2HRS)
	{
		LED_blink_Counter = 4+(3*(RemoteData.Light));
		LED_blink_Status = 1;
		TimerStartFlag = 1;
		TimerHrsValue = 14400;
	}
	else if(Timer == REMOTE_TIMER_4HRS)
	{
		LED_blink_Counter = 8+(3*(RemoteData.Light));
		LED_blink_Status = 1;
		TimerStartFlag = 1;
		TimerHrsValue = 28800;
	}
	else if(Timer == REMOTE_TIMER_6HRS)
	{
		LED_blink_Counter = 12+(3*(RemoteData.Light));
		LED_blink_Status = 1;
		TimerStartFlag = 1;
		TimerHrsValue = 43200;
	}
	else if(Timer == REMOTE_TIMER_8HRS)
	{
		LED_blink_Counter = 16+(3*(RemoteData.Light));
		LED_blink_Status = 1;
		TimerStartFlag = 1;
		TimerHrsValue = 57600;
	}
}

void SleepOperation(void)
{
	if(SleepTimerCompleteFlag_1hr)
	{
		RemoteData.FanSpeed = RemoteData.FanSpeed - 1;
		SleepTimerCompleteFlag_1hr = 0;
		switch(RemoteData.FanSpeed)
		{
			case 0:
				//operation
				LED_blink_Counter = 2+(3*(RemoteData.Light));
				LED_blink_Status = 1;
				fan_power_off();
				//i2c_speed(FAN_OFF_VALUE);
				RemoteData.Power = 0;
				RemoteData.Sleep = 0;
				SleepTimerStartFlag_1hr = 0;
				SleepTimerCompleteFlag_1hr = 0;
				SleepTimerCounter_1hr = 0;
				//fanSpeed status =0 , fanSleep = 0 , fan power off
				break;
			case 1:
				//operation
				fanSpeed1();
				break;
			case 2:
				//operation
				fanSpeed2();
				break;
			case 3:
				//operation
				fanSpeed3();
				break;
			case 4:
				//operation
				fanSpeed4();
				break;
			case 5:
				//operation
				fanSpeed5();
				break;
			default:
				//operation
				//not possible
				break;
		}
	}
}

void Timer_Disable(void)
{
	//Operation
	LED_blink_Counter = 2+(3*(RemoteData.Light));
	LED_blink_Status = 1;
	TimerStartFlag = 0;
	General_Counter = 0;
	TimerHrsValue = 0;
	RemoteData.Timer_Hrs = REMOTE_TIMER_OFF;
}

