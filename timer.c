#include "timer.h"

void timerInit(int timerCompare)
{
	// this should also at some point include setup for sleep on timer2
	TCCR1B = (1<<WGM12)|(1<<CS12)|(1<<CS10);
	setTimer(timerCompare);
	TIMSK |= (1<<OCIE1A);
}

void setTimer(int timerCompare)
{
	OCR1A = timerCompare;
}

void resetTimer( void )
{
	TCNT1 = 0;
}

ISR(TIMER1_COMPA_vect)
{
	// This is where the magic happens
	//	MORSEPORT ^= MORSEPIN;
	// The magic is that the chip wakes up
}
