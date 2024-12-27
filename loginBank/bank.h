//
// Created by claude delcroix on 30/11/2024.
//

#ifndef BANK_H
#define BANK_H
#include <stdbool.h>
int menu() ;
#define MAX 20

typedef struct bank bank;
struct bank {
    char numberCard[17];
    char valid[6];
    char cmc[4];
    long solde;
};


typedef struct account account;
struct account {
    char first_name[MAX];
    char last_name[MAX];
    char username[MAX];
    char phone[MAX];
    char gender;
    char DOB[MAX];
    char password[MAX];
    bank bankAccount;
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
void choiceAfterInformation(const int m,account person);
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
account readFromFileB(account person,const char* filename);
void bankAccount(account* person);
void bankToFile(account person,const char* filename);
void bankInfo(const account person);
account readBankFromFile(account person,const char* filename);
void showSolde(account person,const char* filename);
void newSolde(account* person,const char* filename);

#endif //BANK_H
