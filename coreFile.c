#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "./include/criptString.h"
#include "./include/colors.h" //text colors , weights
#include "./include/configDB.h"
#include "./include/clientConfig.h"

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
void clientUIFunction()
{
  printf("\nYou're in the client section of the program!\n");
  return;
}

void adminUIFunction()
{
  printf("\nYou're in the admin section of the program!\n");
  sleep(1);
}

void displayBankingLogo(){
  printf(BOLD_GREEN "     ____              _    _                             _                 \n    | __ )  __ _ _ __ | | _(_)_ __   __ _   ___ _   _ ___| |_ ___ _ __ ___  \n    |  _ \\ / _` | '_ \\| |/ / | '_ \\ / _` | / __| | | / __| __/ _ \\ '_ ` _ \\ \n    | |_) | (_| | | | |   <| | | | | (_| | \\__ \\ |_| \\__ \\ ||  __/ | | | | |\n    |____/ \\__,_|_| |_|_|\\_\\_|_| |_|\\__, | |___/\\__, |___/\\__\\___|_| |_| |_|\n                                    |___/       |___/" RESET);
  usleep(500000);
  printf(BOLD "\n\nBanking Login...\n\n" RESET);
}

int main(void)
{
  displayBankingLogo();
  // load data base config
  dbConfig config;
  verifyFile(&config);

  usleep(500000);
  printf("\nLogin:\n Press 1 for client servicies\n Press 2 for admin servicies\nOption : ");

  char option;
  scanf("%c", &option);
  if (option == '1')
  {
    clientUIFunction();
  }
  else if (option == '2')
  {
    adminUIFunction();
  }
  else
  {
    printf("Any jailbreak attempts are recorded!\n");
    // .log file registration
  }
  saveConfig(&config);
  // displayConfig(&config);
  return 0;
}