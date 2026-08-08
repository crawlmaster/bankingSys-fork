#ifndef BANKINGSYS_CRYPTO_H
#define BANKINGSYS_CRYPTO_H

#define SHIFT 7

#include <stdio.h>

char shiftLetterForward(char letter);
char shiftNumberForward(char number);
char shiftLetterBackwards(char letter);
char shiftDigitBackwards(char number);
void cryptString(char **string);
void decryptString(char **string);


#endif