#ifndef TIMER_H
#define TIMER_H
#include <avr/interrupt.h>
void timerInit(int timerCompare);
void setTimer(int timerCompare);

void ISR(TIMER1_COMPA_vect);
#endif //TIMER_H
