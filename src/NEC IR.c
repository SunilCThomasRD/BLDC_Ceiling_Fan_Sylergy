#include	"A94B114.h"
#include	"func_def.h"

unsigned char RemoteGetKeyProcess(long value)
{
	unsigned char ADDH,ADDL,DATAH,DATAL;
	ADDH = (long)(value>>24)&0xFF;
	ADDL = (long)(value>>16)&0xFF;
	DATAH = (long)(value>>8)&0xFF;
	DATAL = value&0xFF;
	if((DATAH ^ DATAL) != 0xFF)
	{
		return(GARBAGE_DATA_RECEIVED);
	}
	switch(value)
	{
		case KEY1:
			//OPERATION
			return(POWER);
			break;
		case KEY2:
			//OPERATION
			return(LIGHT);
			break;
		case KEY3:
			//OPERATION
			return(FAN_SPEED_1);
			break;
		case KEY4:
			//OPERATION
			return(FAN_SPEED_2);
			break;
		case KEY5:
			//OPERATION
			return(FAN_SPEED_3);
			break;
		case KEY6:
			//OPERATION
			return(FAN_SPEED_4);
			break;
		case KEY7:
			//OPERATION
			return(FAN_SPEED_5);
			break;
		case KEY8:
			//OPERATION
			return(FAN_SPEED_6);
			break;
		case KEY9:
			//OPERATION
			return(BOOST);
			break;
		case KEY10:
			//OPERATION
			return(TIME_2HRS);
			break;
		case KEY11:
			//OPERATION
			return(TIME_4HRS);
			break;
		case KEY12:
			//OPERATION
			return(TIME_8HRS);
			break;
		case KEY13:
			//OPERATION
			return(REVERSE_MODE);
			break;
		case KEY14:
			//OPERATION
			return(SLEEP_MODE);
			break;
		default:
			//opearation
			return(GARBAGE_DATA_RECEIVED);
	}		
}