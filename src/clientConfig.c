#include <stdio.h>
#include <stdlib.h>

#include "../include/clientConfig.h"
#include "../include/configDB.h"
#include "../include/colors.h"
#include "../include/cryptString.h"

// functions for creating hashing table , hash index , add note to table

void loadDataBase(dbConfig *dataBaseConfig)
{
	{
		FILE *dataBase = fopen(DATABASE_FILE, "r");
		if (!dataBase)
		{
			printf(BOLD_RED "Error occurred when openning the dataBase file!\n" RESET);
			exit(EXIT_FAILURE);
		}

		char *buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);

		if (dataBaseConfig->isEncrypted == 0)
		{
			// first time encryption
			// __uint32_t tempID;
			// __uint64_t tempCNP;
			// char tempIBAN[MAX_IBAN_LENGHT];
			// char tempSurname[MAX_USER_NAME_LENGHT];
			// char tempName[MAX_USER_NAME_LENGHT];
			// char tempPassword[MAX_USER_PASS_LENGHT];
			// double tempSold;
			while(fgets(buffer , MAX_BUFFER_SIZE , dataBase) != NULL){
				cryptString(&buffer);
				printf("%s" , buffer);
			}
		}
		else
		{
			// the file is already encrypted - first of all decrypt it when load it in mememory
		}
	}
}
// 137