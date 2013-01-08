#ifndef TIMER_H
#define TIMER_H
#include "globals.h"
#include <avr/interrupt.h>

void timerInit(int timerCompare);
void setTimer(int timerCompare);
void resetTimer( void );
void enaFastTimer( void );
void enaSlowTimer( void );
void disFastTimer( void );
void disSlowTimer( void );

#endif //TIMER_H
