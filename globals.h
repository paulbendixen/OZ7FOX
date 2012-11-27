#ifndef GLOBALS_H
#define GLOBALS_H
#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 4000000UL
//#define F_CPU 3696400
#endif

#define MORSEPORT PORTA
#define MORSESETUP DDRA
#define MORSEPIN 0x01

#define SELECTOR PORTB
#define SELECTORSETUP DDRB
#define FOXA 0x01
#define FOXU 0x02
#define FOXV 0x04

#endif // GLOBALS_H
