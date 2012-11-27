#include "timer.h"

void timerInit(int timerCompare)
{
	TCCR1A = WGM12;
	TCCR1B = CS12|CS10;
	setTimer(timerCompare);
	TIMSK |= OCIE1A;
}

void setTimer(int timerCompare)
{
	OCR1A = timerCompare;
}

ISR(TIMER1_COMPA_vect)
{
	// This is where the magic happens
	MORSEPORT ^= MORSEPIN;
}
