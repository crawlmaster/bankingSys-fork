#include "../include/cryptString.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static int isLetter(char c)
{
	return 'a' <= (c | 0x20) && (c | 0x20) <= 'z';
}

static int isNumber(char c)
{
	return '0' <= c && c <= '9';
}

char shiftLetterForward(char letter)
{
	return 'a' + (letter - 'a' + 1) % 26;
}

char shiftNumberForward(char number)
{
	return '0' + (number - '0' + 1) % 10;
}

char shiftLetterBackwards(char letter)
{
	switch (letter) {
	case 'a':
		return 'z';
	case 'A':
		return 'Z';
	default:
		return letter - 1;
	}
}

char shiftDigitBackwards(char number)
{
	return number == '0' ? '9' : number - 1;
}

void cryptString(char **string)
{
	size_t string_len = strlen(*string);
	for (size_t i = 0; i < string_len; ++i) {
		if (isLetter((*string)[i]))
			(*string)[i] = shiftLetterForward((*string)[i]);
		else if (isNumber((*string)[i]))
			(*string)[i] = shiftNumberForward((*string)[i]);
	}
}

void decryptString(char **string)
{
	for (int i = 0; i < (int)strlen(*string); ++i) {
		if (isalpha((*string)[i]))
			(*string)[i] = shiftLetterBackwards(((*string)[i]));
		else if (isdigit(((*string)[i])))
			(*string)[i] = shiftDigitBackwards(((*string)[i]));
	}
}
