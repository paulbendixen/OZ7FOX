#include <avr/io.h>
#include <avr/sleep.h>
#include "globals.h"
#include "timer.h"
#include "key.h"
#include "main.h"

/**
   @file main.c
   @brief Main function.
   @return status code (never returns)
   
   The main function does all the fun stuff.
*/
int main(void)
{
	/// The number of this fox.
	uint8_t thisFoxNo;
	/// The total number of foxes.
	uint8_t totalFoxNo;
	/// Counter variable for fox iteration.
	uint8_t currentFox;
   /// Time spent transmitting
   unsigned int timeSpent;
	/*
	 * do init stuff
	 */
	initPorts();

	/*
	TODO: Make these parameters be selectable from dip switches
         or a similar device instead of being statically defined.
	thisFoxNo = SELECTOR & 0x0F;
	totalFoxNo = (SELECTOR & 0xF0)>>4;
	*/
	thisFoxNo = 0;
	totalFoxNo = 4;
	
	// counter/timer register setup
	timerInit(MORSE_COUNTER_COMPARE_VALUE,SLOW_TIMER_COUNT);

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
      /* Count through the foxes, wait for it to be our turn. */
		for (currentFox = 0; currentFox < thisFoxNo; currentFox++)
		{
			//sleep for a minute
			deepSleep();
#ifndef NDEBUG
			MORSEPORT ^= 0x20;
#endif
		}
      // Disable the slow timer (for sleeping) and enable the fast timer (for keying)
		disSlowTimer();
		enaFastTimer();

      // Send this fox' ID (including callsign) and record the time spend doing this.
		timeSpent = sendFoxID(thisFoxNo);
      
      // Send two consecutitve long beeps followed by short spaces.
		sendLongBeep(HALF_MINUTE - 4*SPACE_LENGTH - timeSpent);
		space();
		sendLongBeep(HALF_MINUTE - 4*SPACE_LENGTH - timeSpent);
		space();
		
      // retransmit the fox id.
		sendFoxID(thisFoxNo);

      // Disable the fast timer (for keying) and enable the slow timer (for sleeping) 		
      disFastTimer();
		enaSlowTimer();
		
		currentFox++; // count ourselves
		synchronizeTick();
		for (; currentFox < totalFoxNo; currentFox++)
		{
#ifndef NDEBUG
			MORSEPORT ^=(0x10<<currentFox);;
#endif
			deepSleep();
			// do the sleep thing again
		}
	}
}

/**
   @brief Send the complete ID for this fox.
   @param fox_id The ID of the fox
   @return The number of morse tics spent transmitting the fox ID

	It consists of its callsign followed by
	its number.
*/
int sendFoxID(uint8_t fox_id) 
{
	int totalLength;
	totalLength = sendCallsign();
	switch(fox_id)
	{
		case 0:
			return totalLength + sendChar(alpha);	//A
		case 1:
			return totalLength + sendChar(uniform);	//U
		case 2:
			return totalLength + sendChar(victor);	//V
		case 3:
			return totalLength + sendChar(four);	//4
		case 4:
			return totalLength + sendChar(five);	//5
		default:
			return totalLength;
	}
}

/**
   @brief Broadcast "OZ7FOX"
   @return The number of morse tics spent transmitting "OZ7FOX"
   
   OZ7FOX is the call for all
	foxes in OZ-land (DK).
*/
int sendCallsign() 
{
      int count = 0;
		count += sendChar(oscar);
		count += sendChar(zulu);
		count += sendChar(seven);
		count += sendChar(foxtrot);
		count += sendChar(oscar);
		count += sendChar(xray);
      return count;
}

/**
   @brief Initialize the ports on the microprocessor as either input or output ports.
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
