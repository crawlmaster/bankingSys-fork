#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/hashTable.h"
#include "../include/clientConfig.h"

userAccPtr createNode(__uint32_t tempID, __uint64_t tempCNP, char *tempIBAN, char *tempSurname, char *tempName, char *tempPassword, double tempSold){
	userAccPtr temp = malloc(sizeof(struct userAcc));
	if(!temp) exit(EXIT_FAILURE);
	temp->ID = tempID;
	temp->CNP = tempCNP;
	strncpy(temp->IBAN , tempIBAN , MAX_IBAN_LENGHT - 1);
	strncpy(temp->name , tempName , MAX_USER_NAME_LENGHT - 1);
	strncpy(temp->surname , tempSurname , MAX_USER_NAME_LENGHT - 1);
	strncpy(temp->password , tempPassword , MAX_USER_PASS_LENGHT - 1);
	temp->sold = tempSold;
	return temp;
}

userAccPtr *addUser(userAccPtr *hashTable, int *tableSize, __uint32_t tempID, __uint64_t tempCNP, char *tempIBAN, char *tempSurname, char *tempName, char *tempPassword, double tempSold)
{
	userAccPtr tempNode = createNode(tempID, tempCNP, tempIBAN, tempSurname, tempName, tempPassword, tempSold);
	hashTable[(*tableSize)++] = tempNode;
	return hashTable;
}