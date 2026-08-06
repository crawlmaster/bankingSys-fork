# **Rezultate functii hashing :**

Toate testele pentru functiile de mai jos au fost realizate pe o baza de date de test cu 500 de intrari.
Urmeaza fiecare versiune si cate coleziuni produce fiecare pentru baza de date respectiva.<br>
Baza de date se afla la : *./tempDataBase.txt*
<br>*(Rezultatele sunt direct luate din terminal , ca output a testelor!)*

## Prima versiune

```c
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
```
## Rezultate :
 -  
 - Au fost detectate pentru un test de 1000 intrari , **265 coleziuni**.<br>
 - Numarul maxim de coleziuni care se se gaseste in tabelul de disperie este **6**.

## Version 2 : Adaugare seed si opearatii pe biti
```c

int hashing_function_seed(node_ptr node ){
  unsigned int seed = 312;
  int string_length = (int)strlen(node->IBAN);
  for(int i = 0 ; i < string_length ; ++i){
    int block = 0;
    for(int j = 0 ; j < 5 && ((i + j) < string_length) ; ++j)
      block += node->IBAN[i + j];
    seed = ((seed < 1) + seed) ^ block;
  }
  return (int)(seed % INITIAL_BANK_CAPACITY);
}

```

## Rezultate : 
- Au fost detectate pentru un test de 1000 intrari , **222 coleziuni**
 - Numarul maxim de coleziuni care se se gaseste in tabelul de disperie este **13**

Mentiuni : <br>
Rezultatele de mai sus au fost generate cu un seed = 312 , cu siguranta la un seed ales *bine* putem genera mai putin coleziuni.

Dupa cum am mentionat , seed - ul clar influenteaza coleziunile , de aceea am facut aceasta functie :
```c

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
```

Iar functia de hashing sa modificat in :
```C
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
```

Modificarile aduse trateaza cazul *return negative_value* , ceea ce ar fi provocat **SEGFAULT uri** in program. <br>
Astfel pentru o shiftare de 4 bytes per time , avem rezultatele urmatoare : <br>
 * Au fost detectate pentru un test de 1000 intrari , **260 coleziuni**
 * Numarul maxim de coleziuni care se se gaseste in tabelul de disperie este **4**

Am putut minimiza dimensiunea listei de coleziune , in schimb s au marit numarul de coleziuni.
Am nevoie de o functie care ar putea avea o disperise mai buna , in loc sa ramana 30-40% din spatiu liber , trebuie sa folosim aproape la maxim tot spatiul , reducand de la 30-40% la 5-10%.

O posibila solutie ar fi modificarea functiei de hashing care ar putea acoperi o mai mare "zona" din vector , dupa care o mica optimizare ar fi si tratarea coleziunilor , dar nu cu metoda `Chaining`.