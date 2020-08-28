/**
 * @file	timer.c
 * @brief	Implementation for all timer and timing
 * @version	1.0
 */

#include "timer.h"

/**
 * @brief	Initializer for the timers
 * @param	fastTimerCompare compare register setting for the fast timer
 * @param	slowTimerCompare Compare register setting for the slow timer
 *
 * Sets up the registers needed for the two timers to run correctly.
 * It does not set up any interrupts, so timers must be enabled otherwere
 */
void timerInit(uint16_t fastTimerCompare, uint8_t slowTimerCompare)
{
	// this should also at some point include setup for sleep on timer2
	// Setup for timer/counter 1
	TCCR1B = (1<<WGM12)|(1<<CS10);// (1<<CS12) makes it 1024
	setTimer(fastTimerCompare);
	// Setup for timer/counter 2
	// Setup for asyncrhronous operation on timer/counter 2
	ASSR = 1<<AS2;
	// make sure the asynchronous register is written
	while((ASSR & 0x07)!=0);
	// Datasheet p. 127
	// CTC; toggle OC2 on match; prescaler = 1024
	// TCCR2 [FOC2|WGM20|COM21|COM20][WGM21|CS22|SC21|CS20]
	TCCR2 = 0x1F;//0b0001 1111
	//TCCR2 = (1<<COM20)|(1<<WGM21)|(1<<CS20)|(1<<CS21)|(1<<CS22);
	TCNT2 = 0;
	OCR2 = slowTimerCompare;
	//TIMSK |= (1<<OCIE1A)|(1<<OCIE2);
	while((ASSR & 0x07)!=0);
}


/**
 * @brief Set the compare register for the fast timer
 */
void setTimer(int timerCompare)
{
	OCR1A = timerCompare;
}

/**
 * @brief	Reset the timer, so that we count from zero
 */
void resetTimer( void )
{
	TCNT1 = 0;
}

/**
 * @brief	Wait the defined number of morse ticks before going on
 * @param	press the time to wait before continuing
 *
 * This function enables the fast timer and waits the number of timer ticks
 * defined in the press parameter.
 * The chip will be in idle mode while waiting for the timeout
 */
ticks_t delay(ticks_t press)
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
	return press;
}

/**
 * @brief	Waits for one minute before returning, using low power mode
 *
 * This function sets the chip in the lowest power mode for six seconds and
 * does this 10 times, this results in a one minute delay
 */
void deepSleep( void )
{
	cli();
	sleep_enable();
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	sei();
	for ( int i=0;i<10;i++)
	{
		sleep_cpu();
	}
	sleep_disable();
}

/**
 * @brief	Consume the last of the tick
 * @pre		54 or more seconds must have passed of the transmission
 * @post	The system is now in sync with the other foxes
 *
 * The function consumes the last of the 6 second tick that is currently
 * running. This enambles synchronization of the system, so that counting
 * of minutes is not started untill the others start counting also.
 */
void synchronizeTick( void )
{
	cli();
	sleep_enable();
	set_sleep_mode(SLEEP_MODE_EXT_STANDBY);
	sei();
	sleep_cpu();
	sleep_disable();
}

/**
 * @brief	Enable interrupts for the fast timer
 *
 * This function allows the timer for morse timer to be enabled
 */
void enaFastTimer( void )
{
	// make sure an interrupt is not going to happen
	TIFR |= 1 << OCF1A;
	// enable the next timer interrupt
	TIMSK |= 1 << OCIE1A;
}

/**
 * @brief	Disable the interrupt for the fast timer
 *
 * This function disables the interrupt on the fast timer so that a wrong
 * system continuation is avoided
 */
void disFastTimer(void )
{
	TIMSK &= !(1 << OCIE1A);
}

/**
 * @brief	Enable the interrupt for the slow timer
 *
 * This function allows the timer for the deep sleep timer to wake us up
 */
void enaSlowTimer( void )
{
	// Make sure an interrupt is not going to happen
	TIFR |= 1 << OCF2;
	// Enable the next timer interrupt
	TIMSK |= 1 << OCIE2;
	// synchronize with the next one minute tick
	// TODO Actually synchronize
}

/**
 * @brief	Disable the interrupt for the slow timer
 *
 * Disables the 6 second timer interrupt so that it does not interfere with 
 * the morse code transmission
 */
void disSlowTimer( void )
{
	TIMSK &= !(1 << OCIE2);
}

/**
 * @brief	Interrupt Service routine for the fast timer
 *
 * This function wakes up the system when the timer reaches the predifined state
 * it does not do anything but can be used for debugging
 */
ISR(TIMER1_COMPA_vect)
{
	// This is where the magic happens
	//	MORSEPORT ^= MORSEPIN;
	// The magic is that the chip wakes up
}

/**
 * @brief	Interrupt Service routine for the slow timer
 *
 * This function wakes up the system when the timer reaches the predifined state
 * it does not do anything but can be used for debugging
 */
ISR(TIMER2_COMP_vect)
{
	// deepSleep() has taken over this functionality.

	//if (++minuteCounter == 10)
	//	minuteCounter = 0;
	//MORSEPORT ^= 0x10;
}
