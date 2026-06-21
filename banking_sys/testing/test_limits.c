#include <stdio.h>
#include <limits.h>
#include <float.h>

int count_digits(long value){
  int counter = 0;
  while(value != 0){
    ++counter;
    value /= 10;
  }
  return counter;
}

int main(void){
//  unsigned long a = 123435432422312243;
  long int b = LONG_MAX;
  printf("Unsigned long max size : %lud\n" , ULONG_MAX);
  printf("Long int max size : %lu\n" , b);
  printf("Valoarea maxima pentru double : %lf\n" , DBL_MAX);
  printf("Unsigned long digit counter : %d\n" , count_digits(LONG_MAX));
  
  // printf("What happends when addition gives OverFlow ?");
  // printf("%d" , INT_MAX + 1);  
  return 0;
}
