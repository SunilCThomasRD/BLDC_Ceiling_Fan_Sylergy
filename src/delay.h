/***************************************************************************//**
*   @file       delay.h
*   @brief      Polling delay header file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ABOV96_CORE_DELAY_H_
#define __ABOV96_CORE_DELAY_H_
/* Includes ------------------------------------------------------------------*/

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
/* Private Function Prototype ------------------------------------------------*/
/* Public Variable -----------------------------------------------------------*/
/* Public Function -----------------------------------------------------------*/

//------------------------------------------------------------------------------

volatile void NOP_1us_Delay(void);
volatile void NOP_10us_Delay(unsigned int delay);

#endif  /* End of __ABOV96_CORE_DELAY_H */
/* --------------------------------- End Of File ------------------------------ */
