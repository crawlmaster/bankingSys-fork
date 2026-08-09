#ifndef CLIENT_CONFIG_H
#define CLIENT_CONFIG_H

#include <stdio.h>

// DEFINE SECTION
#define MAX_USER_NAME_LENGHT 30
#define MAX_USER_PASS_LENGHT 16
#define MAX_IBAN_LENGHT 25

#pragma pack(push , 1)
typedef struct client
{
  __uint32_t ID;
  __uint64_t CNP;
  char IBAN[MAX_IBAN_LENGHT];
  char surname[MAX_USER_NAME_LENGHT];
  char name[MAX_USER_NAME_LENGHT];
  char password[MAX_USER_PASS_LENGHT];
  double sold;
} userAcc, *userAcc_ptr;

#pragma pack(pop)

#endif