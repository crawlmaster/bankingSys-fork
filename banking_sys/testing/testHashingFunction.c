#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_IBAN 25
#define INITIAL_VALUE 100
#define INITIAL_BANK_CAPACITY 1000
#define SEED 739

typedef struct node{
  long int ID;
  char IBAN[MAX_IBAN];
}node , *node_ptr;

node_ptr create_node(long int ID , char IBAN[MAX_IBAN]){
  node_ptr temp = malloc(sizeof(struct node));
  if(!temp) exit(1);
  temp->ID = ID;
  strncpy(temp->IBAN , IBAN , MAX_IBAN - 1);
  temp->IBAN[MAX_IBAN - 1] = '\0';
  return temp;
}

node_ptr *addNode(node_ptr *table , int *tableSize, long int ID , char IBAN[MAX_IBAN]){
  node_ptr temp_node = create_node(ID , IBAN);
  table[(*tableSize)++] = temp_node;
  return table;
}

int hashing_function(node_ptr node){
  int value = 0;
  for(int i = 0 ; i < (int)strlen(node->IBAN) ; ++i){
    value += node->IBAN[i];
  }
  int sum = node->ID + value;
  // while(sum >= INITIAL_BANK_CAPACITY)
  //   sum /=2;

  if(sum < 0) sum = -sum;
  return sum % INITIAL_BANK_CAPACITY;
}

int hashing_function_seed(node_ptr node , int seed){
  int string_length = (int)strlen(node->IBAN);
  unsigned long current_seed = (unsigned long)seed + node->ID;
  for(int i = 0 ; i < string_length ; ++i){
    unsigned int block = 0;
    for(int j = 0 ; j < 5 && ((i + j) < string_length) ; ++j)
      block += node->IBAN[i + j];
    current_seed = ((current_seed << 4) + current_seed) ^ block;
  }
  return (int)(current_seed % INITIAL_BANK_CAPACITY);
}

void find_best_seed(node_ptr *hashTable, int hashTable_size)
{
  int best_seed = 0;
  int best_seed_col = INITIAL_BANK_CAPACITY;     // Total coliziuni minim
  int best_seed_max_col = INITIAL_BANK_CAPACITY; // Lungime listă maximă minimă

  for (int seed_test = 0; seed_test < INITIAL_BANK_CAPACITY; ++seed_test)
  {
    int index_value[INITIAL_BANK_CAPACITY] = {0};
    for (int j = 0; j < hashTable_size; ++j)
    {
      int tempIndex = hashing_function_seed(hashTable[j], seed_test);
      index_value[tempIndex]++;
    }

    int currentSeedTotalCol = 0;
    int currentSeedMaxCol = 0;

    for (int i = 0; i < INITIAL_BANK_CAPACITY; ++i)
    {
      if (index_value[i] > 1)
      {
        currentSeedTotalCol += (index_value[i] - 1);
        if (index_value[i] > currentSeedMaxCol)
        {
          currentSeedMaxCol = index_value[i];
        }
      }
    }

    // cautam clusterul maxim cat mai mic
    if (currentSeedMaxCol < best_seed_max_col)
    {
      best_seed_max_col = currentSeedMaxCol;
      best_seed_col = currentSeedTotalCol;
      best_seed = seed_test;
    }
    // la clustere maxime egale, selectam numarul minim total de coliziuni
    else if (currentSeedMaxCol == best_seed_max_col && currentSeedTotalCol < best_seed_col)
    {
      best_seed_col = currentSeedTotalCol;
      best_seed = seed_test;
    }
  }

  printf("--- REZULTAT TEST SEED ---\n");
  printf("Cel mai bun seed gasit: %d\n", best_seed);
  printf("Dimensiune maxima cluster: %d clienți\n", best_seed_max_col);
  printf("Total coliziuni in tabela: %d\n", best_seed_col);
}

int main(void){
  node_ptr *hashTable = malloc(sizeof(node_ptr) * INITIAL_BANK_CAPACITY);
  int hashTable_size = 0;
  FILE *dataBase = fopen("tempDataBase.txt" , "r");
  if(!dataBase){
    printf("Eroare la deschiderea bazei de date\n");
    exit(1);
  }
  long int temp_id;
  char temp_iban[MAX_IBAN];
  
  while(fscanf(dataBase, "%ld %s" , &temp_id , temp_iban) == 2)
    addNode(hashTable , &hashTable_size, temp_id , temp_iban);
  
  // for(int i = 0 ; i < hashTable_size ; ++i){
  //   printf("Client Nr %d\nID : %ld\nIBAN : %s\n\n" , i + 1 , hashTable[i]->ID , hashTable[i]->IBAN);
  // }
  int *index_table = calloc(INITIAL_BANK_CAPACITY , sizeof(int));
  for(int i = 0 ;i < hashTable_size ; ++i){
    int index = hashing_function_seed(hashTable[i] , SEED);
    printf("Index : %d\n" , index);
    index_table[index]++;
  }
  printf("Distributia de coleziuni\n");
  bool flag = false;
  int total_colision = 0;
  int maxColDetected = 0;
  int remaining_indexs = 0;
  for(int i = 0 ; i <  INITIAL_BANK_CAPACITY; ++i)
    if(index_table[i] > 1){
      printf("Pe pozitia %d sa inregistrat o coleziuni de dim %d\n" , i + 1 , index_table[i]);
      flag = true;
      ++total_colision;
      if(index_table[i] > maxColDetected) maxColDetected = index_table[i];
    } else if(index_table[i] == 0) ++remaining_indexs;
  if(!flag) printf("Nu au fost inregistrate coleziuni !\n");
  else printf("Au fost detectate pentru un test de %d intrari , %d coleziuni\nNumarul maxim de coleziuni care se se gaseste in tabelul de disperie este %d\n" , hashTable_size , total_colision , maxColDetected);
  printf("Raman nepopulate %d intrari in hashTable , adica %.2lf procente din numarul total\n" , remaining_indexs , (double)remaining_indexs / INITIAL_BANK_CAPACITY * 100);
  // find_best_seed(hashTable , hashTable_size);
  return 0;
}
