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

void choiceAfterInformation(const int m,const account person) {
    switch (m) {
        case 1 :
            printInfo(person);
            break;

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
    while(fscanf(file,"First Name: %[^\n]\nLast Name : %[^\n]\nUsername: %[^\n]\nPhone: %c\nGender: %[^\n]\nBirthDay: %[^\n]\n\n",person.first_name,person.last_name,person.username,person.phone,person.gender,person.DOB) == 6) {
        printf(".");
    }
    /*placeTheEndLine(person.phone);
    placeTheEndLine(person.DOB);
    printf("\n");*/
    fclose(file);
    return person;
}
