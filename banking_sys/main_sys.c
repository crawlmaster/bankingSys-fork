#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// DEFINE SECTION
#define MAX_USER_NAME_LENGHT 60
#define MAX_USER_PASS_LENGHT 64
#define MAX_IBAN_LENGHT 25


typedef struct client{
  char userName[MAX_USER_NAME_LENGHT]; 
  char password[MAX_USER_PASS_LENGHT];
  long int ID; //clients ID - CNP
  char IBAN[MAX_IBAN_LENGHT];
  double sold;
}userAcc , *userAcc_ptr;


//void cript_database (different file with separated header files)
//void decript_database (same as cript_database function)


//userAcc_ptr __add_client_to_dataBase

//userAcc_ptr __delete_client_from_dataBase

//User acctions :
//userAcc_ptr solt_integoration
//userAcc_ptr withdraw_from_account
//userAcc_ptr add_money_to_account
//void convert_iban_PDF(struct clinet)

// TODO: Aux function:
// search_client_in_dataBase

// Functions for UI
void clientUIFunction(){
  // long int clientID;
  
  // printf("Enter you credentials\nName %s: \nID : %ld");
  // while(1){
    printf("\tYou're in the client section of the program!\n");
    return ;
  // }
}

void adminUIFunction(){
  printf("\tYou're in the admin section of the program!\n");
}

int main(void){

  printf("Banking Login \n Press 1 for client servicies\n Press 2 for admin servicies\nOption : ");
  char option ;
  scanf("%c",  &option);
  if(option == '1'){
    //user UI
    clientUIFunction();
  } else if(option == '2'){
    // admin UI
    adminUIFunction();
  } else {
    printf("Any jailbreak attempts are recorded!\n");
    // .log file registration
  }

  return 0;
}
