//======================================================
// peripheral setting routines
//======================================================

#include	"A94B114.h"
#include	"func_def.h"

//======================================================
// peripheral setting routines
//======================================================
void ADC_init()
{
	// initialize A/D convertor
	ADCM = 0x28;    	// setting // 20
	ADCM1 = 0x0E;   	// trigger source, alignment, frequency
	IE2 |= 0x01;    	// enable ADC interrupt
	LDOCR = 0x01;
}

void ADC_start(unsigned char ch)
{
	// start A/D convertor
	ADCM = (ADCM & 0xf0) | (ch & 0xf);	// select channel
	ADCM |= 0x40;   	// start ADC
}


void ExINT_init()
{
	// initialize external interrupt
	EIPOL0 = 0x02;  	// polarity 10 ~ 12
	EIPOL1 = 0x00;  	// polarity 0 ~ 2
	IE |= 0x02;     	// enable Ext. INT. 10
}

void LVI_init()
{
	// initialize LVI, LVR
	LVIR = 0x21;    	// set LVI & LVR
	DBTSR = 0x00;   	// set debounce
	IE2 |= 0x08;    	// Enable LVI interrupt
}

void LVI_De_init()
{
	// Disable LVI, LVR
	LVIR = 0x00;    	// set LVI & LVR
	DBTSR = 0x00;   	// set debounce
	IE2 &= ~0x08;    	// Enable LVI interrupt
}

void Timer0_init()
{
	// initialize Timer0
	// 8bit timer, period = 0.25000mS
	T0CR = 0x07;    	// fx/32
	T0DR = 0x7C;    	// period count= 125

	IE1 |= 0x10;    	// Enable Timer interrupt
	T0CR |= 0x80;   	// enable timer
}

void Timer1_init()
{
	// initialize Timer1
	// 16bit timer, period = 499.968000mS
	T1CRH = 0x00;   	// timer disable
	T1CRL = 0x01;   	// fx/2048
	//T1CRL = 0x04; 	// Timer output polarity start Low
	T1ADRH = 0x0F;		// counter value = 3907
	T1ADRL = 0x43;
	IE1 |= 0x20;    	// Enable Timer interrupt
	T1CRH |= 0x80;  	// enable timer
}


void clock_init()
{
	BITCR = 0x84;
	WDTMR = 0x00;
	SYSCON_AR = 0x5A;	// Enable permission to access SCCR

	// internal RC clock (16.0MHz)
	OSCCR = 0x04;   	// Set High freq. OSC
	SCCR = 0x40;
	wait_100uSec(NOP_COUNT/2);
	OSCCR = 0x04;
	WDTMR = 0x00;
	SYSCON_AR = 0x00;	// Disable permission
//	WDTMR = 0x38;

}

void port_init()
{
	// initialize ports
	//   2 : PWM2o    out speed control
	//  12 : P05      out 
	//  15 : EINT10   in  ir remote
	P0IO = 0xFB;    	// direction 11111011
	P0PU = 0x00;    	// pullup
	P0OD = 0x00;    	// open drain
	P0DB = 0x00;    	// debounce
	P0   = 0x00;    	// port initial value

	P1IO = 0xF7;    	// direction
	P1PU = 0x00;    	// pullup
	P1OD = 0x00;    	// open drain
	P1DB = 0x00;    	// debounce
	P1   = 0x00;    	// port initial value

	P2IO = 0xF0;    	// direction
	P2PU = 0x00;    	// pullup
	P2OD = 0x00;    	// open drain
	P2DB = 0x00;    	// debounce
	P2   = 0x00;    	// port initial value

	// Set port functions
	P0FSRL = 0x30;  	// P03~00
	P0FSRH = 0x00;  	// P07~04
	P1FSRL = 0x02;  	// P13~10
	P1FSRH = 0x00;  	// P17~14
	P2FSR = 0x70;   	// P23~20
}

void	Nop_1us_16Mhz(void)
{
	NOP; NOP; NOP; NOP;	// NOP = 62.6ns(@16Mhz) 62.5ns * 16 = 1us
	NOP; NOP; NOP; NOP;
	NOP; NOP; //NOP; NOP;	// LCALL = 2 clock
	//NOP; NOP; NOP; NOP;	// RET = 4 clock
}

void	wait_100uSec(unsigned int delay)
{
	register unsigned int i;

	for( i = 0; i < (delay*10); i++)
	{
		Nop_1us_16Mhz();
		Nop_1us_16Mhz();
		Nop_1us_16Mhz();
		Nop_1us_16Mhz();
	}
}

