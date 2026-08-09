#ifndef CONFIG_DATABASE_H
#define CONFIG_DATABASE_H

#include <stdio.h>
#include <stdint.h>

#define CONFIG_KW "CFMT"
#define FILE_PATH "dataBase/config.meta"
#pragma pack(push, 1)

typedef struct
{
  char headerKw[5]; // verify if we have the rigth file
  __uint8_t isEncrypted;
  __uint8_t cypherShift;
  __uint32_t numberOfClients;
  __uint32_t lastID;
  __uint64_t createdTime;
  __uint64_t lastTimeModified;
} dbConfig;

#pragma pack(pop)


void saveConfig(dbConfig *config);
short int createConfigFile(dbConfig *config);
short int loadConfigFile(dbConfig *config);
void verifyFile(dbConfig *fileConfig);
void formatTime(__uint64_t timestamp, char *buffer, size_t bufferSize);
void displayConfig(dbConfig *config);

#endif