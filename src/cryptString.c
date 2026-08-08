#include "../include/criptString.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LAST_LETTER 26

char shiftLetterForward(char letter)
{
	if(letter >= 'a' && letter <= 'z'){
		if(letter + SHIFT > 'z'){
			letter = (letter + SHIFT) - LAST_LETTER;
		} else {
			letter += SHIFT;
		}
	} else {
		if(letter + SHIFT > 'Z'){
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
		number = (number + SHIFT) - 10;
	}
	else
	{
		number += SHIFT;
	}
	return number;
}

char shiftLetterBackwards(char letter)
{
	if (letter >= 'a' && letter <= 'z')
	{
		if (letter - SHIFT < 'a')
		{
			letter = (letter - SHIFT) + 26;
		}
		else
		{
			letter -= SHIFT;
		}
	}
	else
	{
		if (letter - SHIFT < 'A')
		{
			letter = (letter - SHIFT) + 26;
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
		number = (number - SHIFT) + 10;
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
		else
		{
			printf("Invalid Character !\n");
			exit(EXIT_FAILURE);
		}
	}
}

#undef LAST_LETTER