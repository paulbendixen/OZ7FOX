#ifndef KEY_H
#define KEY_H
#include "globals.h"
#include "timer.h"
#include <avr/sleep.h>

void initMorseCounter(void);
void startCounter(void);
void stopCounter(void);
void key(int press);
void sendChar(unsigned char morseCh);
void charSpace(void);
void space(void);
#endif //KEY_H
