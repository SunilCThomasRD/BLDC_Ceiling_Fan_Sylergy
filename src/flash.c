#define FLASH_GLOBALS

#define		MyDef	extern


#include	"A94B114.h"
#include "flash.h"
#include	"func_def.h"

#define PGM_TIME 0x9D	// 2.5ms
#define NOP _nop_()

#define PAGEBUF_SIZE 32
#define coderom ((unsigned char volatile code  *) 0)
#define DUMMY_FLASH_ADDRESS	0x600			// Set a dummy write area within the protection zone.

#define	FLASH_WRITE_SECURITY_ID		0xF0
#define	FLASH_ERASE_SECURITY_ID		0xE0

// Do not change this define.
// code_buf, g_FEMR, g_FECR, g_WDTMR must be data area. (Do not define at xdata area or idata.)
volatile unsigned char data code_buf[20] _at_ 0x30;		// Lower 128bytes internal RAM. (GPR Address 0x30~0x7F)
volatile unsigned char data g_FEMR, g_FECR, g_WDTMR;
volatile unsigned char data g_IE, g_IE1, g_IE2;
//==============================================================================
// Sram-jump Program Routine.
//==============================================================================
// must execute in SRAM!, 0 ~ 0x11(code size : 18 byte)
// Do not change this routine.
volatile void write_page_buffer_src()		
{
    FEMR = FLASH_SEL                |   // FSEL (Select Flash memory)
           FLASH_PBUFF_SEL          |   // PBUFF (Select page buffer)
           FLASH_CON_ENABLE         ;   // FEEN (Enable program & erase)

	#pragma asm
		mov		r0,#32
		mov		dptr,#0x10E0	; page buffer address
    write_page_buffer_src_loop:
		mov		a, @r1
		movx	@dptr,a
		inc		r1
		inc		dptr        
		djnz	r0,write_page_buffer_src_loop
	#pragma endasm

    FEMR = 0;
}

// must execute in SRAM!, 0 ~ 0x0E(code size : 15 byte)
// Do not change this routine.
volatile void do_flash_at_sram_src()		
{
	#pragma	asm
		mov	FEMR,g_FEMR				// 3 byte
		mov	FECR,g_FECR				// 3 byte
	_flash_busy_wait:
		mov	A,FESR					// 2 byte
		JNB	ACC.7,_flash_busy_wait	// 3 byte
		clr	A						// 1 byte
		mov	FEMR,A					// 2 byte
	#pragma endasm
// C source
//     FEMR = g_FEMR;
//     FECR = g_FECR;
//     while( !(FESR & 0x80) );
//     FEMR = 0;
}	// RET // 1byte
//==============================================================================
void Flash_Enter()
{
	cli();				// Global Interrupt Disable
	g_IE = IE;
	g_IE1 = IE1;
	g_IE2 = IE2; 
	g_WDTMR = WDTMR;	// Backup WDTMR
	WDTMR	= 0;		// Watch Dog Timer Stop.
	g_WDTMR |= 0x04;	// Clear WDT Counter
	
	// To access Flash Control register, ENTRY_0~2 should be set 0xAA, 0x55, 0xA5.
	*(unsigned char xdata *)0x10D8 = 0xAA;
    *(unsigned char xdata *)0x10DA = 0x55;
    *(unsigned char xdata *)0x10DD = 0xA5;
	
	FEARL = (unsigned char)( DUMMY_FLASH_ADDRESS & 0xff);
	FEARM = (unsigned char)(( DUMMY_FLASH_ADDRESS >> 8) & 0xff);
	FEARH = 0;
	
}

void Flash_Exit()
{
	FECR = FLASH_MODE_EXIT;
	
	FEARL = (unsigned char)( DUMMY_FLASH_ADDRESS & 0xff);
	FEARM = (unsigned char)(( DUMMY_FLASH_ADDRESS >> 8) & 0xff);
	FEARH = 0;
	
	// After to change Flash Control register, ENTRY_0~2 should be set 0x00.
	*(unsigned char xdata *)0x10D8 = 0x00;
    *(unsigned char xdata *)0x10DA = 0x00;
    *(unsigned char xdata *)0x10DD = 0x00;
	
	// Flash code buffer ram clear.
#pragma asm
	mov		r0, #code_buf
	mov		r2, #20
	clr		a
loop0:
	mov		@r0, a
	inc		r0
	djnz	r2, loop0
#pragma endasm

	WDTMR	= g_WDTMR;	// Restore WDTMR
	 IE = g_IE;
	IE1 = g_IE1;
	IE2 = g_IE2; 
	sei();				// Global Interrupt Enable
}


void write_page_buffer(unsigned char *dt)	// dt -> r3, r2, r1	
{
	unsigned char *temp = dt;
	
    #pragma asm
		mov		dptr,#write_page_buffer_src
		mov		r0,#0x30
        mov		r2,#0x12
	write_page_buffer_loop:
		clr		a
		movc	a,@a+dptr
		mov		@r0,a
		inc		dptr
		inc		r0
		djnz	r2,write_page_buffer_loop
        ljmp	0x8030		; jump sram region
    #pragma endasm
}

#if 0
void do_flash_at_sram()
{
    #pragma asm
		mov		dptr,#do_flash_at_sram_src
		mov		r0,#0x30
		mov		r1,#0x0F
	do_flash_at_sram_loop:
		clr		a
		movc	a,@a+dptr
		mov		@r0,a
		inc		dptr
		inc		r0
		djnz	r1,do_flash_at_sram_loop
		ljmp	0x8030
    #pragma endasm
}
#else
void do_flash_at_sram()
{
	unsigned char code *ptr;		//need to add "code"
	unsigned char temp=0, i;

	ptr=(unsigned char code*)do_flash_at_sram_src;
	//temp=sizeof(int);
	for(i=0; i<15;i++)	//**size of "do_flash_at_sram_src" is less than 32.
	{
		code_buf[i]=ptr[i];
	}
//	ljmp_code_buf();		//Jump 0x8030
	#pragma asm
		ljmp	0x8030		;FLASH Writing Start
	#pragma endasm
	
}
#endif
char Flash_Erase(unsigned int addr)
{
	unsigned int i;
	unsigned char flash_state_id = FLASH_ERASE_SECURITY_ID;
	
	// Flash Flash Control Register CLR change before initialization.
	FECR	= 0;
	FETCR	= 0;
	FEMR	= 0; 
	
	// Enable program mode
	Flash_Enter();

	FETCR = PGM_TIME;				// 0x9D = 157 : (157+1) * 2 (31.25ns * 256) = 2.528ms
	FECR = FLASH_PBUFF_RESET;

	g_FEMR = FLASH_SEL				|
		   FLASH_ERASE_MODE 		|
		   FLASH_CON_ENABLE 		;

	g_FECR = FLASH_START_ERASE_PGM	;
	
	FEARL = (unsigned char)(addr&0xff);
	FEARM = (unsigned char)((addr>>8)&0xff);
	FEARH = 0;
	
	if(flash_state_id != FLASH_ERASE_SECURITY_ID)
	{
		Flash_Exit();
		WDTMR = 0;			// If Flash ID fail, may be WDTMR value error.
		
		return -1;
	}
	
	do_flash_at_sram();
 
	Flash_Exit();
	
	// read data  
	for(i=0; i<PAGEBUF_SIZE;i++){	// Read flash data.
		if(coderom[addr] != 0x00) 
      		return -1;

		addr++;
	}
	return 0;
}

char Flash_Write(unsigned int addr, unsigned char *dt)
{
	unsigned int i;
	unsigned char *pdt;
	unsigned char flash_state_id = FLASH_WRITE_SECURITY_ID;
	
	// Enable program mode
	Flash_Enter();
	
	FETCR = PGM_TIME;				// 0x9D = 157 : (157+1) * 2 (31.25ns * 256) = 2.528ms

    // 0x81
    FEMR = FLASH_SEL                | // FSEL (Select Flash memory)
           FLASH_CON_ENABLE         ; // FEEN (Enable program & erase of Flash)

    // 
    FECR = FLASH_PBUFF_RESET        ; // PBRSTB (Reset page buffer)

	FEARL = (unsigned char)(addr&0xff);
	FEARM = (unsigned char)((addr>>8)&0xff);
	FEARH = 0x00;

    write_page_buffer(dt);

   // 0xA1
    g_FEMR = FLASH_SEL         |		// FSEL (Select Flash memory)
             FLASH_PGM_MODE    |		// PGM (Enable program or verify mode with VFY)
             FLASH_CON_ENABLE;			// FEEN (Enable program & erase of Flash)

    // 0x0B
    g_FECR = FLASH_START_ERASE_PGM;		// WRITE (Start program or erase)
										// FERSTB (Reset Flash and EEPROM)
										// PBRSTB (Reset page buffer)
	
	if(flash_state_id != FLASH_WRITE_SECURITY_ID)
	{
		Flash_Exit();
		WDTMR = 0;						// If Flash ID fail, may be WDTMR value error.
		
		return -1;
	}
	
    do_flash_at_sram();
 
	Flash_Exit();
	
	// read data
	pdt = dt;
	for(i=0;i<PAGEBUF_SIZE;i++)		// Read flash data.
	{	
		if (coderom[addr]!=*pdt) 
	  		return -2;
		
		addr++;
		pdt++;
	}
	
	return 0;
}

char Flash_Read(unsigned int addr, unsigned char *dt, unsigned char length)
{
	unsigned int i;
	unsigned char *pdt;
	
	// read data
	pdt = dt;
	for(i=addr; i<(addr+length); i++)	// Read flash data.
	{
		*pdt = coderom[i];
		pdt++;
	}
	
	return 0;
}

