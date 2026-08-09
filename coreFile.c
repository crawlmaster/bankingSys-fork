#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "./include/criptString.h"


// text weigth - color
#define BOLD_GREEN "\x1b[1;32m"
#define GREEN "\x1b[32m"
#define BOLD_RED "\x1b[1;31m"
#define RED "\x1b[31m"

#define BOLD "\x1b[1m"
#define RESET "\x1b[0m"

#define CONFIG_KW "CFMT"
#define FILE_PATH "dataBase/config.meta"
#pragma pack(push, 1)

typedef struct
{
  char headerKw[5]; // verify if we have the rigth file
  __uint32_t numberOfClients;
  __uint32_t lastID;
  __uint8_t isEncrypted;
  __uint8_t cypherShift;
  __uint64_t createdTime;
  __uint64_t lastTimeModified;
} dbConfig;

#pragma pack(pop)

// create , load , save data base config file

void saveConfig(dbConfig *config)
{
  config->lastTimeModified = (__uint64_t)time(NULL);
  FILE *file = fopen(FILE_PATH, "wb");
  if (!file)
  {
    printf(BOLD_RED);
    printf("\nError opening the config file for saving!\n");
    printf(RESET);
    return;
  }

  size_t saving = fwrite(config, sizeof(dbConfig), 1, file);
  if (saving != 1)
  {
    printf(BOLD_RED);
    printf("\nError saving the config file!\n");
    printf(RESET);
    return;
  }
  fclose(file);
  printf(BOLD_GREEN);
  printf("Config file (.meta) was saved successfully!\n");
  printf(RESET);
}

short int createConfigFile(dbConfig *config)
{
  printf("Initializare date...\n");

  memset(config , 0 , sizeof(dbConfig));

  memcpy(config->headerKw , CONFIG_KW , 5);
  config->createdTime = (__uint64_t)time(NULL);
  config->lastTimeModified = (__uint64_t)time(NULL);
  config->cypherShift = SHIFT;
  config->isEncrypted = 0;
  config->lastID = 0;
  config->numberOfClients = 0;
  printf(BOLD_GREEN);
  printf("\n%s file was initialy configured!\n" , FILE_PATH);
  saveConfig(config);
  printf(RESET);
  return 1;
}

short int loadConfigFile(dbConfig *config)
{
  FILE *fileConfig = fopen(FILE_PATH, "rb");
  if (!fileConfig)
  {
    printf(BOLD_RED);
    printf("\nError on opening and creating config file!\n");
    printf(RESET);
    return 0;
  }

  size_t read_bytes = fread(config, sizeof(dbConfig), 1, fileConfig);
  fclose(fileConfig);

  if (read_bytes != 1)
  {
    printf(BOLD_RED);
    printf("\nConfig file (.meta) is corrupted!\n");
    printf(RESET);
    return -1;
  }

  if (strncmp(config->headerKw , CONFIG_KW , 5) != 0){
    printf(BOLD_RED);
    printf("\n%s may be corrupted or is a different file!\n" , FILE_PATH);
    printf(RESET);
    return -1;
  }
  printf(BOLD_GREEN);
  printf("%s was loaded!\n" , FILE_PATH);
  printf(RESET);
  return 1;
}



void verifyFile(dbConfig *fileConfig)
{
  FILE *file = fopen(FILE_PATH , "rb");
  if (file == NULL)
  {
    printf("Error on opening config file!\n");
    return ;
  }
  // printf("%s file was opened!\n" , FILE_PATH);
  char temp;
  temp = fgetc(file);
  if (temp == EOF)
  {
    if(createConfigFile(fileConfig) != 1){
      printf(BOLD_RED);
      printf("\nError on creating config file!\n");
      printf(RESET);
      return ;
    }
  }
  else
  {
    loadConfigFile(fileConfig);
  }
  fclose(file);
}

void formatTime(__uint64_t timestamp, char *buffer, size_t bufferSize)
{
  time_t raw_time = (time_t)timestamp;

  struct tm *timeInfo = localtime(&raw_time);
  if (timeInfo == NULL)
  {
    printf(BOLD_RED);
    printf("Invalid date!\n");
    printf(RESET);
    return;
  }

  strftime(buffer, bufferSize, "%Y-%m-%d %H:%M:%S", timeInfo);
}

void loadingConfig(dbConfig *config)
{
  verifyFile(config);
}

void displayConfig(dbConfig *config)
{
  char createdTime_mod[30] = {0};
  formatTime(config->createdTime, createdTime_mod, sizeof(createdTime_mod));

  char lastModTime[30] = {0};
  formatTime(config->lastTimeModified, lastModTime, sizeof(lastModTime));
  printf(BOLD);
  printf("\nConfig file : \n");
  printf(RESET);
  printf("Key word : %s\n", config->headerKw);
  printf("Number of clients : %d\n", config->numberOfClients);
  printf("Last id : %d\n", config->lastID);
  printf("Created time : %s\n", createdTime_mod);
  printf("Last time modified : %s\n", lastModTime);
  printf("Cipher shift : %d\n", config->cypherShift);
  printf("Encripted : %s\n\n", (config->isEncrypted == 1) ? "Yes" : "NO");
}

// DEFINE SECTION
#define MAX_USER_NAME_LENGHT 60
#define MAX_USER_PASS_LENGHT 64
#define MAX_IBAN_LENGHT 25

typedef struct client
{
  char userName[MAX_USER_NAME_LENGHT];
  char password[MAX_USER_PASS_LENGHT];
  long int ID; // clients ID - CNP
  char IBAN[MAX_IBAN_LENGHT];
  double sold;
} userAcc, *userAcc_ptr;

// void cript_database (different file with separated header files)
void simulateEncryption(){
  int c;
  //clears the stdin buffer 
  while((c = getchar()) != '\n' && c != '\0');
  
  printf("Enter a text : ");
  char *string = NULL; 
  string = malloc(sizeof(char) * 40);
  int stringSize = 0;
  int a;
  a = getchar();
  while (a != '\n' && a != '\0'){
    string[stringSize++] = a;
    a = getchar();
  }
  string[stringSize] = '\0';
  cryptString(&string);
  printf("Encrypted string : %s\n" , string);
  decryptString(&string);
  printf("Decrypted string : %s\n" , string);
  free(string);
}
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
  // long int clientID;

  // printf("Enter you credentials\nName %s: \nID : %ld");
  // while(1){
  printf("\nYou're in the client section of the program!\n");
  return;
  // }
}

void simulare_incarcare(int total_elemente)
{
  for (int i = 1; i <= total_elemente; i++)
  {
    // Calculezi procentul
    int procent = (i * 100) / total_elemente;

    printf("\rIncarcare baza de date: %d%% (%d/%d)", procent, i, total_elemente);
    fflush(stdout);

    usleep(500);
  }
  printf(BOLD_GREEN);
  printf("\n\n[OK] Baza de date a fost incarcata cu succes!\n\n");
  printf(RESET);
}

void adminUIFunction()
{
  printf("\nYou're in the admin section of the program!\n");
  simulare_incarcare(1000);
  sleep(1);
  simulateEncryption();
}



int main(void)
{

  // text for terminal loading

  // printf(FILE_PATH);

  printf(BOLD_GREEN);
  printf("     ____              _    _                             _                 \n    | __ )  __ _ _ __ | | _(_)_ __   __ _   ___ _   _ ___| |_ ___ _ __ ___  \n    |  _ \\ / _` | '_ \\| |/ / | '_ \\ / _` | / __| | | / __| __/ _ \\ '_ ` _ \\ \n    | |_) | (_| | | | |   <| | | | | (_| | \\__ \\ |_| \\__ \\ ||  __/ | | | | |\n    |____/ \\__,_|_| |_|_|\\_\\_|_| |_|\\__, | |___/\\__, |___/\\__\\___|_| |_| |_|\n                                    |___/       |___/");
  printf(RESET);

  usleep(500000);

  printf(BOLD);
  printf("\n\nBanking Login...\n\n");
  printf(RESET);

  // load data base config
  dbConfig config;
  loadingConfig(&config);

  usleep(500000);
  printf("\nLogin:\n Press 1 for client servicies\n Press 2 for admin servicies\nOption : ");



  char option;
  scanf("%c", &option);
  if (option == '1')
  {
    // user UI
    clientUIFunction();
  }
  else if (option == '2')
  {
    // admin UI
    adminUIFunction();
  }
  else
  {
    printf("Any jailbreak attempts are recorded!\n");
    // .log file registration
  }
  saveConfig(&config);
  displayConfig(&config);
  return 0;
}