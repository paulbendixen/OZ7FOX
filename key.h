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
#define DAH(index) (1 << (7 - index))
/// Same as dah, only with dits
#define DIT(index) (0 << (7 - index))

/**
   @brief   Macros that define dit, dah and spaces width

   We define the widths of dits and dahs, and we
   define the withs of spacing between individual
   dits and dahs, between characters and between
   words. These are standardized.
*/
/// The width of a dit in ticks
#define TICKS_DIT 1
/// The width of a dah in ticks
#define TICKS_DAH 3
/// The space between dits and dahs inside a character
#define TICKS_INTRA_CHAR 1
/// The space between characters
#define TICKS_INTER_CHAR 3
/// The space inside a word is the same as the space between characters
#define TICKS_INTRA_WORD TICKS_INTER_CHAR
/// The space between words
#define TICKS_INTER_WORD 7

/**
 * @brief	A macro to determine wether a bit is true or false
 * @param	p The morse_pattern_t to extract the bit from
 * @param	i The index of bit to extract (from left, starting with 0)
 * @return	Returns 1 if the bit was set and 0 otherwise
 *
 * This macro extracts a bitvalue from a bit pattern
 */
#define EXTRACT_MORSE_BIT(p,i) ((p >> (7-i)) & 1)

/// Macro to turn morse key ON
#define MORSE_ON MORSEPORT &= !MORSEPIN
/// Macro to turn morse key OFF
#define MORSE_OFF MORSEPORT |= MORSEPIN

/// The length of a morse character in terms of dits and dahs
typedef uint8_t morse_length_t;
/// A pattern of dits and dahs (0 and 1)
typedef uint8_t morse_pattern_t;

/// A number of ticks is represented as an unsigned integer
typedef unsigned int ticks_t;

/**
 * @struct morse_char
 * @brief	A struct that contains a complete morse charater
 *
 * This struct is at the heart of the code.
 * It gives the pattern to send out, a binary 0 being a dit and a binary 1
 * being a dah.
 * The length of the structure is given in length so that e.g. a (dah-dit)
 * is a 1 and a 0 with a length of two.
 * All the actual characters are described in their expanded form in the
 * implementation.
 */
typedef struct morse_char
{
   /// @var		pattern The dits and dahs of a morse character
   morse_pattern_t pattern;
   /// @var 	length How many dits and dahs there are in the chararcter
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

ticks_t sendChar(morse_char_t character);
ticks_t sendLongBeep(ticks_t morse_ticks);
ticks_t charSpace(ticks_t alreadySpent);
ticks_t wordSpace(ticks_t alreadySpent);
ticks_t space(ticks_t targetWidth, ticks_t alreadySpent);

#endif //KEY_H
