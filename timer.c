#include "timer.h"

void timerInit(int timerCompare)
{
	WGM = 4;
	setTimer(timerCompare);
}

void setTimer(int timerCompare)
{
	OCR1A = timerCompare;
}

void ISR(TIMER1_COMPA_vect)
{
	// This is where the magic happens
	MORSEPORT ^= MORSEPIN;
}
