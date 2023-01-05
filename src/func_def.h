
#define KEY1		0x30CF2AD5									//POWER
#define KEY2		0x1B7EE01F										//LIGHT
#define KEY3		0x30CFAA55										// FAN SPEED 1
#define KEY4		0x30CF6A95										// FAN SPEED 2
#define KEY5		0x30CFEA15										// FAN SPEED 3
#define KEY6		0x30CF1AE5										// FAN SPEED 4
#define KEY7		0x30CF9A65										// FAN SPEED 5
#define KEY8		0x1B7EA857										// FAN SPEED 6
#define KEY9		/*0x00FF6996*/ 0x1B7EC837			// BOOST
#define KEY10		0x30CF5AA5										// TIMER 2H
#define KEY11		0x30CFDA25										// TIMER 4H
#define KEY12		0x30CF3AC5										// TIMER 8H
#define KEY13		0x1B7E48B7										// REVERSE
#define KEY14		0x30CFFA05 										// SMART / SLEEP
								

#define POWER					0x0E
#define LIGHT					0x01
#define FAN_SPEED_1		0x02
#define FAN_SPEED_2		0x03
#define FAN_SPEED_3		0x04
#define FAN_SPEED_4		0x05
#define FAN_SPEED_5		0x06
#define FAN_SPEED_6		0x07
#define BOOST					0x08
#define TIME_2HRS			0x09
#define TIME_4HRS			0x0A
#define TIME_8HRS			0x0B
#define REVERSE_MODE	0x0F
#define SLEEP_MODE		0x0C
#define GARBAGE_DATA_RECEIVED		0x0D

#define REMOTE_TIMER_OFF		0x00
#define REMOTE_TIMER_2HRS		0x01
#define REMOTE_TIMER_4HRS		0x02
#define REMOTE_TIMER_6HRS		0x03
#define REMOTE_TIMER_8HRS		0x04


#define LED_OFF 				P0 |= 0x20
#define LED_ON		 			P0 &= ~(0x20)

#define ADC_SAMPLES 					50

#define FAN_LOAD_UNHEALTHY_VALUE			210// 41W Sense - 40W OK 
#define FAN_LOAD_HEALTHY_VALUE				185 // OK 36W
#define FAN_LOAD_HYSTERSIS_VALUE			170 // 34-35W OK OK
#define FAN_LOAD_UNHELATHY_STABLIZING_TIME 	25   // 250*20ms = 5sec


#define SLEEP_ONE_HOUR_TIMER1_VALUE		7200
#define TIMER_5_MINUTES		600

#define FAN_OFF_VALUE					0
#define FAN_SPEED1_VALUE			100
#define FAN_SPEED2_VALUE			120
#define FAN_SPEED3_VALUE			150
#define FAN_SPEED4_VALUE			170
#define FAN_SPEED5_VALUE			203// 225- 32W Final // 337 RPM  //205 - 33W -34W Hunt 
#define FAN_SPEED6_VALUE			185 // 333 RPM
#define FAN_BOOST_VALUE				203

//======================================================
// Function and global variables definition
//======================================================

void port_init();             	// initialize ports
void clock_init();            	// initialize operation clock
void ExINT_init();            	// initialize external interrupt
void Timer0_init();           	// initialize Timer0
void Timer1_init();           	// initialize Timer1
void Timer2_init();           	// initialize Timer2
void ADC_init(void);
void ADC_start(unsigned char ch);
void Fan_load_Line_Monitor(void);
unsigned char test_self_PGM();

void LVI_init();              	// initialize LVI, LVR
void LVI_De_init();


void fanSpeed1(void);
void fanSpeed2(void);
void fanSpeed3(void);
void fanSpeed4(void);
void fanSpeed5(void);
void fanSpeed6(void);
void fanSpeed_BOOST(void);
void Timer_Disable(void);
void i2c_speed(unsigned char);

void fan_power_on(void);
void fan_power_off(void);
void Timer_Hrs_process(unsigned char);
void process(void);
void SleepOperation(void);
void SystemInitialization(void);
void Fan_Reverse_Funct(void);

#define cli()		(EA = 0)
#define sei()		(EA = 1)

#define	NOP		_nop_()

#define NOP_COUNT 500

void	Nop_1us_16Mhz(void);
void	wait_100uSec(unsigned int delay);

extern void          _nop_     (void);


#define	PAGE_SIZE				32
#define	SELF_PGM_OK				0
#define	SELF_PGM_ERASE_ERROR	1
#define	SELF_PGM_VERIFY_ERROR	2

#define	TEST_WRITE_ADDRESS		0x1fe0
#define	TEST_WRITE_SECTOR		TEST_WRITE_ADDRESS/32


unsigned char RemoteGetKeyProcess(long);

struct RemoteStatus
{
	unsigned int Power :1;
	unsigned int Light :1;
	unsigned int FanSpeed :3;
	unsigned int Timer_Hrs :3;
	unsigned int Sleep :1;
};