#ifndef TIMER_H
#define TIMER_H
#include "globals.h"
#include <avr/interrupt.h>

void timerInit(int timerCompare);
void setTimer(int timerCompare);
void resetTimer( void );

//void ISR(TIMER1_COMPA_vect);
#endif //TIMER_H
