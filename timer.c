#include "timer.h"

void timerInit(int timerCompare)
{
	// this should also at some point include setup for sleep on timer2
	// Setup for timer/counter 1
	TCCR1B = (1<<WGM12)|(1<<CS10);// (1<<CS12) makes it 1024
	setTimer(timerCompare);
	// Setup for timer/counter 2
	ASSR = 1<<AS2;
	while((ASSR & 0x07)!=0);
	// TCCR2 [FOC2|WGM20|COM21|COM20][WGM21|CS22|SC21|CS20]
	TCCR2 = 0x1F;//0b0001 1111
	//TCCR2 = (1<<COM20)|(1<<WGM21)|(1<<CS20)|(1<<CS21)|(1<<CS22);
	TCNT2 = 0;
	OCR2 = 95;
	//TIMSK |= (1<<OCIE1A)|(1<<OCIE2);

	
}

void setTimer(int timerCompare)
{
	OCR1A = timerCompare;
}

void resetTimer( void )
{
	TCNT1 = 0;
}

void enaFastTimer( void )
{
	// make sure an interrupt is not going to happen
	TIMSK |= 1<<OCIE1A;
}

void disFastTimer(void )
{
	TIMSK &= !(1<<OCIE1A);
}

void enaSlowTimer( void )
{
	// Make sure an interrupt is not going to happen
	TIMSK |= 1<<OCIE2;
}

void disSlowTimer( void )
{
	TIMSK &= !(1<<OCIE2);
}

ISR(TIMER1_COMPA_vect)
{
	// This is where the magic happens
	//	MORSEPORT ^= MORSEPIN;
	// The magic is that the chip wakes up
}

ISR(TIMER2_COMP_vect)
{
	if (++minuteCounter == 10)
		minuteCounter = 0;
	MORSEPORT ^= 0x10;
}
