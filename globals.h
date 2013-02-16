/**
 * @file	globals.h
 * @brief	Assorted definitions we might use
 */
#ifndef GLOBALS_H
#define GLOBALS_H
#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 1000000UL
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

#define MORSE_UNIT_IN_MILLIS 60

/**
@brief Converts the given time in ms to a clock tick defined by the CPU frq

This timer calculates what count should go into the compare register for the 
fast counter.

The timer is calculated as:

   Timer count = t_milis / prescaler * (F_CPU / 1000) - 1

@warning	The macro MUST NOT exceed the maximum number of
   timer counts which is 2^16 counts.

For a processor clocked at 1MHz, the maximum time roughly
corresponds to 65 milliseconds. 
   
See ATMega16 datasheet p. 100
*/

#define MORSE_COUNTER_COMPARE_VALUE ((MORSE_UNIT_IN_MILLIS * (F_CPU / 1000UL)) - 1)
#if MORSE_COUNTER_COMPARE_VALUE > 0xFFFF
#error MORSE_COUNTER_COMPARE_VALUE too large (>65536). Do something (RTAVRM)
#endif


/* The Interrupt is fired twice a f_{OC2} cycle, since it is the one
 * that toggles the output so t_{OC2} should be 12s.
 * 	      F_{clkIO}
 * f_{OCn} = --------------
 *            2*N*(1+OCRn)
 * 
 *            2*N*(1+OCRn)     2*1024*(1+192)
 * t_OCn =  --------------- = -------------- = 12
 *             F_clkIO          32.768
 */
#define SLOW_TIMER_COUNT 191
#define SPACE_LENGTH 7
#define HALF_MINUTE (30000 / MORSE_UNIT_IN_MILLIS)

extern uint8_t minuteCounter;

#endif // GLOBALS_H
