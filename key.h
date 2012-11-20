#ifndef KEY_H
#define KEY_H
#include "globals.h"

void initMorseCounter(void);
void startCounter(void);
void stopCounter(void);
void key(int press);
void sendChar(unsigned char);

#endif //KEY_H
