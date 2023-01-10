#include	"A94B114.h"
#include	"func_def.h"
#include  "MotorPara.h"
//======================================================
// interrupt routines
//======================================================

int timerValue,pulseCount;
long bitPattern,NewKey,SleepTimerCounter_1hr,General_Counter;
unsigned char RemotePress,ADC250usCount;

extern unsigned char OneSecTimer,Command,LED_blink_Counter,LED_blink_Status;

unsigned char TimerStartFlag,SleepTimerCompleteFlag_1hr,SleepTimerStartFlag_1hr,LowVoltageResetFlag,Timer_Counter_Complete_Flag;
unsigned int TimerHrsValue,Timer5min,msCount=0;

extern struct RemoteStatus RemoteData;
xdata unsigned int Fan_load_unhealthy_Counter;

void INT_Ext10() interrupt 1
{
//	LED_OFF;
	if(!RemotePress)
	{
	timerValue = msCount;
	msCount = 0;
	pulseCount++;
	if((timerValue>=200)) // If the pulse width is greater than 50ms, this will mark the SOF
	{ 
		pulseCount = -2; // First 2 counts needs to be skipped hence pulse ocunt is set to -2 
		bitPattern = 0;
	}
	else if((pulseCount>=0) && (pulseCount<32)) //Accumulate the bit values between 0-31.
	{	  
		if(timerValue>=8)                      //pulse width greater than 2ms is considered as LOGIC1
		{
			bitPattern |=(long) 1<<(31-pulseCount);
		}
		else
		{
		}
	}
	else if(pulseCount>=32)                  //This will mark the End of frame as 32 pulses are received
	{
		NewKey = bitPattern;                // Copy the newKey(patter) and set the pulse count to 0;
		pulseCount = 0;
		RemotePress = 1;
	}
	}
	// External interrupt 10
	// TODO: add your code here
}

void INT_Timer0() interrupt 9
{
	if(msCount <= 250)
	{
		msCount++;
	}
	ADC250usCount++;
	//Fan_load_unhealthy_Counter++;
	if (ADC250usCount >= 100)
	{
		ADC_start(8);
		ADC250usCount = 0;
		Fan_load_unhealthy_Counter++;
	}		
	// Timer0 interrupt
	// TODO: add your code here
}


void INT_Timer1() interrupt 10				// 250msec interrupt
{
	if(LED_blink_Counter)
	{
		if(OneSecTimer % 2 == 0)
		{
			LED_ON;
		}
		else
		{
			LED_OFF;
		}
		LED_blink_Counter--;
	}
	if((LED_blink_Status) && (LED_blink_Counter > 0))
	{
		OneSecTimer++;
	}
	else
	{
		OneSecTimer = 0;
		LED_blink_Status = 0;
		LED_blink_Counter = 0;
		if(RemoteData.Light)
		{
			LED_ON;
		}
	}
	
	if(TimerStartFlag)
	{
		General_Counter++;
		Timer5min++;
		if(General_Counter >= TimerHrsValue)
		{
			/*LED_blink_Counter = 2;
			LED_blink_Status = 1;
			//fan_power_off();
			//i2c_speed(FAN_OFF_VALUE);
			Timer_Counter_Complete_Flag = 1;
			RemoteData.Power = 0;
			RemoteData.Timer_Hrs = REMOTE_TIMER_OFF;
			TimerStartFlag = 0;
			General_Counter = 0;
			TimerHrsValue = 0;*/
			Timer_Counter_Complete_Flag = 1;
		}
	}
	if(SleepTimerStartFlag_1hr)
	{
		SleepTimerCounter_1hr++;
		Timer5min++;
		if(SleepTimerCounter_1hr >= SLEEP_ONE_HOUR_TIMER1_VALUE)
		{
			SleepTimerCompleteFlag_1hr = 1;
			SleepTimerCounter_1hr = 0;
		}		
	}
	// Timer1 interrupt
	// TODO: add your code here
}

unsigned int adcVal = 0;
xdata long ADCdata;
xdata unsigned int ADC_Value = 0;

void INT_ADC() interrupt 12
{ 
	static unsigned char SamplesTaken = 0;
	xdata long temp = 0;
	//long temp,ADCdata;
	// ADC interrupt
	// TODO: add your code here
	adcVal = (ADCRH << 8) | ADCRL;
	ADCdata += adcVal;
	SamplesTaken++;
	if(SamplesTaken >= ADC_SAMPLES)
	{
		ADCdata = ADCdata/ADC_SAMPLES;
		temp = (long)250*ADCdata;
		temp = temp/4096;
		ADC_Value = (unsigned int)temp;
		SamplesTaken = 0;
		ADCdata = 0;
	}
	ADCM &= ~0x40;  	// stop ADC
	
}



void INT_LVI() interrupt 15
{
	// LVI interrupt
	// TODO: add your code here
	LowVoltageResetFlag = 1;
	
}
