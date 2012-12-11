#include "timer.h"

void timerInit(int timerCompare)
{
	TCCR1B = (1<<WGM12)|(1<<CS12)|(1<<CS10);
	setTimer(timerCompare);
	TIMSK |= (1<<OCIE1A);
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
