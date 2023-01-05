//==========================================================
//	
//	A94B114 Special Function Register Address define
//	
//==========================================================

//----------------------------------------------------- 0x80
sfr     P0          =   0x80;
sbit    P07         =   0x87;
sbit   	P06	        =   0x86;
sbit   	P05	        =   0x85;
sbit   	P04	        =   0x84;
sbit   	P03	        =   0x83;
sbit   	P02	        =   0x82;
sbit   	P01	        =   0x81;
sbit   	P00	        =   0x80;

sfr     SP	        =   0x81;
sfr16	DPTR0       =   0x82;
sfr     DPL	        =   0x82;
sfr     DPH	        =   0x83;
sfr16	DPTR1       =   0x82;
sfr     DPL1        =   0x82;
sfr     DPH1        =   0x83;
sfr     DBTSR       =   0x84;
sfr     BITCNT      =   0x85;
sfr     BITCR       =   0x86;
sfr     PCON        =   0x87;
//----------------------------------------------------- 0x88
sfr     P1	        =   0x88;
sbit   	P15	        =   0x8D;
sbit   	P14	        =   0x8C;
sbit   	P13	        =   0x8B;
sbit   	P12	        =   0x8A;
sbit   	P11         =   0x89;
sbit   	P10	        =   0x88;

sfr     LVIR        =   0x89;
sfr     IOFFSET     =   0x8A;
sfr     EIPOL0      =   0x8B;
sfr     EIPOL1      =   0x8C;
sfr     WDTMR       =   0x8D;
sfr     WDTR        =   0x8E;
sfr     WDTCR       =   0x8E;
sfr     SYSCON_AR   =   0x8F;
//----------------------------------------------------- 0x90
sfr     P2	        =   0x90;
sbit   	P23	        =   0x93;
sbit   	P22	        =   0x92;
sbit   	P21         =   0x91;
sbit   	P20	        =   0x90;

sfr     T0CR        =   0x92;
sfr     T0CNT       =   0x93;
sfr     T0DR        =   0x94;
sfr     T0CDR       =   0x94;
sfr     ADCM        =   0x95;
sfr     ADCM1       =   0x96;
sfr16   ADCR        =   0x96;
sfr     ADCRL       =   0x96;
sfr     ADCRH       =   0x97;
//----------------------------------------------------- 0x98
sfr     RSFR        =   0x98;
sfr     ILVL        =   0x9A;
sfr     P0IO        =   0x9B;
sfr     P0PU        =   0x9C;
sfr     P0OD        =   0x9D;
sfr     P0DB        =   0x9E;
//----------------------------------------------------- 0xA0
sfr     IRQ0        =   0xA0;
sbit   	CMP_INT_F   =   0xA0;		// Comparator Interrput FLAG
sbit   	EIN10_INT_F =   0xA1;		// External Interrupt 10 FLAG
sbit   	EIN11_INT_F =   0xA2;		// External Interrupt 11 FLAG
sbit   	EIN12_INT_F =   0xA3;		// External Interrupt 12 FLAG
sbit   	EINT_INT_F  =   0xA4;		// External Interrupt 0~2 FLAG

sfr     EO          =   0xA2;
sfr     P1IO        =   0xA3;
sfr     P1PU        =   0xA4;
sfr     P1OD        =   0xA5;
sfr     P1DB        =   0xA6;
//----------------------------------------------------- 0xA8
sfr     IRQ1        =   0xA8;
sbit   	I2C_INT_F   =   0xA8;		// I2C Interrupt FLAG
sbit   	UART_RX_INT_F =   0xA9;		// UART RX Interrupt FLAG
sbit   	UART_TX_INT_F =   0xAA;		// UART TX Interrupt FLAG

sbit   	T0_INT_F    =   0xAC;		// T0 Interrupt FLAG
sbit   	T1_INT_F    =   0xAD;		// T1 Interrupt FLAG
sbit   	T2_INT_F    =   0xAE;		// T2 Interrupt FLAG

sfr   	LDOCR       =   0xAA;
sfr     P2IO        =   0xAB;
sfr     P2PU        =   0xAC;
sfr     P2OD        =   0xAD;
sfr     P2DB        =   0xAE;
//----------------------------------------------------- 0xB0
sfr     IRQ2        =   0xB0;
sbit   	ADC_INT_F   =   0xB0;		// ADC Interrupt FLAG
sbit   	WDT_INT_F   =   0xB1;		// WDT Interrupt FLAG
sbit   	BIT_INT_F   =   0xB2;		// BIT Interrupt FLAG
sbit   	LVI_INT_F   =   0xB3;		// LVI Interrupt FLAG

sfr     CMX         =   0xB2;
sfr16   P0FSR       =   0xB3;
sfr     P0FSRL      =   0xB3;
sfr     P0FSRH      =   0xB4;
sfr16   P1FSR       =   0xB5;
sfr     P1FSRL      =   0xB5;
sfr     P1FSRH      =   0xB6;
sfr     P2FSR       =   0xB7;
//----------------------------------------------------- 0xB8
sfr     IE          =   0xB8;
sbit   	CMP_INT_EN	=   0xB8;		// Comparator Interrput Enable
sbit   	EINT10_INT_EN =   0xB9;		// External Interrupt 10 Enable
sbit   	EINT11_INT_EN =   0xBA;		// External Interrupt 11 Enable
sbit   	EINT12_INT_EN =   0xBB;		// External Interrupt 12 Enable
sbit   	EINT_INT_EN  =   0xBC;		// External Interrupt 0~2 Enable
sbit   	EA      	=   0xBF;		// Grobal Interrupt Enable

sfr16   T1CR        =   0xBA;
sfr     T1CRL       =   0xBA;
sfr     T1CRH       =   0xBB;
sfr16   T1ADR       =   0xBC;
sfr     T1ADRL      =   0xBC;
sfr     T1ADRH      =   0xBD;
sfr16   T1BDR       =   0xBE;
sfr     T1BDRL      =   0xBE;
sfr     T1BDRH      =   0xBF;
//----------------------------------------------------- 0xC0
sfr     IE1         =   0xC0;
sbit   	I2C_INT_EN  =   0xC0;		// I2C Interrupt Enable
sbit   	UART_RX_INT_EN =   0xC1;	// UART RX Interrupt Enable
sbit   	UART_TX_INT_EN =   0xC2;	// UART TX Interrupt Enable
sbit   	T0_INT_EN   =   0xC4;		// T0 Interrupt Enable
sbit   	T1_INT_EN   =   0xC5;		// T1 Interrupt Enable
sbit   	T2_INT_EN   =   0xC6;		// T2 Interrupt Enable

sfr16   T2CR        =   0xC2;
sfr     T2CRL       =   0xC2;
sfr     T2CRH       =   0xC3;
sfr16   T2ADR       =   0xC4;
sfr     T2ADRL      =   0xC4;
sfr     T2ADRH      =   0xC5;
sfr16   T2BDR       =   0xC6;
sfr     T2BDRL      =   0xC6;
sfr     T2BDRH      =   0xC7;
//----------------------------------------------------- 0xC8
sfr     IE2         =   0xC8;
sbit   	ADC_INT_EN  =   0xC8;		// ADC Interrupt Enable
sbit   	WDT_INT_EN  =   0xC9;		// WDT Interrupt Enable
sbit   	BIT_INT_EN  =   0xCA;		// BIT Interrupt Enable
sbit   	LVI_INT_EN  =   0xCB;		// LVI Interrupt Enable

sfr     EIFLAG      =   0xC9;
sfr16   T1CDR       =   0xCC;
sfr     T1CDRL      =   0xCC;
sfr     T1CDRH      =   0xCD;
sfr16   T1DDR       =   0xCE;
sfr     T1DDRL      =   0xCE;
sfr     T1DDRH      =   0xCF;
//----------------------------------------------------- 0xD0
sfr     PSW	        =   0xD0;
sbit    CY 	        =   0xD7;
sbit    AC 	        =   0xD6;
sbit    F0          =   0xD5;
sbit    RS1	        =   0xD4;
sbit    RS0	        =   0xD3;
sbit    OV 	        =   0xD2;
sbit    F1          =   0xD1;
sbit    P  	        =   0xD0;

sfr16   TEST        =   0xD1;
sfr     TESTL       =   0xD1;
sfr     TESTH       =   0xD2;
sfr     TDISR       =   0xD3;
sfr     DMY_REFA    =   0xD4;
sfr     DMY_REFB    =   0xD5;
sfr     CMPCR       =   0xD6;
sfr     CMPTR       =   0xD7;
//----------------------------------------------------- 0xD8
sfr     OSCCR       =   0xD8;
sfr     SCCR        =   0xD9;
sfr     CMPDBT      =   0xDE;
sfr     XBANK       =   0xDF;
//----------------------------------------------------- 0xE0
sfr     ACC	        =   0xE0;
sfr     UCTRL1      =   0xE1;	// USART	R/W 8'b0000_0000	USART Control Register 1
sfr     UCTRL2      =   0xE2;	// USART	R/W 8'b0000_0000	USART Control Register 2
sfr     UCTRL3      =   0xE3;	// USART	R/W 8'b0000_0000	USART Control Register 3
sfr     USTAT       =   0xE4;	// USART	R/W 8'b1000_0000	USART Status Register
sfr     UBAUD       =   0xE5;	// USART	R/W 8'b1111_1111	USART BaudRate Register
sfr     UDATA       =   0xE6;	// USART	R/W 8'b0000_0000	USART Data Register
//----------------------------------------------------- 0xE8
sfr     IP          =   0xE8;
sfr     IP1         =   0xE9;
sfr     IP2         =   0xEA;

sfr     UCTRL4      =   0xEB;   // USART	R/W 8'b0000_0000	USART Control Register 4
sfr     FPCR        =   0xEC;   // USART	R/W 8'b0000_0000	USART Floating Point Register
//----------------------------------------------------- 0xF0
sfr     B           =   0xF0;
//----------------------------------------------------- 0xF8
sfr     I2CSR       =   0xF8;	// I2C Status Register
sfr     I2CMR       =   0xF9;	// I2C Mode Control Register
sfr     I2CSCLLR    =   0xFA;	// I2C SCL Low Period Register 
sfr     I2CSCLHR    =   0xFB;	// I2C SCL High Period Register
sfr     I2CSDHR     =   0xFC;	// I2C SDA Hold Register
sfr     I2CDR       =   0xFD;	// I2C Data Register
sfr     I2CSAR      =   0xFE;	// I2C Slave Address Register  
sfr     I2CSAR1     =   0xFF;	// I2C Slave Address Register 1  
// //----------------------------------------------------- //
// Flash and EEPROM Memory REGISTER                        //
// //----------------------------------------------------- //
sfr     FEMR        =   0xF1; // Flash and EEPROM mode register          
sfr     FECR        =   0xF2; // Flash and EEPROM control register       
sfr     FESR        =   0xF3; // Flash and EEPROM status register        
sfr     FETCR       =   0xF4; // Flash and EEPROM time control register  
sfr     FEARL       =   0xF5; // Flash and EEPROM address register low   
sfr     FEARM       =   0xF6; // Flash and EEPROM address register middle
sfr     FEARH       =   0xF7; // Flash and EEPROM address register high  
sfr     FEDR        =   0xEF; // Flash and EEPROM data register  
sfr     FETR        =   0xE7; // Flash and EEPROM TEST register  
// ==================================================================== //
// Flash and EEPROM Memory REGISTER                                     //
// ==================================================================== //
// (0xF1) FEMR;              // FECON        Flash and EEPROM mode register
#define FLASH_SEL               (0x80)
#define FLASH_PGM_MODE          (0x20)
#define FLASH_ERASE_MODE        (0x10)
#define FLASH_PBUFF_SEL         (0x08)
#define FLASH_OTPE_SEL          (0x04)
#define FLASH_VERFY_MODE        (0x02)          // self verify mode
#define FLASH_CON_ENABLE        (0x01)

// (0xF2) FECR;              // FECON        Flash and EEPROM control register
#define FLASH_BULK_ERASE        (0x80 | 0x03)
#define FLASH_MODE_EXIT         (0x30 | 0x03)
#define FLASH_START_ERASE_PGM   (0x08 | 0x03)
#define FLASH_START_READ        (0x04 | 0x03)
#define FLASH_RESET             (0x01)
#define FLASH_PBUFF_RESET       (0x02)
#define FLASH_FECR_INIT         (0x03)

// (0xF3) FESR;              // FECON        Flash and EEPROM status register
#define FLASH_BUSY              (0x80)
#define FLASH_VERIFY_OK         (0x40)
#define FLASH_CRC_MODE          (0x20)
#define FLASH_MWAIT_EN          (0x10)
#define FLASH_IRQ               (0x08)
#define FLASH_ST_PGM_MODE       (0x04)
#define FLASH_ST_ERASE_MODE     (0x02)
#define FLASH_ST_VERIFY_MODE    (0x01)

// (0xE7) FETR;              // FECON        Flash and EEPROM test register
#define FLASH_LOCK_DISABLE      (0x80)
#define FLASH_VPP_OUT_ENABLE    (0x60)
#define FLASH_FULL_READ         (0x08)
#define FLASH_PAGE_READ         (0x00)
#define FLASH_X_FAST            (0x04)
#define FLASH_Y_FAST            (0x00)
#define FLASH_EVEN_ENABLE       (0x02)
#define FLASH_ODD_ENABLE        (0x01)
#define FLASH_VMARGIN_ENABLE    (0x01)


// Interrupt vectors of A94B114
#define CMP_VECT		0		// IE.0
#define EINT10_VECT		1		// IE.1
#define EINT11_VECT		2		// IE.2
#define EINT12_VECT		3		// IE.3
#define EINT_VECT		4		// IE.4

#define I2C_VECT		5		// IE1.0
#define USART_RX_VECT	6		// IE1.1
#define USART_TX_VECT	7		// IE1.2
#define TIMER0_VECT 	9		// IE1.4
#define TIMER1_VECT 	10		// IE1.5
#define TIMER2_VECT 	11		// IE1.6

#define ADC_VECT		12		// IE2.0
#define WDT_VECT		13		// IE2.1
#define BIT_VECT		14		// IE2.2
#define LVI_VECT		15		// IE2.3

// Interrupt en/dis control
#define cmpint_en()		(CMP_INT_EN = 1)
#define eint10_en()		(EINT10_INT_EN = 1)
#define eint11_en()		(EINT11_INT_EN = 1)
#define eint12_en()		(EINT12_INT_EN = 1)
#define eint_en()		(EINT_INT_EN = 1)

#define i2cint_en()		(I2C_INT_EN = 1)
#define uartrxint_en()	(UART_RX_INT_EN = 1)
#define uarttxint_en()	(UART_TX_INT_EN = 1)
#define t0int_en()		(T0_INT_EN = 1)
#define t1int_en()		(T1_INT_EN = 1)
#define t2int_en()		(T2_INT_EN = 1)

#define adcint_en()		(ADC_INT_EN = 1)
#define wdtint_en()		(WDT_INT_EN = 1)
#define bitint_en()		(BIT_INT_EN = 1)
#define lviint_en()		(LVI_INT_EN = 1)

#define cmpint_dis()	(CMP_INT_EN = 0)
#define eint10_dis()	(EINT10_INT_EN = 0)
#define eint11_dis()	(EINT11_INT_EN = 0)
#define eint12_dis()	(EINT12_INT_EN = 0)
#define eint_dis()		(EINT_INT_EN = 0)

#define i2cint_dis()	(I2C_INT_EN = 0)
#define uartrxint_dis()	(UART_RX_INT_EN = 0)
#define uarttxint_dis()	(UART_TX_INT_EN = 0)
#define t0int_dis()		(T0_INT_EN = 0)
#define t1int_dis()		(T1_INT_EN = 0)
#define t2int_dis()		(T2_INT_EN = 0)

#define adcint_dis()	(ADC_INT_EN = 0)
#define wdtint_dis()	(WDT_INT_EN = 0)
#define bitint_dis()	(BIT_INT_EN = 0)
#define lviint_dis()	(LVI_INT_EN = 0)
// ==================================================================== //