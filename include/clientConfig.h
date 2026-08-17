#ifndef CLIENT_CONFIG_H
#define CLIENT_CONFIG_H

#include <stdio.h>
#include "configDB.h"

// DEFINE SECTION
#define MAX_USER_NAME_LENGHT 30
#define MAX_USER_PASS_LENGHT 16
#define MAX_IBAN_LENGHT 25
#define MAX_BUFFER_SIZE 140
#define DATABASE_FILE "dataBase/dataBase.txt"

#pragma pack(push , 1)
typedef struct userAcc
{
  __uint32_t ID;
  __uint64_t CNP;
  char IBAN[MAX_IBAN_LENGHT];
  char surname[MAX_USER_NAME_LENGHT];
  char name[MAX_USER_NAME_LENGHT];
  char password[MAX_USER_PASS_LENGHT];
  __uint64_t sold;
} userAcc, *userAccPtr;

#pragma pack(pop)

// functions

void loadDataBase(dbConfig *dataBaseConfig , userAccPtr *hashTable , int *tableSize);
short int checkClient(userAccPtr *hashTable , int tableSize);

#endif