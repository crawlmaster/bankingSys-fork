#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "clientConfig.h"
#include <stdio.h>

#define INITIAL_BANK_CAPACITY 1000
typedef char *key;
typedef int   value;
typedef uint64_t (*hashFunction)(key, value);

typedef struct hashTable {
	userAcc	   **users;
	uint32_t     size;
	hashFunction hashingFunction;
} hashTable;

userAccPtr createNode(uint32_t tempID, uint64_t tempCNP, char *tempIBAN,
		      char *tempSurname, char *tempName, char *tempPassword,
		      double tempSold);

userAccPtr *addUser(userAccPtr *hashTable, int *tableSize, uint32_t tempID,
		    uint64_t tempCNP, char *tempIBAN, char *tempSurname,
		    char *tempName, char *tempPassword, double tempSold);

#endif
