//
// Created by claude delcroix on 30/11/2024.
//

#ifndef BANK_H
#define BANK_H
#include <stdbool.h>
int menu() ;
#define MAX 20

typedef struct account account;
struct account {
    char first_name[MAX];
    char last_name[MAX];
    char username[MAX];
    char phone[MAX];
    char gender;
    char DOB[MAX];
    char password[MAX];
};

void diviser();
char* initialisation();
void passWord(account* person);
char* verifiePassword() ;
bool isTrue(const char* person,const char* pass);
account putInformation(account person);
void clearInputBuffer();
int menuAfterInformation(account person);
void printInfo(account person);
void choiceAfterInformation(const int m,const account person);
void passWordAndUsernameInFile(char* passWord,char* userName);
void passwordInFile(char* password);
void userInFile(char* username);
char* realPassword();
char* realUser();
char* passWordToConnect();
char* username();
void writeToFile(account person,const char* filename);
account readFromFile(account person,const char* filename);
void placeTheEndLine(char* string);

#endif //BANK_H
