//
// Created by claude delcroix on 30/11/2024.
//

#include "bank.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

void clearInputBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int menu() {
    printf("           MAIN MENU           \n");
    printf("1. Create account\n");
    printf("2. Login\n");
    int menu = 0;
    scanf("%d",&menu);
    clearInputBuffer();
    while(menu != 1 && menu!=2) {
        printf("Please enter the correct choice \n");
        scanf("%d",&menu);
        clearInputBuffer();
    }
    return menu;
}

void diviser() {
    for(int i = 0;i < 50;i++) {
        printf("-");
    }
    printf("\n");
}

char* initialisation() {
    char* string = (char*)malloc(MAX*sizeof(char));
    if(string == NULL) {
        fprintf(stderr,"allocation failed in initialisation\n");
        exit(EXIT_FAILURE);
    }
    return string;
}

void passWord(account* person) {
    int c,i = 0;
    while((c = getch()) != '\r' && i < MAX) {
        if(c == '\b' && i > 0) {
            printf("\b \b");
            i--;
        }else if(c != '\b') {
            person->password[i++] = c;
            printf("*");
        }
    }
    person->password[i] = '\0';
}

char* verifiePassword() {
    char* pass = initialisation();
    int c,i = 0;
    while((c = getch()) != '\r' && i < MAX) {
        if(c == '\b' && i > 0) {
            printf("\b \b");
            i--;
        }else if(c != '\b') {
            pass[i++] = c;
            printf("*");
        }
    }
    pass[i] = '\0';
    return pass;
}

bool isTrue(const char* person,const char* pass) {
    return (strcmp(person,pass) == 0);
}

account putInformation(account person) {
    printf("please fill the information\n");
    printf("First Name :    ");
    fgets(person.first_name,MAX,stdin);
    person.first_name[strcspn(person.first_name,"\n")] = '\0';
    printf("\nLast Name :    ");
    fgets(person.last_name,MAX,stdin);
    person.last_name[strcspn(person.last_name,"\n")] = '\0';
    printf("\nUserName :   ");
    fgets(person.username,MAX,stdin);
    person.username[strcspn(person.username,"\n")] = '\0';
    printf("\nPhone :   ");
    fgets(person.phone,MAX,stdin);
    person.phone[strcspn(person.phone,"\n")] = '\0';
    printf("\n Gender (M or F) :   ");
    scanf("%c",&person.gender);
    clearInputBuffer();
    printf("\nBirthDay :   ");
    fgets(person.DOB,MAX,stdin);
    person.DOB[strcspn(person.DOB,"\n")] = '\0';
    printf("\nPassword :   ");
    passWord(&person);

    printf("\n please put the password to confirm\n");
    char* pass = verifiePassword();

    if(strcmp(person.password,pass) != 0)
    while(isTrue(person.password,pass) != 0) {
        printf("the password is not correct please put the password again\n");
        pass = verifiePassword();
        free(pass);
    }
    userInFile(person.username);
    passwordInFile(person.password);

    printf("\n The account is created\n");
    printf("*****************SUCCESS***************\n");
    //free(pass);
    return person;
}

void userInFile(char* username) {
    FILE* user = fopen("username.txt","w");
    if(user == NULL) {
        perror("error opening file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(user,"%s",username);
    fclose(user);
    printf("\n\n *************Your username is updated***********\n\n");
}

void passwordInFile(char* password) {
    FILE *pass = fopen("password.txt","w");
    if(pass == NULL) {
        perror("error opening file\n");
        exit(EXIT_FAILURE);
    }
    printf("password : %s \n",password);
    fprintf(pass,"%s",password);
    fclose(pass);
    printf("\n\n *************Your password is updated***********\n\n");
}

void passWordAndUsernameInFile(char* passWord,char* userName) {
    FILE *user = fopen("username.txt","w");
    FILE *password = fopen("password.txt","w");
    if(user == NULL || password == NULL) {
        perror("error opening file\n");
        exit(EXIT_FAILURE);
    }
    //ecrire l'username dans le file
    fprintf(user,"%s",userName);
    printf("\n\n *************Your username is updated***********\n\n");
    //ecrire le password dans le file
    fprintf(password,"%s",passWord);
    printf("\n\n *************Your password is updated***********\n\n");
    fclose(user);
    fclose(password);
}

int menuAfterInformation(account person) {
    printf("\n Good Morning %s \n",person.first_name);
    printf("\n *******************MENU************************\n");
    printf("1. See my information\n");
    printf("2. Put Bank information\n");
    printf("3. Deposit money\n");
    printf("4. Take money\n");
    printf("5. Exit\n");
    int menu = 0;
    scanf("%d",&menu);
    clearInputBuffer();

    while(menu < 1 || menu > 5) {
        printf("\n Please enter the correct choice \n");
        scanf("%d",&menu);
        clearInputBuffer();
    }
    return menu;
}

void printInfo(account person) {
    printf("\n First Name : %s",person.first_name);
    printf("\n Last Name : %s",person.last_name);
    printf("\n Username :  %s",person.username);
    printf("\n Phone :   %s",person.phone);
    printf("\n Gender : %c",person.gender);
    printf("\n BirthDay : %s",person.DOB);
    printf("\n\n");
}

void choiceAfterInformation(const int m,account person) {
    switch (m) {
        case 1 :
            printInfo(person);
            break;
        case 2 :
            diviser();
            printf("1.put bank information\n2.See bank information\n3.My solde\n");
            short int ch = 0;
            scanf("%hd",&ch);
        clearInputBuffer();
            if(ch == 1) {
                bankAccount(&person);
                bankToFile(person,"client.txt");
            }else if(ch == 2) {
                person = readBankFromFile(person,"client.txt");
                bankInfo(person);
            }else {
                showSolde(person,"client.txt");
            }
        break;
        case 3 :
            diviser();
            printf("Put the amount : ");
            long amount = 0;
            scanf("%ld",&amount);
            person = readBankFromFile(person,"client.txt");
            person.bankAccount.solde += amount;
            newSolde(&person,"client.txt");
            break;
        case 4 :
            diviser();
            printf("Put the amount to take from your account : ");
            long take = 0;
            scanf("%ld",&take);
            person = readBankFromFile(person,"client.txt");
            person.bankAccount.solde -= take;
            newSolde(&person,"client.txt");
            break;
        case 5 :
            diviser();
            printf("\t\t GOOD BYE \n");
        exit(0);
        default:
            printf("Invalid choice!\n");
    }
}

char* realPassword() {
    FILE* password = fopen("password.txt","r");
    if(password == NULL) {
        perror("error opening file \n");
        exit(EXIT_FAILURE);
    }
    char* real = initialisation();
    fscanf(password,"%s",real);
    fclose(password);
    return real;
}

char* realUser() {
    FILE* username = fopen("username.txt","r");
    if(username == NULL) {
        perror("error opening file\n");
        exit(EXIT_FAILURE);
    }
    char* real = initialisation();
    fscanf(username,"%s",real);
    fclose(username);
    return real;
}

char* username() {
    printf("Enter the username : ");
    printf("\n");
    char* user = initialisation();
    if(fgets(user,MAX,stdin) == NULL) {
        fprintf(stderr,"failled in username\n");
        exit(EXIT_FAILURE);
    }
    size_t len = strlen(user);
    if(len > 0 && user[len - 1] == '\n') {
        user[len - 1] = '\0';
    }
    return user;
}

char* passWordToConnect() {
    printf("Enter your password : ");
    printf("\n");
    char* password = initialisation();
    int c, i = 0;

    while((c = getch()) != '\r' && i < 25) {
        if(c == '\b' && i > 0) {
            printf("\b \b");
            i--;
        }else if(c != '\b') {
            password[i++] = c;
            printf("*");
        }
    }
    password[i] = '\0';

    return password;
}

void writeToFile(account person,const char* filename) {
    FILE* file = fopen(filename,"a");
    if(file == NULL) {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file,"First Name: %s\nLast Name : %s\nUsername: %s\nPhone: %s\nGender: %c\nBirthDay: %s\n\n",person.first_name,person.last_name,person.username,person.phone,person.gender,person.DOB);
    fclose(file);
}

void placeTheEndLine(char* string) {
    string[strlen(string)-1] = '\0';
}

account readFromFile(account person,const char* filename) {
    FILE* file = fopen(filename,"r");
    if(file == NULL) {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    printf("recuperation of information.\n");
    while(fscanf(file,"First Name: %[^\n]\nLast Name : %[^\n]\nUsername: %[^\n]\nPhone: %[^\n]\nBirthDay: %[^\n]\n\n",person.first_name,person.last_name,person.username,person.phone,person.DOB) == 5) {
        printf(".");
    }
    /*placeTheEndLine(person.phone);
    placeTheEndLine(person.DOB);
    printf("\n");*/
    fclose(file);
    return person;
}

account readFromFileB(account person,const char* filename) {
    FILE *file = fopen(filename,"r");
    if(file == NULL) {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    printf("recuperation of information.\n");

    char buffer[256];
    char gender[1];
    while(fgets(buffer,sizeof(buffer),file)) {
        if(sscanf(buffer,"First Name: %[^\n]",person.first_name) == 1)continue;
        if(sscanf(buffer,"Last Name : %[^\n]",person.last_name) == 1)continue;
        if(sscanf(buffer,"Username: %[^\n]",person.username) == 1)continue;
        if(sscanf(buffer,"Phone : %[^\n]",person.phone) == 1)continue;
        if(sscanf(buffer,"Gender: %[^\n]",gender) == 1)continue;
        if(sscanf(buffer,"BirthDay: %[^\n]",person.DOB) == 1)continue;
    }
    fclose(file);
    person.gender = gender[0];
    return person;
}

//readFromFileB est meilleure que la premiere version du code

void bankAccount(account* person) {
    printf("put the card number : ");
    fgets(person->bankAccount.numberCard,MAX,stdin);
    person->bankAccount.numberCard[strcspn(person->bankAccount.numberCard,"\n")] = '\0';

    printf("\nput the valid date : ");
    fgets(person->bankAccount.valid,MAX,stdin);
    person->bankAccount.valid[strcspn(person->bankAccount.valid,"\n")] = '\0';

    printf("\nPut the valid cmc : ");
    fgets(person->bankAccount.cmc,MAX,stdin);
    person->bankAccount.cmc[strcspn(person->bankAccount.cmc,"\n")] = '\0';

    long long x = 0;
    printf("\nPut your solde : ");
    scanf("%ld",&x);
    person->bankAccount.solde = x;
    printf("it's just a joke :) \n");

    diviser();
    printf("Your bank account is created successfully\n");
}

void bankToFile(account person,const char* filename) {
    FILE* file = fopen(filename,"a");
    if(file == NULL) {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file,"Card number : %s\nValid date : %s\nCMC: %s\nSolde : %ld\n\n",person.bankAccount.numberCard,person.bankAccount.valid,person.bankAccount.cmc,person.bankAccount.solde);
    fclose(file);
    diviser();
}

account readBankFromFile(account person,const char* filename) {
    FILE* file = fopen(filename,"r");
    if(file == NULL) {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while(fgets(buffer,sizeof(buffer),file)) {
        if(sscanf(buffer,"Card number : %[^\n]",person.bankAccount.numberCard) == 1)continue;
        if(sscanf(buffer,"Valid date : %[^\n]",person.bankAccount.valid) == 1)continue;
        if(sscanf(buffer,"CMC: %[^\n]",person.bankAccount.cmc) == 1)continue;
        if(sscanf(buffer,"Solde : %ld",&person.bankAccount.solde) == 1)continue;
    }
    fclose(file);
    return person;
}

void bankInfo(const account person) {
    printf("Card number : %s\n",person.bankAccount.numberCard);
    printf("Valid date : %s\n",person.bankAccount.valid);
    printf("CMC : %s\n",person.bankAccount.cmc);
    printf("Solde : %ld\n",person.bankAccount.solde);
}

void showSolde(account person,const char* filename) {
    person = readBankFromFile(person,filename);
    diviser();
    printf("Please don't show your solde to anyone \n");
    printf("Solde : %ld $\n",person.bankAccount.solde);
    diviser();
}

void newSolde(account* person,const char* filename) {
    if(filename == NULL) {
        perror("No such directory...\n");
        exit(EXIT_FAILURE);
    }
    FILE* file = fopen(filename,"a");
    if(file == NULL) {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file,"Solde : %ld",person->bankAccount.solde);
}
