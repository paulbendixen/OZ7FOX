/**
 * @file	key.c
 * @brief	The implementation of the functions for keying the transmitter
 * 
 * All the actual transmission of dits and dahs are done from this file
 */

#include "key.h"
#include "timer.h"

/** 
 * Initialization of constants corresponding to the characters
 * that are supported. They are declared as extern in key.h
 * and are thus visible for other source files linking
 * with this program. */
const morse_char_t zero =     {DAH(0)|DAH(1)|DAH(2)|DAH(3)|DAH(4), 5};
const morse_char_t one =      {DIT(0)|DAH(1)|DAH(2)|DAH(3)|DAH(4), 5};
const morse_char_t two =      {DIT(0)|DIT(1)|DAH(2)|DAH(3)|DAH(4), 5};
const morse_char_t three =    {DIT(0)|DIT(1)|DIT(2)|DAH(3)|DAH(4), 5};
const morse_char_t four =     {DIT(0)|DIT(1)|DIT(2)|DIT(3)|DAH(4), 5};
const morse_char_t five =     {DIT(0)|DIT(1)|DIT(2)|DIT(3)|DIT(4), 5};
const morse_char_t six =      {DAH(0)|DIT(1)|DIT(2)|DIT(3)|DIT(4), 5};
const morse_char_t seven =    {DAH(0)|DAH(1)|DIT(2)|DIT(3)|DIT(4), 5};
const morse_char_t eight =    {DAH(0)|DAH(1)|DAH(2)|DIT(3)|DIT(4), 5};
const morse_char_t nine =     {DAH(0)|DAH(1)|DAH(2)|DAH(3)|DIT(4), 5};
const morse_char_t alpha =    {DIT(0)|DAH(1), 2};
const morse_char_t bravo =    {DAH(0)|DIT(1)|DIT(2)|DIT(3), 4};
const morse_char_t charlie =  {DAH(0)|DIT(1)|DAH(2)|DIT(3), 4};
const morse_char_t delta =    {DAH(0)|DIT(1)|DIT(2), 3};
const morse_char_t echo =     {DIT(0), 1};
const morse_char_t foxtrot =  {DIT(0)|DIT(1)|DAH(2)|DIT(3), 4};
const morse_char_t golf =     {DAH(0)|DAH(1)|DIT(2), 3};
const morse_char_t hotel =    {DIT(0)|DIT(1)|DIT(2)|DIT(3), 4};
const morse_char_t india =    {DIT(0)|DIT(1), 2};
const morse_char_t juliet =   {DIT(0)|DAH(1)|DAH(2)|DAH(3), 4};
const morse_char_t kilo =     {DAH(0)|DIT(1)|DAH(2), 3};
const morse_char_t lima =     {DIT(0)|DAH(1)|DIT(2)|DIT(3), 4};
const morse_char_t mike =     {DAH(0)|DAH(1), 2};
const morse_char_t november = {DAH(0)|DIT(1), 2};
const morse_char_t oscar =    {DAH(0)|DAH(1)|DAH(2), 3};
const morse_char_t papa =     {DIT(0)|DAH(1)|DAH(2)|DIT(3), 4};
const morse_char_t quebec =   {DAH(0)|DAH(1)|DIT(2)|DAH(3), 4};
const morse_char_t romeo =    {DIT(0)|DAH(1)|DIT(2), 3};
const morse_char_t sierra =   {DIT(0)|DIT(1)|DIT(2), 3};
const morse_char_t tango =    {DAH(0), 1};
const morse_char_t uniform =  {DIT(0)|DIT(1)|DAH(2), 3};
const morse_char_t victor =   {DIT(0)|DIT(1)|DIT(2)|DAH(3), 4};
const morse_char_t whisky =   {DIT(0)|DAH(1)|DAH(2), 3};
const morse_char_t xray =     {DAH(0)|DIT(1)|DIT(2)|DAH(3), 4};
const morse_char_t yankee =   {DAH(0)|DIT(1)|DAH(2)|DAH(3), 4};
const morse_char_t zulu =     {DAH(0)|DAH(1)|DIT(2)|DIT(3), 4};

const morse_char_t *allChars[] = { &zero,  
&one,
&two,
&three,
&four,
&five,
&six,
&seven,
&eight,
&nine,
&alpha,
&bravo,
&charlie,
&delta,
&echo,
&foxtrot,
&golf,
&hotel,
&india,
&juliet,
&kilo,
&lima,
&mike,
&november,
&oscar,
&papa,
&quebec,
&romeo,
&sierra,
&tango,
&uniform,
&victor,
&whisky,
&xray,
&yankee,
&zulu};


/**
 * @brief	THIS IS THE ONE THAT SENDS A MORSE CHARACTER :D
 * @param	chararcter The morse_char_t character to send
 * @return	Returns the total number of morse ticks consumed
 *
 * This function iterates through the morse_char_t struct, sending
 * out the dits and dahs.
 */
ticks_t sendChar(morse_char_t character)
{
	int index;
	ticks_t morse_ticks, total_morse_ticks = 0;
	for (index = 0; index < character.length; ++index)
	{
		MORSE_ON; // start keying

		morse_ticks = (EXTRACT_MORSE_BIT(
					character.pattern, index) ? TICKS_DAH : TICKS_DIT );
		delay(morse_ticks);
		
		MORSE_OFF; // stop keying
		
		// Intra-character spacing is one tick.
		morse_ticks += delay(TICKS_INTRA_CHAR);
		total_morse_ticks += morse_ticks; 
	}
	// Make a space trailing this character
	total_morse_ticks += charSpace(TICKS_INTRA_CHAR);
	return total_morse_ticks;
}


/**
 * @brief	Sends the beep used for tracking
 * @param	morse_ticks The number of morse ticks the beep should be
 *
 * This function sends out the long beep that the hunters use to track.
 * The length of the beep must be so that the \e complete transmission is less
 * than one minute.
 */
ticks_t sendLongBeep(ticks_t morse_ticks)
{
	// Turn keying on.
	MORSE_ON; 
	// Delay the appropriate number of ticks.
	delay(morse_ticks); 
	// Turn keying off.
	MORSE_OFF;
	return morse_ticks;
}

/**
 * @brief	Makes a space between characters
 * @returns	Returns the number of morse ticks consumed
 * @param afterChar Whether this space is trailing a sent character.
 *
 * This function holds a pause of two or three morse ticks.
 * The standard is to hold for three morseticks between characters
 * but since all morse dits and dahs is followed by a single tick of silence
 * only two ticks are nessecary. 
 */
ticks_t charSpace(ticks_t alreadySpent)
{
	return space(TICKS_INTER_CHAR, alreadySpent);
}

/**
 * @brief	Makes an actual space character
 * @return	Returns the number of morse ticks consumed
 *
 * This function holds a pause of six morse ticks.
 * Actually the standard is to hold for seven morse ticks between words but
 * since all morse dits and dahs in this implementation is followed by a single
 * tick of silence, only six ticks are nessecary.
 */
ticks_t wordSpace(ticks_t alreadySpent)
{
	return space(TICKS_INTER_WORD, alreadySpent);
}

/**
 * @brief	Makes a space of an arbitrary number of ticks
 * @param	targetWidth	Duration of space in ticks
 * @param	alreadySpent	Ticks we have already waited.
 * @return	The number of ticks used
 * 
 * This function holds a pause of an arbitrary number of ticks
 * as defined by the argument width.
 * The alreadySpent variable should be 0 if there is nothing before this,
 * the INTRA_WORD or INTRA_CHAR constants is usually good default choices.
 */
ticks_t space(ticks_t targetWidth, ticks_t alreadySpent)
{
	/* If the time spent waiting already is
	 * less than what we are supposed to wait,
	 * wait the remainder of the delay.
	 * Otherwise, don't wait. */
	return (
			alreadySpent < targetWidth
			? delay(targetWidth - alreadySpent)
			: 0
	);
}

/**
 * @brief	internal helper function to send ascii as morse structs
 * @param	ch The ASCII char to transmit using morse
 * @return	The number of ticks it took to send the char
 */
ticks_t sendUsingArray( const char ch )
{
	ticks_t tickCounter;
	if( ( 0x41 <= ch ) && ( 0x5a >= ch ) ) /* Capitals */
	{
		/* 65 = alpha = 10 so subtract 55 */
		tickCounter = sendChar( *allChars[ ch - 55 ] );
	}
	else if( ( 0x61 <= ch ) && ( 0x7a >= ch ) ) /* lowercase */
	{
		/* 97 = alpha = 10 so subtract 87 */
		tickCounter = sendChar( *allChars[ ch - 87 ] );
	}
	else if( 0x20 == ch ) /* This is a space*/
	{
		tickCounter = wordSpace( TICKS_INTRA_WORD );
	}
	else if( ( 0x30 <= ch ) && ( 0x39 >= ch ) ) /* Numbers */
	{
		tickCounter = sendChar( *allChars[ ch - 0x30 ] );
	}
	else /* fail catcher */
	{
		/* This is where an error logger would go... */
		tickCounter = 0;
	}
	return tickCounter;
}

/**
 * @brief	Sends a null terminated string, using the array method
 * @param	message A pointer to an array of chars that is null terminated.
 * @return	The number of ticks used.
 *
 * This function takes a null terminated string and transmits it.
 *
 * @warning	This function may read beoynd the limits of the array if it is
 * not properly terminated
 */
ticks_t sendString(char *message)
{
	ticks_t tickCounter=0;
	while ( 0 != *message )
	{
		tickCounter += sendUsingArray( *message );
		message++;
	}
	return tickCounter;
}

/**
 * @brief	Sends a string of length chars using the array method
 * @param	message a char pointer to the string to send
 * @param	chars the length of the string to send
 * @return	The total time for sending the entire string in ticks
 */
ticks_t sendStringN(char *message, const int chars)
{
	ticks_t tickCounter = 0;
	int i;
	for( i = 0; i < chars ; i++ )
	{
		tickCounter += sendUsingArray( *message );
		message++;
	}
	return tickCounter;
}
