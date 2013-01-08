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
	foxNo = SELECTOR & 0x0F;
	foxes = (SELECTOR & 0xF0)>>4;
	/*
	 * counter/timer register setup
	 */

	timerInit(0x8842);

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
			while (minuteCounter > 0);
			
		}
		disSlowTimer();
		enaFastTimer();
		
		//sendChar(28);//S
		//sendChar(24);//O
		//sendChar(28);//S
		//charSpace();
		//sendChar(28);//S
		//sendChar(24);//O
		//sendChar(28);//S
		//space();
		disSlowTimer();
		enaSlowTimer();
		for (;fox<foxes;fox++)
		{
			// do the sleep thing again
		}
	}
}
