#include <avr/io.h>
#include <avr/sleep.h>
#include "globals.h"
#include "timer.h"
#include "key.h"

uint8_t minuteCounter =0;

int main(void)
{
	int t;
	uint8_t foxNo;
	uint8_t foxes;
	uint8_t fox;

	/*
	 * do init stuff
	 */
	SELECTORSETUP = 0x00;
	MORSESETUP = 0xFF;

	DDRD = 1<<7;
	/*
	foxNo = SELECTOR & 0x0F;
	foxes = (SELECTOR & 0xF0)>>4;
	*/
	foxNo = 0;
	foxes = 4;
	/*
	 * counter/timer register setup
	 */

	timerInit(FAST_TIMER_COUNT,SLOW_TIMER_COUNT);

	sei();
	
	/* Main loop */
	while (1)
	{
		/* Procedure:
		 * 1. check what fox we are
		 * 2. wait for our time to send
		 * 3. send
		 * 	3a.	send call
		 * 	3b.	send tone
		 * 	3c.	send call
		 * 4. setup sleep time for wakeing up
		 * 5. loop sleep untill we are supposed to wake up
		 */

		enaSlowTimer();
		for (fox = 0;fox<foxNo;fox++)
		{
			//sleep for a minute
			//MORSEPORT ^= 0x10;
			//while (minuteCounter > 0);
			deepSleep();
			MORSEPORT ^=0x20;
		}
		disSlowTimer();
		enaFastTimer();
		
		sendChar(24);//O
		sendChar(35);//Z
		sendChar(7);//7
		sendChar(15);//F
		sendChar(24);//O
		sendChar(33);//X
		space();
		switch(foxNo)
		{
			case 1:
				sendChar(0xa);	//A
				break;
			case 2:
				sendChar(30);	//U
				break;
			case 3:
				sendChar(31);	//V
				break;
			case 4:
				sendChar(4);	//4
				break;
			case 5:
				sendChar(5);	//5
				break;
			default:
				break;
		}
		sendLongBeep();
		space();
		sendLongBeep();
		space();
		sendChar(24);//O
		sendChar(35);//Z
		sendChar(7);//7
		sendChar(15);//F
		sendChar(24);//O
		sendChar(33);//X
		space();
		switch(foxNo)
		{
			case 1:
				sendChar(0xa);	//A
				break;
			case 2:
				sendChar(30);	//U
				break;
			case 3:
				sendChar(31);	//V
				break;
			case 4:
				sendChar(4);	//4
				break;
			case 5:
				sendChar(5);	//5
				break;
			default:
				break;
		}
		


		disFastTimer();
		enaSlowTimer();
		for (;fox<foxes;fox++)
		{
			MORSEPORT ^=(0x10<<fox);;
			deepSleep();
			// do the sleep thing again
		}
	}
}
