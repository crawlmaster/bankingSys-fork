#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/clientConfig.h"
#include "../include/configDB.h"
#include "../include/colors.h"
#include "../include/cryptString.h"
#include "../include/hashTable.h"

// functions for creating hashing table , hash index , add note to table

void loadDataBase(dbConfig *dataBaseConfig , userAccPtr *hashTable , int *tableSize)
{
	FILE *dataBase = fopen(DATABASE_FILE, "r");
	if (!dataBase)
	{
		printf(BOLD_RED "Error occurred when openning the dataBase file!\n" RESET);
		exit(EXIT_FAILURE);
	}

		char *buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);

	__uint32_t tempID;
	__uint64_t tempCNP;
	// char *tempIBAN = malloc(sizeof(char) * MAX_IBAN_LENGHT);
	// char *tempSurname = malloc(sizeof(char) * MAX_USER_NAME_LENGHT);
	// char *tempName = malloc(sizeof(char) * MAX_USER_NAME_LENGHT);
	// char *tempPassword = malloc(sizeof(char) * MAX_USER_PASS_LENGHT);
	__uint64_t tempSold;
	char tempIBAN[MAX_IBAN_LENGHT];
	char tempSurname[MAX_USER_NAME_LENGHT];
	char tempName[MAX_USER_NAME_LENGHT];
	char tempPassword[MAX_USER_PASS_LENGHT];

	if (dataBaseConfig->isEncrypted == 0)
	{
		// first time encryption
		while(fgets(buffer , MAX_BUFFER_SIZE , dataBase) != NULL){

			int parsedArguments = sscanf(buffer , "%u %ld %s %s %s %s %ld" ,
				&tempID , &tempCNP , tempIBAN , tempSurname , tempName , tempPassword , &tempSold);

			if(parsedArguments != 7){
				printf(BOLD_RED "Error occurred when reading from data base!\n" RESET);
			}
			addUser(hashTable , tableSize , tempID , tempCNP , tempIBAN , tempSurname , tempName , tempPassword , tempSold);
			// cryptString(&buffer);
			// printf("%s" , buffer);
		}
		// dataBaseConfig->isEncrypted = 1;
	}
	else
	{
		// the file is already encrypted - first of all decrypt it when load it in mememory
		while(fgets(buffer , MAX_BUFFER_SIZE , dataBase) != NULL){

			decryptString(&buffer);
			sscanf(buffer, "%u %ld %s %s %s %s %ld",
						&tempID, &tempCNP, tempIBAN, tempSurname, tempName, tempPassword, &tempSold);
		}
	}
	// free(tempIBAN);
	// free(tempSurname);
	// free(tempName);
	// free(tempPassword);
	free(buffer);
	fclose(dataBase);
}
