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


//See ATMega16 datasheet p. 100
#define FAST_TIMER_COUNT 0x8842

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

extern uint8_t minuteCounter;

#endif // GLOBALS_H
