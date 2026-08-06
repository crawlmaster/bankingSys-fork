#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_STRING_SIZE 50
#define SHIFT 7



char shiftLetterForward(char letter){
	// verifica litera mica
	if(letter >= 'a' && letter <= 'z'){
		if(letter + SHIFT > 'z'){
			letter = (letter + SHIFT) - 26;
		} else {
			letter += SHIFT;
		}
	} else {
		if(letter + SHIFT > 'Z'){
			letter = (letter + SHIFT) - 26;
		} else {
			letter += SHIFT;
		}
	}
	return letter;
}

char shiftNumberForward(char number){
	if(number + SHIFT > '9'){
		number = (number + SHIFT) - 10;
	} else {
		number += SHIFT;
	}
	return number;
}

char shiftLetterBackwards(char letter){
	if(letter >= 'a' && letter <= 'z'){
		if(letter - SHIFT < 'a'){
			letter = (letter - SHIFT) + 26;
		} else {
			letter -= SHIFT;
		}
	} else {
		if(letter - SHIFT < 'A'){
			letter = (letter - SHIFT) + 26;
		} else {
			letter -= SHIFT;
		}
	}
	return letter;
}

char shiftDigitBackwards(char number){
	if(number - SHIFT < '0'){
		number = (number - SHIFT) + 10;
	} else {
		number -= SHIFT;
	}
	return number;
}

void cript_string(char **string){
	for(int i = 0 ; i < (int)strlen(*string) ; ++i){
		if(isalpha((*string)[i])) (*string)[i] = shiftLetterForward((*string)[i]);
		else if(isdigit((*string)[i])) (*string)[i] = shiftNumberForward((*string)[i]);
		else if((*string)[i] == ' ') continue;
		else{
			printf("Invalid Character !\n");
			exit(EXIT_FAILURE);
		}
	}
}

void decrypt_string(char **string){
	for(int i = 0; i < (int)strlen(*string) ; ++i){
		if(isalpha((*string)[i])) (*string)[i] = shiftLetterBackwards(((*string)[i]));
		else if(isdigit(((*string)[i]))) (*string)[i] = shiftDigitBackwards(((*string)[i]));
		else {
			printf("Invalid Character !\n");
			exit(EXIT_FAILURE);
		}
	}
}

int main(void){

	char *iban = malloc(25 * sizeof(char));
	char *cnp = malloc(30 * sizeof(char));

	FILE *openFile = fopen("criptText.txt" , "r");
	if(!openFile){
		perror("Eroare la deschiderea fisierului de intrare!\n");
		exit(1);
	}

	char *string = NULL;
	int stringSize = 0;
	string = malloc(sizeof(char) * INITIAL_STRING_SIZE);
	if(!string){
		perror("Eroare la alocarea memoeiei pentru string!\n");
		fclose(openFile);
		exit(1);
	}

	printf("Enter string : ");

	int c = getchar();
	while(c != '\0' && c != '\n'){
		string[stringSize++] = c;
		c = getchar();
	}
	string[stringSize] = '\0';

	
	cript_string(&string);
	printf("String ul dupa criptare : %s\n", string);
	
	decrypt_string(&string);
	printf("String ul dupa decriptare : %s\n", string);

	// FILE *outputFile = fopen("outputCript.txt" , "w");
	
	// fprintf(outputFile , "0x%02X" , 4);
	fclose(openFile);

	printf("Iban : ");
	scanf("%s" , iban);
	printf("CNP : ");
	scanf("%s" , cnp);

	printf("Datele criptate : \n");
	cript_string(&iban);
	cript_string(&cnp);
	printf("Iban : %s\nCNP : %s\n" , iban , cnp);

	return 0;
}