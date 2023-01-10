//======================================================
// Main program routine
// - Device name  : A94B114
// - Package type : 20TSSOP
//======================================================
// For XDATA variable : V1.041.00 ~
#define		MAIN	1

// Generated    : Mon, Sep 02, 2019 (15:31:54)
#include	"A94B114.h"
#include "flash.h"
#include	"func_def.h"
#include  "MotorPara.h"
//#include    "Intrins.h"
//#include    "delay.h"     //
//#include "a94b114_gpio.h"
//#include "a94b114_clock.h"
//#include "a94b114_usart.h"

extern unsigned char RemotePress,SleepTimerCompleteFlag_1hr,SleepTimerStartFlag_1hr,TimerStartFlag,LowVoltageResetFlag,Timer_Counter_Complete_Flag;
unsigned char Command,LED_blink_Counter,LED_blink_Status,Fan_load_Healthy=1;
extern unsigned int Timer5min,TimerHrsValue;
extern long NewKey,SleepTimerCounter_1hr,General_Counter;
extern xdata unsigned int ADC_Value;
extern xdata unsigned int Fan_load_unhealthy_Counter;
unsigned char OnceProgrameFlag,OneSecTimer;
//struct variable var;
struct RemoteStatus RemoteData;
xdata unsigned char Fan_load_helathy_count,Fan_load_healthy_once_flag;

//void putstring(char *str)
//{
//	while(*str != 0)
//		USART_SendDataWithInterrupt(*str++);
//}
unsigned char Sleep_Data = 0;

void main()
{
	unsigned char Var_Data[14];
	cli();          	// disable INT. during peripheral setting
	port_init();    	// initialize ports
	//LED_Init
	P0IO |= (1<<5);
	
	clock_init();   	// initialize operation clock
	ExINT_init();   	// initialize external interrupt
	P2PU |= 0x0C;
	P2 |= 0x0C;
	Timer0_init();  	// initialize Timer0
	Timer1_init();  	// initialize Timer1
	ADC_init();     	// initialize A/D convertor

//	#ifdef DEBUG
//		/*Set Alernative Function for USART P14(RX) / P5(TX)*/
//		Port_SetAlterFunctionpin(PORT1, PIN4, 0x1);
//		Port_SetAlterFunctionpin(PORT1, PIN5, 0x1);
//		

//		USART_Initial(9600, USART_DATA_8BIT, USART_STOP_1BIT, USART_PARITY_NO, USART_TX_RX_MODE);
//		
////		USART_ConfigureInterrupt(USART_RX_COMPLETE_INT, TRUE);
//		USART_ConfigureInterrupt(USART_TX_COMPLETE_INT, TRUE);
//	#endif	//DEBUG
	P2IO |= 0x03;
	P2PU |= 0x03;    	// pullup
	P2 |= 0X03;
	I2C_Parameter_syllergy();
	I2C_Motor_Start();
	P2IO &= ~0x03;
	P2PU &= ~0X03;
	
//	LVI_De_init();
//	test_self_PGM();
//	LVI_init();
//	OnceProgrameFlag = 0x00;
	Flash_Read(TEST_WRITE_ADDRESS, &OnceProgrameFlag, 1);
	if(OnceProgrameFlag != 0xAA)
	{
		RemoteData.Power = 1;
		RemoteData.Light = 0;
		RemoteData.FanSpeed = 0;//		RemoteData.FanSpeed = 5;Sunil need to change 0 to 5.

		RemoteData.Timer_Hrs = 0;
		RemoteData.Sleep = 0;
		test_self_PGM();
	}
	else
	{
		Flash_Read(TEST_WRITE_ADDRESS, &Var_Data, 14);
		RemoteData.Power = Var_Data[1];
		RemoteData.Light = Var_Data[2];
		RemoteData.FanSpeed = Var_Data[3];
		RemoteData.Timer_Hrs = Var_Data[4];
		RemoteData.Sleep = Var_Data[5];	
		General_Counter = (Var_Data[6]) | (Var_Data[7]<<8) | (Var_Data[8]<<16) | (Var_Data[9]<<24);
		SleepTimerCounter_1hr = (Var_Data[10]) | (Var_Data[11]<<8) | (Var_Data[12]<<16) | (Var_Data[13]<<24);
	}
	LVI_init();     	// initialize LVI, LVR
	WDTMR = 0x00;
	sei(); 
	if(RemoteData.Light)
	{
		LED_ON;
		
	}
	// enable INT.
	SystemInitialization();
//	putstring("a94b114 USART INTERRUPT TEST!!\n");

	// TODO: add your main code here
//	LED_ON;
	while(1)
	{

//		if(Fan_load_Healthy)
//		{
//			Fan_load_Line_Monitor();
//		}
//		if((Fan_load_Healthy == 0) && (Fan_load_unhealthy_Counter >= FAN_LOAD_UNHELATHY_STABLIZING_TIME))
//		{
//			Fan_load_Line_Monitor();
//			Fan_load_unhealthy_Counter = 0;
//		}
		if(RemotePress)
		{
			Command = RemoteGetKeyProcess(NewKey);
			//RemotePress = 0;
			NewKey = 0;
			LED_blink_Counter = 0;
			LED_blink_Status = 0;
			OneSecTimer = 0;
			LED_OFF;
			process();
			RemotePress = 0;
			Fan_load_healthy_once_flag = 0;
			LVI_De_init();
			test_self_PGM();
			LVI_init();
		}
//		if((RemoteData.Sleep)&&(SleepTimerCompleteFlag_1hr))
//		{
//			SleepOperation();
//			LVI_De_init();
//			test_self_PGM();
//			LVI_init();
//		}
//		if((SleepTimerStartFlag_1hr) || (TimerStartFlag))
//		{
//			if(Timer5min >= TIMER_5_MINUTES)
//			{
//				//write flash
//				//test_self_PGM();
//				Timer5min = 0;
//			}
//		}
		if(Timer_Counter_Complete_Flag)
		{
//			LED_blink_Counter = 2;	//Sunil need to uncommand
//			LED_blink_Status = 1;		//Sunil need to uncommand
			LED_ON;
			fan_power_off();
			//i2c_speed(FAN_OFF_VALUE);
//			Timer_Counter_Complete_Flag = 1;
			RemoteData.Power = 0;
			RemoteData.Timer_Hrs = REMOTE_TIMER_OFF;
			TimerStartFlag = 0;
			General_Counter = 0;
			TimerHrsValue = 0;
			Timer_Counter_Complete_Flag = 0;
		}
		if(LowVoltageResetFlag)
		{
			
			//LVI_De_init();
			//test_self_PGM();
			LowVoltageResetFlag = 0;
			//LVI_init();
		}
	}
}

void process()
{
	switch(Command)
	{
		case POWER:
			//OPERTION
			fan_power_on();
			break;
		/*case LIGHT:
			//OPERTION
			if(RemoteData.Light)
			{
				RemoteData.Light = 0;
				LED_OFF;
			}
			else
			{
				RemoteData.Light = 1;
				LED_ON;
			}
			Command = 0;				
			break; */
		case FAN_SPEED_1:
			//OPERTION
			if(!RemoteData.Sleep)
				{		
					Sleep_Data = 1;
					fanSpeed1();
				}
			Command = 0;				
			break;
		case FAN_SPEED_2:
			//OPERTION
			if(!RemoteData.Sleep)
				{		
					Sleep_Data = 2;
					fanSpeed2();
				}
			Command = 0;	
			break;
		case FAN_SPEED_3:
			//OPERTION
			if(!RemoteData.Sleep)
				{		
					Sleep_Data = 3;
					fanSpeed3();
				}
			Command = 0;	
			break;
		case FAN_SPEED_4:
			//OPERTION			
			if(!RemoteData.Sleep)
				{		
					Sleep_Data = 4;
					fanSpeed4();
				}
			Command = 0;	
			break;
		case FAN_SPEED_5:
			//OPERTION
			if(!RemoteData.Sleep)
				{		
					Sleep_Data = 5;
					fanSpeed5();
				}
			Command = 0;	
			break;
		case FAN_SPEED_6:
			//OPERTION
			if(!RemoteData.Sleep)
				{		
					Sleep_Data = 6;
					fanSpeed6();
				}
			Command = 0;	
			break;
		case BOOST:
			//OPERTION
			if(!RemoteData.Sleep)
				{		
					fanSpeed_BOOST();
				}
			Command = 0;	
			break;
		case TIME_2HRS:
			//OPERTION
			if((RemoteData.Power)&&(!RemoteData.Sleep)&&(RemoteData.Timer_Hrs != REMOTE_TIMER_2HRS))
			{				
				Timer_Hrs_process(REMOTE_TIMER_2HRS);
				RemoteData.Timer_Hrs = REMOTE_TIMER_2HRS;	
			}
			else if((RemoteData.Power)&&(!RemoteData.Sleep)&&(RemoteData.Timer_Hrs == REMOTE_TIMER_2HRS))
			{
				Timer_Disable();					
			}
			Command = 0;
			break;
		case TIME_4HRS:
			//OPERTION
			if((RemoteData.Power)&&(!RemoteData.Sleep)&&(RemoteData.Timer_Hrs != REMOTE_TIMER_4HRS))
			{
				Timer_Hrs_process(REMOTE_TIMER_4HRS);
				RemoteData.Timer_Hrs = REMOTE_TIMER_4HRS;									
			}
			else if((RemoteData.Power)&&(!RemoteData.Sleep)&&(RemoteData.Timer_Hrs == REMOTE_TIMER_4HRS))
			{
				Timer_Disable();
			}
			Command = 0;
			break;
		/*case TIME_6HRS:
			//OPERTION
			if((RemoteData.Power)&&(!RemoteData.Sleep)&&(RemoteData.Timer_Hrs != REMOTE_TIMER_6HRS))
			{
				Timer_Hrs_process(REMOTE_TIMER_6HRS);
				RemoteData.Timer_Hrs = REMOTE_TIMER_6HRS;									
			}
			else if((RemoteData.Power)&&(!RemoteData.Sleep)&&(RemoteData.Timer_Hrs == REMOTE_TIMER_6HRS))
			{
				Timer_Disable();	
			}
			Command = 0;
			break;*/
		case TIME_8HRS:
			//OPERTION
			if((RemoteData.Power)&&(!RemoteData.Sleep)&&(RemoteData.Timer_Hrs != REMOTE_TIMER_8HRS))
			{
				Timer_Hrs_process(REMOTE_TIMER_8HRS);
				RemoteData.Timer_Hrs = REMOTE_TIMER_8HRS;									
			}
			else if((RemoteData.Power)&&(!RemoteData.Sleep)&&(RemoteData.Timer_Hrs == REMOTE_TIMER_8HRS))
			{
				Timer_Disable();	
			}
			Command = 0;
			break;
		case SLEEP_MODE:
			//OPERATION
			Timer_Disable();
			if((!RemoteData.Sleep) && (RemoteData.Power))
			{
				LED_blink_Counter = 4+(3*(RemoteData.Light));
				LED_blink_Status = 1;
//				RemoteData.Sleep = 1;	//Sunil need to uncommand.
				SleepTimerStartFlag_1hr =1;
				SleepTimerCompleteFlag_1hr = 0;
				SleepTimerCounter_1hr = 0;
				//Sleep operations
			}
			else
			{
				LED_blink_Counter = 2+(3*(RemoteData.Light));
				LED_blink_Status = 1;
				RemoteData.Sleep = 0;
				SleepTimerStartFlag_1hr = 0;
				SleepTimerCompleteFlag_1hr = 0;
				SleepTimerCounter_1hr = 0;
				// disable all the sleep operations
			}
			break;
			
						
		/* case REVERSE_MODE:
				if(P0 & 0x40)
				{
					P0 &= ~(1<<6);
				}
				else
				{
					P0 |= (1<<6);
				}
			break; */			
			
			
		default:
			//operation
		break;
			
	}
}

void SystemInitialization(void)
{
	if(RemoteData.Power)
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
	}    
	

	if(RemoteData.Timer_Hrs)
		
	{
		Timer_Hrs_process(RemoteData.Timer_Hrs);
		// timer start flag loaded
		// general counter value loaded
	}
	if(	RemoteData.Sleep)
	{
		LED_blink_Counter = 4+(3*(RemoteData.Light));
		LED_blink_Status = 1;
//		RemoteData.Sleep = 1;	//Sunil need to uncommand.
		SleepTimerStartFlag_1hr =1;
		SleepTimerCompleteFlag_1hr = 0;		
	}
}

unsigned char current_speed;
void Fan_load_Line_Monitor(void)
{
	
	if(Fan_load_Healthy)	
	{
		if ((ADC_Value >= (FAN_LOAD_UNHEALTHY_VALUE)))
		{
			P2IO |= 0x03;
			P2PU |= 0x03;    	// pullup
			P2 |= 0X03;
			Fan_load_Healthy = 0;
			current_speed = i2c_devicer(speedCtrl_Base_address);
			P2IO &= ~0x03;
			P2PU &= ~0X03;
			if(!Fan_load_healthy_once_flag)
			{
				current_speed = current_speed-10;
				i2c_speed(current_speed);
			}
			else if (Fan_load_healthy_once_flag)
			{
				if(ADC_Value <= (FAN_LOAD_UNHEALTHY_VALUE+3))
				{
					Fan_load_Healthy = 1;
				}
				else
				{
					Fan_load_Healthy = 0;
				}
			}
		}			
	}
	else
	{
		//Check wheateher AC is not in healthy state
		if((ADC_Value <= FAN_LOAD_HYSTERSIS_VALUE)||(ADC_Value < (FAN_LOAD_HEALTHY_VALUE-1)))
		{
			//Fan_load_Healthy = 1;
			if(current_speed < 255)
			{	
				current_speed = current_speed+1;
			}
			i2c_speed(current_speed);
			//SystemInitialization();
			//fan on in previous condition
		}
		else if((ADC_Value >= (FAN_LOAD_HEALTHY_VALUE-1)) && (ADC_Value <= (FAN_LOAD_UNHEALTHY_VALUE-5)))
		{
			Fan_load_helathy_count++;
			if(Fan_load_helathy_count >= 20)
			{
				Fan_load_helathy_count = 0;
				Fan_load_Healthy = 1;	
				Fan_load_healthy_once_flag = 1;
			}				
		}
		/*else if(ADC_Value >= FAN_LOAD_UNHEALTHY_VALUE+25)
		{
			current_speed = current_speed-10;
			i2c_speed(current_speed);
		}*/
		else
		{
			//lower the speed
			current_speed = current_speed-2;
			i2c_speed(current_speed);
		}
	}
}