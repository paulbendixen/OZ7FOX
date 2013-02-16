#include <avr/io.h>
#include <avr/sleep.h>
#include "globals.h"
#include "timer.h"
#include "key.h"

void sendFoxID(uint8_t fox_id); 
void sendCallsign();
void initPorts();

int main(void)
{
	// The number of this fox.
	uint8_t thisFoxNo;
	// The total number of foxes.
	uint8_t totalFoxNo;
	// Counter variable for fox iteration.
	uint8_t currentFox;

	/*
	 * do init stuff
	 */
	initPorts();

	/*
	TODO: Make these parameters be selectable from dip switches
	thisFoxNo = SELECTOR & 0x0F;
	totalFoxNo = (SELECTOR & 0xF0)>>4;
	*/
	thisFoxNo = 0;
	totalFoxNo = 4;
	
	// counter/timer register setup
	timerInit(FAST_TIMER_COUNT,SLOW_TIMER_COUNT);

	// Enable interrupts.
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
		for (currentFox = 0; currentFox < thisFoxNo; currentFox++)
		{
			//sleep for a minute
			//MORSEPORT ^= 0x10;
			//while (minuteCounter > 0);
			deepSleep();
			MORSEPORT ^=0x20;
		}
		disSlowTimer();
		enaFastTimer();
		
		sendFoxID(thisFoxNo);

		sendLongBeep();
		space();
		sendLongBeep();
		space();
		
		sendFoxID(thisFoxNo);

		disFastTimer();
		enaSlowTimer();
		
		currentFox++; // count ourselves
		synchronizeTick();
		for (; currentFox < totalFoxNo; currentFox++)
		{
			MORSEPORT ^=(0x10<<currentFox);;
			deepSleep();
			// do the sleep thing again
		}
	}
}

/*
	Send the complete ID for this fox.
	It consists of its callsign followed by
	its number.
*/
void sendFoxID(uint8_t fox_id) 
{
		sendCallsign();
		switch(fox_id)
		{
			case 1:
				sendChar(alpha);	//A
				break;
			case 2:
				sendChar(uniform);	//U
				break;
			case 3:
				sendChar(victor);	//V
				break;
			case 4:
				sendChar(four);	//4
				break;
			case 5:
				sendChar(five);	//5
				break;
			default:
				break;
		}
}

/*
	Broadcast "OZ7FOX", which is the call for all
	foxes in OZ-land (DK).
*/
void sendCallsign() 
{
		sendChar(oscar);
		sendChar(zulu);
		sendChar(seven);
		sendChar(foxtrot);
		sendChar(oscar);
		sendChar(xray);
}

/*
	Initialize the ports on the microprocessor as
	either input or output ports.
*/
void initPorts() 
{
	// All selector ports are in input mode
	SELECTORSETUP = 0x00;
	// All morse ports are output ports
	MORSESETUP = 0xFF;
#ifndef NDEBUG
	// D7 toggles every time 6 second timer triggers. Make D7 output.
	DDRD = 1 << 7;
#endif
}
