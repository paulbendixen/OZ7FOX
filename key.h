/**
 * @file	key.h
 * @brief	The header file for keying functions
 *
 * This file contains functions for keying the transmitter.
 * Pausing functions are called from here, maintainging timing.
 */
#ifndef KEY_H
#define KEY_H
#include "globals.h"
#include "timer.h"

/**
 * @brief	Macros to generate a bit pattern
 *
	Macros to generate bit pattern conrresponsing to a dit (dot) or 
	dah (dash) at a given position. These can be composited
	using the logical OR (|) to form strings
	of morse characters.
*/
#define DAH(n) (1 << (7-n))
/// Same as dah, only with dits
#define DIT(n) (0 << (7-n))

/**
 * @brief	A macro to determine wether a bit is true or false
 * @param	n The nth bit to test
 * @param	b The bitpattern to extract the bit from
 * @return	Returns 1 if the bit was set and 0 otherwise
 *
 * This macro extracts a bitvalue from a bit pattern
 */
#define EXTRACT_MORSE_BIT(n,b) ((b >> (7-n)) & 1)

typedef uint8_t morse_length_t;
typedef uint8_t morse_pattern_t;

/**
 * @brief	A struct that contains a complete morse charater
 * @var		pattern The dits and dahs of a morse character
 * @var 	length How many dits and dahs there are in the chararcter
 *
 * This struct is at the heart of the code.
 * It gives the pattern to send out, a binary 0 being a dit and a binary 1
 * being a dah.
 * The length of the structure is given in length so that e.g. a (dah-dit)
 * is a 1 and a 0 with a length of two.
 * All the actual characters are described in their expanded form in the
 * implementation.
 */
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

int sendChar(morse_char_t character);
void sendLongBeep(unsigned int morse_ticks);
int charSpace(void);
int space(void);

#endif //KEY_H
