#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "./include/cryptString.h"
#include "./include/colors.h" //text colors , weights
#include "./include/configDB.h"
#include "./include/clientConfig.h"
#include "./include/hashTable.h"

// void cript_database (different file with separated header files)
// void decript_database (same as cript_database function)


// userAcc_ptr __add_client_to_dataBase

// userAcc_ptr __delete_client_from_dataBase

// User acctions :
// userAcc_ptr solt_integoration
// userAcc_ptr withdraw_from_account
// userAcc_ptr add_money_to_account
// void convert_iban_PDF(struct clinet)

// TODO: Aux function:
// search_client_in_dataBase

// Functions for UI
void clientUIFunction(userAccPtr *hashTable , int *tableSize)
{
  // printf("\nYou're in the client section of the program!\n");
  if(checkClient(hashTable , (*tableSize)) == 1){

  } else {
    printf(BOLD_RED "Any jailbreak attempt will be stopped and recoreded!\n" RESET);
    // register in log file
  }
  return;
}

void adminUIFunction(dbConfig *config , userAccPtr *hashTable , int *hashTableSize)
{
  printf("\nYou're in the admin section of the program!\n");
  loadDataBase(config , hashTable , hashTableSize);
}

void displayBankingLogo(){
  printf(BOLD_GREEN "     ____              _    _                             _                 \n    | __ )  __ _ _ __ | | _(_)_ __   __ _   ___ _   _ ___| |_ ___ _ __ ___  \n    |  _ \\ / _` | '_ \\| |/ / | '_ \\ / _` | / __| | | / __| __/ _ \\ '_ ` _ \\ \n    | |_) | (_| | | | |   <| | | | | (_| | \\__ \\ |_| \\__ \\ ||  __/ | | | | |\n    |____/ \\__,_|_| |_|_|\\_\\_|_| |_|\\__, | |___/\\__, |___/\\__\\___|_| |_| |_|\n                                    |___/       |___/" RESET);
  usleep(500000);
  printf(BOLD "\n\nBanking Login...\n\n" RESET);
}

// void printDataBase(userAccPtr *hashTable){
//   // printf(BOLD_GREEN "Data base from hash table(Cryptated)\n" RESET);
//   // for(int i = 0 ; i < tableSize ; ++i){
//   //   printf("ID : %d  CNP : %ld  IBAN : %s  Surname : %s  Name : %s  Password : %s  Sold : %.2lf\n" , hashTable[i]->ID , hashTable[i]->CNP , hashTable[i]->IBAN , hashTable[i]->surname , hashTable[i]->name , hashTable[i]->password , hashTable[i]->sold);
//   // }
//   printf(BOLD_GREEN "\n\nData base from hash table(Decryptated)\n" RESET);
//   char *buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);
//   for (int i = 0; i < 10; ++i)
//   {
//     sprintf(buffer, "%u %ld %s %s %s %s %ld", hashTable[i]->ID, hashTable[i]->CNP, hashTable[i]->IBAN, hashTable[i]->surname, hashTable[i]->name, hashTable[i]->password, hashTable[i]->sold);
//     printf("%s\n" , buffer);
//     // printf("ID : %d  CNP : %ld  IBAN : %s  Surname : %s  Name : %s  Password : %s  Sold : %.2lf\n", hashTable[i]->ID, hashTable[i]->CNP, hashTable[i]->IBAN, hashTable[i]->surname, hashTable[i]->name, hashTable[i]->password, hashTable[i]->sold);
//     cryptString(&buffer);
//     printf("%s\n" , buffer);
//     decryptString(&buffer);
//     printf("%s\n\n" , buffer);
//   }
// }

int main(void)
{
  displayBankingLogo();
  // hash table
  userAccPtr *hashTable = malloc(sizeof(userAccPtr) * INITIAL_BANK_CAPACITY);
  if(!hashTable){
    printf(BOLD_RED "Error occurred when creating the hash table!\n" RESET);
    exit(EXIT_FAILURE);
  }
  int hashTableSize = 0;

  // load data base config
  dbConfig config;
  verifyFile(&config);

  usleep(500000);
  printf("\nLogin:\n Press 1 for client servicies\n Press 2 for admin servicies\nOption : ");

  char option;
  scanf("%c", &option);
  if (option == '1')
  {
    clientUIFunction(hashTable , &hashTableSize);
  }
  else if (option == '2')
  {
    adminUIFunction(&config , hashTable , &hashTableSize);
  }
  else
  {
    printf(BOLD_RED "Any jailbreak attempts are recorded!\n" RESET);
    // .log file registration
  }
  // printDataBase(hashTable);
  // saveConfig(&config);
  
  return 0;
}