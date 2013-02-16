#include "key.h"

const uint8_t lengths[] = { 5,//0
5,//1
5,//2
5,//3
5,//4
5,//5
5,//6
5,//7
5,//8
5,//9
2,//a
4,//b
4,//c
3,//d
1,//e
3,//f
3,//g
5,//h
2,//i
4,//j
3,//k
4,//l
2,//m
2,//n
3,//o
4,//p
4,//q
3,//r
3,//s
1,//t
3,//u
4,//v
3,//w
4,//x
4,//y
4//z
};

const uint8_t ditdah[36]= { 0x1F,//0
0x1E,//1
0x1C,//2
0x18,//3
0x10,//4
0x00,//5
0x01,//6
0x03,//7
0x07,//8
0x0F,//9
0x02,//a
0x01,//b
0x05,//c
0x01,//d
0x00,//e
0x04,//f
0x03,//g
0x00,//h
0x00,//i
0x0E,//j
0x05,//k
0x02,//l
0x03,//m
0x01,//n
0x07,//o
0x06,//p
0x0B,//q
0x02,//r
0x00,//s
0x01,//t
0x04,//u
0x08,//v
0x06,//w
0x09,//x
0x0D,//y
0x03//z
};


void initMorseCounter(void)
{
}

void startCounter(void)
{
}

void stopCounter(void)
{
}

void delay(int press)
{
	int i;
	for (i = 0; i< press; ++i)
	{
		cli();
		sleep_enable();
		// set sleep mode
		resetTimer();
		set_sleep_mode(SLEEP_MODE_IDLE);
		sei();
		// do the sleep thing
		sleep_cpu();
		sleep_disable();
	}
}

void deepSleep( void )
{
	int i;
	cli();
	sleep_enable();
	set_sleep_mode(SLEEP_MODE_EXT_STANDBY);
	sei();
	for (i=0;i<10;i++)
	{
		sleep_cpu();
	}
	sleep_disable();
}

void sendChar(unsigned char morseCh)
{
	int i;

	for (i =0;i<lengths[morseCh];++i)
	{
		MORSEPORT &= !MORSEPIN;
		delay((ditdah[morseCh] & (1<<i))?3:1);
		MORSEPORT |= MORSEPIN;
		delay(1);
	}
}

void charSpace(void)
{
	MORSEPORT |= MORSEPIN;
	delay(2); // should wait 3, we already waited 1
}

void space(void)
{
	MORSEPORT |= MORSEPIN;
	delay(6); // same as above, but with 7
}
