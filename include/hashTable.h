#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include "clientConfig.h"

#define INITIAL_BANK_CAPACITY 1000
typedef char* key;
typedef int value;
typedef uint64_t (*hashFunction)(key , long);

typedef struct hashTable{
	userAcc **users;
	uint32_t size;
	hashFunction hashingFunction;
}hashTable;

userAccPtr createNode(__uint32_t tempID, __uint64_t tempCNP, char *tempIBAN, char *tempSurname, char *tempName, char *tempPassword, double tempSold);

userAccPtr *addUser(userAccPtr *hashTable, int *tableSize, __uint32_t tempID, __uint64_t tempCNP, char *tempIBAN, char *tempSurname, char *tempName, char *tempPassword, double tempSold);



#endif 
