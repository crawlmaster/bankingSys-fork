#include "../include/criptString.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LAST_LETTER 26
#define FIRST_NUMBER 10
#define FIRST_LETTER_LOWERCASE_ASCIICODE 97
#define FIRST_LETTER_UPPERCASE_ASCIICODE 65
#define LAST_LETTER_LOWERCASE_ASCIICODE 122
#define LAST_LETTER_UPPERCASE_ASCIICODE 90

char shiftLetterForward(char letter)
{
	if(letter >= FIRST_LETTER_LOWERCASE_ASCIICODE && letter <= LAST_LETTER_LOWERCASE_ASCIICODE){
		if(letter + SHIFT > LAST_LETTER_LOWERCASE_ASCIICODE){
			letter = (letter + SHIFT) - LAST_LETTER;
		} else {
			letter += SHIFT;
		}
	} else {
		if(letter + SHIFT > LAST_LETTER_UPPERCASE_ASCIICODE){
			letter = (letter + SHIFT) - LAST_LETTER;
		} else {
			letter += SHIFT;
		}
	}
	return letter;
}

char shiftNumberForward(char number)
{
	if (number + SHIFT > '9')
	{
		number = (number + SHIFT) - FIRST_NUMBER;
	}
	else
	{
		number += SHIFT;
	}
	return number;
}

char shiftLetterBackwards(char letter)
{
	if (letter >= FIRST_LETTER_LOWERCASE_ASCIICODE && letter <= LAST_LETTER_LOWERCASE_ASCIICODE)
	{
		if (letter - SHIFT < FIRST_LETTER_LOWERCASE_ASCIICODE)
		{
			letter = (letter - SHIFT) + LAST_LETTER;
		}
		else
		{
			letter -= SHIFT;
		}
	}
	else
	{
		if (letter - SHIFT < FIRST_LETTER_UPPERCASE_ASCIICODE)
		{
			letter = (letter - SHIFT) + LAST_LETTER;
		}
		else
		{
			letter -= SHIFT;
		}
	}
	return letter;
}

char shiftDigitBackwards(char number)
{
	if (number - SHIFT < '0')
	{
		number = (number - SHIFT) + FIRST_NUMBER;
	}
	else
	{
		number -= SHIFT;
	}
	return number;
}

void cryptString(char **string)
{
	for (int i = 0; i < (int)strlen(*string); ++i)
	{
		if (isalpha((*string)[i]))
			(*string)[i] = shiftLetterForward((*string)[i]);
		else if (isdigit((*string)[i]))
			(*string)[i] = shiftNumberForward((*string)[i]);
		else if ((*string)[i] == ' ')
			continue;
		else
		{
			printf("Invalid Character !\n");
			exit(EXIT_FAILURE);
		}
	}
}

void decryptString(char **string)
{
	for (int i = 0; i < (int)strlen(*string); ++i)
	{
		if (isalpha((*string)[i]))
			(*string)[i] = shiftLetterBackwards(((*string)[i]));
		else if (isdigit(((*string)[i])))
			(*string)[i] = shiftDigitBackwards(((*string)[i]));
		else if((*string)[i] == ' ')
			continue;
		else {
			printf("Invalid Character !\n");
			exit(EXIT_FAILURE);
		}
	}
}

#undef LAST_LETTER
#undef FIRST_NUMBER
#undef FIRST_LETTER_LOWERCASE_ASCIICODE
#undef FIRST_LETTER_UPPERCASE_ASCIICODE
#undef LAST_LETTER_LOWERCASE_ASCIICODE
#undef LAST_LETTER_UPPERCASE_ASCIICODE
