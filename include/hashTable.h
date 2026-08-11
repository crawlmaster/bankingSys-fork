#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include "clientConfig.h"

#define INITIAL_BANK_CAPACITY 1000

userAccPtr createNode(__uint32_t tempID, __uint64_t tempCNP, char *tempIBAN, char *tempSurname, char *tempName, char *tempPassword, double tempSold);

userAccPtr *addUser(userAccPtr *hashTable, int *tableSize, __uint32_t tempID, __uint64_t tempCNP, char *tempIBAN, char *tempSurname, char *tempName, char *tempPassword, double tempSold);
int hashingFunction(userAccPtr node , int seed);

#endif 
