/***************************************************************************//**
*   @file       a94b114_clock.c
*   @brief      a94b114 System clock peripheral function 
*   @author     Application Team, ABOV Semiconductor Co., Ltd.
*   @version    V1.00
*   @date       15. JAN. 2020
*
* Copyright(C) 2020, ABOV Semiconductor
* All rights reserved.
*
********************************************************************************
* ABOV Disclaimer
*
*IMPORTANT NOTICE - PLEASE READ CAREFULLY
*ABOV Semiconductor ("ABOV") reserves the right to make changes, corrections, enhancements, 
*modifications, and improvements to ABOV products and/or to this document at any time without notice. 
*ABOV does not give warranties as to the accuracy or completeness of the information included herein.
*Purchasers should obtain the latest relevant information of ABOV products before placing orders. 
*Purchasers are entirely responsible for the choice, selection, and use of ABOV products and 
*ABOV assumes no liability for application assistance or the design of purchasers' products. No license, 
*express or implied, to any intellectual property rights is granted by ABOV herein. 
*ABOV disclaims all express and implied warranties and shall not be responsible or
*liable for any injuries or damages related to use of ABOV products in such unauthorized applications. 
*ABOV and the ABOV logo are trademarks of ABOV.
*All other product or service names are the property of their respective owners. 
*Information in this document supersedes and replaces the information previously
*supplied in any former versions of this document.
*2020 ABOV Semiconductor  All rights reserved
*
*/


/*******************************************************************************
* Included File
*******************************************************************************/
#include "a94b114_clock.h"
#include "delay.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief	Initialize System Clock peripheral
* @param    clock_sel	This parameter contains the selection of clock.
* @return	None
*/
void Clock_Initial(uint8_t clock_sel)
{
    uint8_t temp_reg;
	if(clock_sel <= HSI32_DIV32)
	{
		/* Internal 32Mhz RC OSC for system clock */
		SYSCON_AR = 0x5A;
		SCCR	&= ~(0x3<<0);            
		
		temp_reg = OSCCR;
		/* Internal RC Oscillator Post-divider Select INT-RC/n (32/n MHz) */
		temp_reg  &= ~((0x3 << 4) | (1 << 2));
		temp_reg  |= (clock_sel << 4) | (1 << 2);
		
		SYSCON_AR = 0x5A;
		OSCCR = temp_reg;
	}
	else if(clock_sel <= LSI_DIV16)
	{
		/* Internal 256kHz RC OSC for system clock */
		temp_reg = OSCCR;
		temp_reg &= ~((0x3 << 6) | (0x01));
		temp_reg |= ((clock_sel - 4) << 6) | (0x01);
		
		SYSCON_AR = 0x5A;
		OSCCR = temp_reg;
		NOP_10us_Delay(1000);
		
		temp_reg = SCCR;
		temp_reg	|= 0x02;
		
		SYSCON_AR = 0x5A;
		SCCR	= temp_reg;  
 	}
	else if(clock_sel == HSE)
	{
		/* Input GPIO mode, Alternative Function for External Main OSC  */
		P1IO &= ~((0x1 << 1) | (0x1 << 0)); 
		
		/* External Main OSC for system clock */
		SYSCON_AR = 0x5A;
		OSCCR |= (0x1<<1);
		NOP_10us_Delay(1000);
		
		temp_reg = SCCR;
		temp_reg	|= 0x01;
		
		SYSCON_AR = 0x5A;
		SCCR	= temp_reg;    
	}
}

/**
* @brief	Controls clock frequency selection and oscillator operation.
* @param    osc_sel 	This parameter contains the selection of Oscillator.
*
* 				     	- LSIRC  = 0
*				    	- HSIRC	 = 1
*							- XCLK   = 2
* @param    hsirc_div 	This parameter contains the Post-divider Selection of Internal RC Oscillator.
*
*							- HSI32_DIV2 		= 0
*							- HSI32_DIV4 		= 1
*							- HSI32_DIV8 		= 2
*							- HSI32_DIV32 	= 3
*							- LSI_DIV2 				= 4
*							- LSI_DIV4 				= 5
*							- LSI_DIV8 				= 6
*							- LSI_DIV16 			= 7
*
* @param    osc_enable	This parameter contains the enable of oscillator.
*
*               - OSC_DIS  = 0
*               - OSC_EN   = 1
* @return	None
*/
void Clock_ConfigureOSC(uint8_t osc_sel, uint8_t irc_div, uint8_t osc_enable)
{
	uint8_t temp_reg;
	
	if(osc_sel == LSIRC)
	{
			if(osc_enable == OSC_DIS)
			{
					/* Disable Low Frequency(256kHz) Internal RC OSC for system clock */
					SYSCON_AR = 0x5A;
					OSCCR &= ~(0x1 << 0);
			}
			else if(osc_enable == OSC_EN)
			{
					/* Enable Low Frequency(256kHz) Internal RC OSC for system clock */
					temp_reg = OSCCR;
					temp_reg |= (osc_enable << 0);
					
					temp_reg &= ~(0x3 << 6);
					temp_reg |= ((irc_div-4) << 6);
		
					SYSCON_AR = 0x5A;
					OSCCR = temp_reg;
			}            
			
	}
	else if(osc_sel == HSIRC)
	{
        if(osc_enable == OSC_DIS)
        {
            /* Disable High Frequency(32MHz) Internal RC OSC for system clock */
						SYSCON_AR = 0x5A;
            OSCCR &= ~(0x1 << 2);          
        }
        else if(osc_enable == OSC_EN)
        {
						temp_reg = OSCCR;
            /* Enable High Frequency(32MHz) Internal RC OSC for system clock */
            temp_reg |= (osc_enable << 2);
            
            temp_reg &= ~(0x3<<4);
            temp_reg |= (irc_div<<4);
			
						SYSCON_AR = 0x5A;
						OSCCR = temp_reg;
        }
 	}
	else if(osc_sel == XCLK)
	{
        if(osc_enable == OSC_DIS)
        {
            /* Disable External Main OSC for system clock */
						SYSCON_AR = 0x5A;
            OSCCR  &= ~(0x1 << 1);
        }
        else if(osc_enable == OSC_EN)
        {
						/* Input GPIO mode, Alternative Function for External Main OSC  */
						P1IO &= ~((0x1 << 1) | (0x1 << 0)); 
            
            /* Enable External Main OSC for system clock */
						SYSCON_AR = 0x5A;
            OSCCR  |= (osc_enable << 1);		           
        }
	}
}


/**
* @brief	Configure Stop release time for fast wakeup(fx = 16Mhz)
* @param    time_sel	This parameter contains the selection of time.(0~7)
* @return	None
*/
void Clock_ConfigureStopReleaseTime(uint8_t time_sel)
{
	uint8_t temp_reg;
	
	temp_reg = SCCR;
	temp_reg &= ~(0x7 << 4);
	temp_reg |= (time_sel << 4);

	SYSCON_AR = 0x5A;
	SCCR = temp_reg;
}

/**
* @brief	Configure Operating LSI(256kHz) at stop mode
* @param   enable   This parameter contains the enable of this function. 
*
*			- FALSE 	= 0
*			- TRUE 		= 1
* @return	None
*/
void Clock_ConfigureLSIOperateOnStop(uint8_t enable)
{
	uint8_t temp_reg;
	
	temp_reg = SCCR;
	temp_reg &= ~(0x1 << 2);
	temp_reg |= (enable << 2);

	SYSCON_AR = 0x5A;
	SCCR = temp_reg;
}

/**
* @brief		Get Systemclock frequency(speed)
* @param   None
* @return		The value of system clock(frequency)
*/
uint32_t Clock_GetSystemFreq(void)
{
	return SYSTEM_CLOCK;
}

/* --------------------------------- End Of File ------------------------------ */