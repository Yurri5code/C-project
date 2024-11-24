#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 26

char* initialisation() {
    char* string = (char*)malloc(MAX * sizeof(char));
    if (string == NULL) {
        fprintf(stderr, "allocation failed in initialisation\n");
        exit(EXIT_FAILURE);
    }
    return string;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char* userName() {
    printf("\n Entrez votre nom d'utilisateur\n");
    printf(" nom :   ");
    char* user = initialisation();
    char* isOk = fgets(user, MAX, stdin);
    if (isOk == NULL) {
        fprintf(stderr, "isOk failed\n");
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(user);
    if (len > 0 && user[len - 1] == '\n') {
        user[len - 1] = '\0';
    }

    return user;
}

char* passWord() {
    printf("\n Entrez votre mot de passe :    ");
    char* password = initialisation();

    int c, i = 0;
    while ((c = getch()) != '\r' && i < 25) {
        if (c == '\b' && i > 0) {
            printf("\b \b");
            i--;
        } else if (c != '\b') {
            password[i++] = c;
            printf("*");
        }
    }
    password[i] = '\0';

    return password;
}

void userInFile(char* user) {
    FILE* ptr = fopen("username.txt", "w");
    if (ptr == NULL) {
        perror("error opening file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(ptr, "%s", user);
    fclose(ptr);
    printf("Votre nom d'utilisateur a ete configure avec succes...\n");
}

void passwordInFile(char* pass) {
    FILE* ptr = fopen("password.txt", "w");
    if (ptr == NULL) {
        perror("error opening file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(ptr, "%s", pass);
    fclose(ptr);
    printf("Votre mot de passe a ete configure avec succes...\n");
}

bool isTrue(const char* s, const char* t) {
    return (strcmp(s, t) == 0);
}

char* realPassword() {
    FILE* ptr = fopen("password.txt", "r");
    if (ptr == NULL) {
        perror("error opening file\n");
        exit(EXIT_FAILURE);
    }
    char* real = initialisation();
    fscanf(ptr, "%s", real);
    fclose(ptr);
    return real;
}

char* realUser() {
    FILE* ptr = fopen("username.txt", "r");
    if (ptr == NULL) {
        perror("error opening file\n");
        exit(EXIT_FAILURE);
    }
    char* real = initialisation();
    fscanf(ptr, "%s", real);
    fclose(ptr);
    return real;
}

short menu() {
    printf("Bonjour et bienvenue \n");
    printf("Choisissez une variante\n");
    printf("1. Creer un compte\n2. Se connecter\n");
    short choice = 0;
    scanf("%hd", &choice);
    clearInputBuffer(); // Vider le buffer d'entrée après scanf
    while(choice < 1 || choice > 2) {
        printf("your choice is not correct\n Please choose again\n");
        scanf("%hd",&choice);
        clearInputBuffer();
    }
    return choice;
}

int main(void) {
    const short choice = menu();
    if (choice == 1) {
        char* name = userName();
        userInFile(name);
        char* pass = passWord();
        passwordInFile(pass);
        free(name);
        free(pass);
    } else {
        printf("Veuillez vous connecter a votre compte\n");

        char* realUsername = realUser();
        char* realPassWord = realPassword();
        //debug : printf("%s \n %s\n",realUsername,realPassWord);
        char * connectName;
        char* connectPass;
        bool loggedIn = false;

        do {
            connectName = userName();
            connectPass = passWord();

            if (!isTrue(connectName, realUsername) || !isTrue(connectPass, realPassWord)) {
                printf("\n************ Mot de passe ou nom d'utilisateur incorrect******\n\n");
                free(connectName);
                free(connectPass);
                printf("Please put the correct password or username\n");
            } else {
                loggedIn = true;
            }
        } while (!loggedIn);

        printf("\n\n ********Bienvenue ***********\n\n");
        free(connectName);
        free(connectPass);
    }

    return 0;
}
