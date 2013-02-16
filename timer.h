#ifndef TIMER_H
#define TIMER_H
#include "globals.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>

void deepSleep(void);
void synchronizeTick(void);
void timerInit(uint16_t fastTimerCompare, uint8_t slowTimerCompare);
void setTimer(int timerCompare);
void resetTimer( void );
void enaFastTimer( void );
void enaSlowTimer( void );
void disFastTimer( void );
void disSlowTimer( void );

#endif //TIMER_H
