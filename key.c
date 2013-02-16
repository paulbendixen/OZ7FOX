#include "key.h"
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
const morse_char_t november = {DAH(0)|DIT(1)};
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

void initMorseCounter(void)
{
}

void startCounter(void)
{
}

void stopCounter(void)
{
}

void sendChar(morse_char_t character)
{
	int i;
	for (i = 0; i < character.length; ++i)
	{
		MORSEPORT &= !MORSEPIN;
		delay(EXTRACT_MORSE_BIT(i,character.pattern) ? 3 : 1 );
		MORSEPORT |= MORSEPIN;
		delay(1);
	}
}

void sendLongBeep(void)
{
	MORSEPORT &= !MORSEPIN;
	// Send about half a minute = 860 ticks
	// minus the time used for sending out callsign
	delay(676); // OZ7FOX 4 is max length  =91
}

void charSpace(void)
{
	MORSEPORT |= MORSEPIN;
	delay(2); // should wait 3, we already waited 1
}

void space(void)
{
	MORSEPORT |= MORSEPIN;
	delay(6); // same as above, but with 7
}

