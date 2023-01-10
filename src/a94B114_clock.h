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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CLOCK_H_
#define __CLOCK_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "a94b114.h"
#include "typedef.h"


/*******************************************************************************
* Public Macro
*******************************************************************************/
#define SYSTEM_CLOCK		16000000

/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum SystemClk { 
	HSI32_DIV2 = 0,
	HSI32_DIV4,
	HSI32_DIV8,
	HSI32_DIV32,  
	LSI_DIV2,
	LSI_DIV4,
	LSI_DIV8,
	LSI_DIV16,
	HSE,
};

enum OSCSel { 
    LSIRC = 0,
    HSIRC,
		XCLK,
};

enum OSCEnable { 
    OSC_DIS = 0,
    OSC_EN
};


/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void Clock_Initial(uint8_t clock_sel);
void Clock_ConfigureOSC(uint8_t osc_sel, uint8_t irc_div, uint8_t osc_enable);
void Clock_ConfigureStopReleaseTime(uint8_t time_sel);
void Clock_ConfigureLSIOperateOnStop(uint8_t enable);
uint32_t Clock_GetSystemFreq(void);
#endif  /* End of __CLOCK_H_ */
/* --------------------------------- End Of File ------------------------------ */