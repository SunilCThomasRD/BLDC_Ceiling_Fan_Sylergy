#include	"A94B114.h"
#include	"func_def.h"
#include "flash.h"

extern volatile void do_flash_at_sram_src();

int count_500;

//unsigned char debug_SFR0;
//unsigned char debug_SFR1;
//unsigned char debug_SFR2;

//unsigned short	debug_count;
//unsigned short	debug_capture_buffer[20];

//bit stop_flag;
//bit debug_flag;

extern struct RemoteStatus RemoteData;

//------------------------------------------------------------------------------
//	C51: SOFTWARE RESET
void	reset (void)
{
	((void (code *) (void)) 0x0000) ();		// only support Keil C51 !!
}
//------------------------------------------------------------------------------

//#define	TEST_WRITE_SECTOR		7
extern long SleepTimerCounter_1hr,General_Counter;

unsigned char test_self_PGM()
{
	unsigned char		return_state;
	unsigned char		flash_sector_num;
	unsigned int		flash_memory_address;
	unsigned char idata test_flash_pattern [ PAGE_SIZE ];
	
	test_flash_pattern[0] = 0xAA;
	test_flash_pattern[1] = RemoteData.Power;
	test_flash_pattern[2] = RemoteData.Light;
	test_flash_pattern[3] = RemoteData.FanSpeed;
	test_flash_pattern[4] = RemoteData.Timer_Hrs;
	test_flash_pattern[5] = RemoteData.Sleep;
	test_flash_pattern[6] = (General_Counter & 0xFF);
	test_flash_pattern[7] = ((General_Counter>>8) & 0xFF);
	test_flash_pattern[8] = ((General_Counter>>16) & 0xFF);
	test_flash_pattern[9] = ((General_Counter>>24) & 0xFF);
	test_flash_pattern[10] = (SleepTimerCounter_1hr & 0xFF);
	test_flash_pattern[11] = ((SleepTimerCounter_1hr>>8) & 0xFF);
	test_flash_pattern[12] = ((SleepTimerCounter_1hr>>16) & 0xFF);
	test_flash_pattern[13] = ((SleepTimerCounter_1hr>>24) & 0xFF);
		
	//pAddr is the sector number ,A94B114 has 255 sectors(0 ~ 255).
	//the 255th sector,last 32 byte flash addr :0x1FE0~0x1FFF (8160~8192)
	flash_sector_num		= TEST_WRITE_SECTOR;
	flash_memory_address	= (flash_sector_num << 5 );
	
	return_state = Flash_Erase( flash_memory_address );
	if ( return_state != 0)	
	{ 
		return SELF_PGM_ERASE_ERROR;	
	}
	
	return_state = Flash_Write( flash_memory_address, test_flash_pattern );
	if ( return_state != 0)	
	{ 
		return SELF_PGM_VERIFY_ERROR;	
	}
	
	return SELF_PGM_OK;
}
//------------------------------------------------------------------------------
/*void MainFlash( void )
{
//------------------------------------------------------------------------------
//    interrupt select
//------------------------------------------------------------------------------
	debug_SFR0 = IRQ0;
	debug_SFR0 = IRQ1;
	debug_SFR0 = IRQ2;
	
	debug_count = 0;
	stop_flag = 0;
	debug_flag = 0;	
	EA = 1;

}*/


