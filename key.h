#ifndef KEY_H
#define KEY_H
#include "globals.h"

void initMorseCounter(void);
void startCounter(void);
void stopCounter(void);
void key(int press);
void sendChar(unsigned char morseCh);

const uint8_t lengths[] = { 5,//0
5,//1
5,//2
5,//3
5,//4
5,//5
5,//6
5,//7
5,//8
5,//9
2,//a
3,//b
3,//c
3,//d
3,//e
3,//f
3,//g
3,//h
3,//i
3,//j
3,//k
3,//l
3,//m
3,//n
3,//o
3,//p
3,//q
3,//r
3,//s
3,//t
3,//u
3,//v
3,//w
3,//x
3,//y
3//z
};

const uint8_t ditdah[36]= { 5,//0
5,//1
5,//2
5,//3
5,//4
5,//5
5,//6
5,//7
5,//8
5,//9
2,//a
3,//b
3,//c
3,//d
3,//e
3,//f
3,//g
3,//h
3,//i
3,//j
3,//k
3,//l
3,//m
3,//n
3,//o
3,//p
3,//q
3,//r
3,//s
3,//t
3,//u
3,//v
3,//w
3,//x
3,//y
3//z
};

#endif //KEY_H
