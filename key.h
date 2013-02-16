#ifndef KEY_H
#define KEY_H
#include "globals.h"
#include "timer.h"
#include <avr/sleep.h>

#define DAH(n) (1 << (7-n))
#define DIT(n) (0 << (7-n))

#define EXTRACT_MORSE_BIT(n,b) ((b >> (7-n)) & 1)

typedef uint8_t morse_length_t;
typedef uint8_t morse_pattern_t;

typedef struct 
{
   morse_pattern_t pattern;
   morse_length_t length;
} morse_char_t;

extern const morse_char_t zero;
extern const morse_char_t one;
extern const morse_char_t two;
extern const morse_char_t three;
extern const morse_char_t four;
extern const morse_char_t five;
extern const morse_char_t six;
extern const morse_char_t seven;
extern const morse_char_t eight;
extern const morse_char_t nine;
extern const morse_char_t alpha;
extern const morse_char_t bravo;
extern const morse_char_t charlie;
extern const morse_char_t delta;
extern const morse_char_t echo;
extern const morse_char_t foxtrot;
extern const morse_char_t golf;
extern const morse_char_t hotel;
extern const morse_char_t india;
extern const morse_char_t juliet;
extern const morse_char_t kilo;
extern const morse_char_t lima;
extern const morse_char_t mike;
extern const morse_char_t november;
extern const morse_char_t oscar;
extern const morse_char_t papa;
extern const morse_char_t quebec;
extern const morse_char_t romeo;
extern const morse_char_t sierra;
extern const morse_char_t tango;
extern const morse_char_t uniform;
extern const morse_char_t victor;
extern const morse_char_t whisky;
extern const morse_char_t xray;
extern const morse_char_t yankee;
extern const morse_char_t zulu;

void initMorseCounter(void);
void startCounter(void);
void stopCounter(void);
void key(int press);
void sendChar(morse_char_t character);
void deepSleep(void);
void sendLongBeep(void);
void charSpace(void);
void space(void);

#endif //KEY_H
