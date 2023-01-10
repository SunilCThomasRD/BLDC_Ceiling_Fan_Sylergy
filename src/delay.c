/***************************************************************************//**
*   @file       delay.c
*   @brief      Polling Delay subroutine
*   @author     V&V Team, ABOV Semiconductor Co., Ltd.
*   @version    V1.00
*   @date       28. NOV. 2019
*
* Copyright(C) 2019, ABOV Semiconductor
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

/* Includes ------------------------------------------------------------------*/
#include    "typedef.h"
#include    "Intrins.h"
#include    "delay.h"       //
/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
/* Private Function Prototype ------------------------------------------------*/
/* Public Variable -----------------------------------------------------------*/
/* Public Function -----------------------------------------------------------*/
/***************************************************************************//**
* @brief    System NOP 1us Delay rountine. (MCLK = 16MHZ)
* @note     1 machine cycle comprises 1 system clock cycles. (@ABOV 94 Core Serise)
*           16 system clock delay
* @param    None
* @return   None
*******************************************************************************/
volatile void NOP_1us_Delay(void)
{
    // ACALL, LCALL : 4, 2 cycle => 4, 2 system clock cycle
    NOP; NOP; NOP; 
	NOP; NOP; NOP;    // NOP : 1 cycle => 1 sys. clock => 6 sys. clk
    // RET : 4 cycle => 4 system clock cycle
    // 16 sys. clk @16MHZ = 62.5ns x 16 = 1us
}
/***************************************************************************//**
* @brief    System NOP 10us Delay rountine. (MCLK = 16MHZ)
* @note     1 machine cycle comprises 1 system clock cycles. (@ABOV 94 Core Serise)
*           160 system clock delay
*           1 machine cycle can be added depending on code optimization.
*
*           ex1)    MOV R7,#(Low byte of delay)
*                   MOV R6,#(high byte of delay)
*                   LCALL   NOP_10us_Delay
*
*           ex2)    MOV A,#(Low byte of delay) // Lower byte and higher byte are the same.
*                   MOV R7,A
*                   MOV R6,A
*                   LCALL   NOP_10us_Delay
*
* @param    delay : unsigned int 1~65,355 (delay) * 10us (@System clock = 16Mhz)
* @return   None
*******************************************************************************/
volatile void NOP_10us_Delay(unsigned int delay)
{
	NOP_1us_Delay();
	NOP_1us_Delay();
	NOP_1us_Delay();
	NOP_1us_Delay();
	NOP_1us_Delay();
	NOP_1us_Delay();
	NOP_1us_Delay();
	NOP_1us_Delay();
	NOP_1us_Delay();
	NOP_1us_Delay();
//    // mov r7 <- low byte of delay      // 1cycle
//    // mov r6 <- high byte of delay     // 1cycle
//    // lcall NOP_10us_Delay             // 2cycle
//    
//    // dummy assignment to avoid warning
//    // 'unreferenced local variable'
//    // Reference Link : http://www.keil.com/support/docs/2622.htm
//    // delay -> [r6:r7]
//    
//    delay = delay;  // dummy
//                    
//    #pragma asm
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//		
//		nop
//        nop
//		nop
//        nop
//        nop
//        nop
//        nop
//        nop
//        nop     //add 9cycle
//        clr     c                           // 1cycle
//        mov     a,r7                        // 1cycle
//        subb    a,#2                        // 1cycle
//        mov     r7,a                        // 1cycle
//        mov     a,r6                        // 1cycle
//        subb    a,#0                        // 1cycle
//        mov     r6,a                        // 1cycle
//        jc     _nop_10us_delay_loop_end     // 2cycle
//        
//    _nop_10us_delay_loop:
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//        lcall   NOP_1us_Delay
//		
//		lcall   NOP_1us_Delay
//        nop
//        nop
//        nop
//        nop
//        nop
//        nop
//        nop
//		nop
//        nop
//        nop
//        nop
//        nop
//        
//        clr     c                           // 1cycle
//        mov     a,r7                        // 1cycle
//        subb    a,#1                        // 1cycle
//        mov     r7,a                        // 1cycle
//        mov     a,r6                        // 1cycle
//        subb    a,#0                        // 1cycle
//        mov     r6,a                        // 1cycle
//        jnc     _nop_10us_delay_loop        // 2cycle

//    _nop_10us_delay_loop_end:
//        nop                                 // 1cycle
//		nop
//		nop
//		nop
//        
//    #pragma endasm
//                                            // ret 2cycle
}

/* --------------------------------- End Of File ------------------------------ */
