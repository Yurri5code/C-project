#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 26

char* initialisation() {
    char* string = (char*)malloc(MAX * sizeof(char));
    if (string == NULL) {
        fprintf(stderr, "allocation failed in initialization\n");
        exit(EXIT_FAILURE);
    }
    return string;
}

void firstProgramme() {
    printf("Bienvenue dans le coffre fort\n");
    printf("Entrez un mot de passe ne depassant pas 25 caracteres\n");
}

char* passWord() {
    printf("\nEntrez votre mot de passe : ");
    char* password = initialisation();

    int c = 0, i = 0;
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
    printf("\n");

    return password;
}

void passwordInFile(char* pass) {
    FILE* ptr = fopen("passeword1.txt", "w");
    if (ptr == NULL) {
        perror("error opening file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(ptr, "%s", pass);
    fclose(ptr);
    printf("Votre mot de passe a ete configure avec succes...\n");
}

bool isPassWord(const char* enterPass, const char* realPass) {
    return (strcmp(enterPass, realPass) == 0);
}

char* realPassWord() {
    FILE* ptr = fopen("passeword1.txt", "r");
    if (ptr == NULL) {
        perror("error opening file\n");
        exit(EXIT_FAILURE);
    }
    char* realPassWord = initialisation();
    fscanf(ptr, "%s", realPassWord);
    fclose(ptr);
    return realPassWord;
}

int main(void) {
    firstProgramme();

    char* firstPass = passWord();
    passwordInFile(firstPass);
    free(firstPass);

    char* realString = realPassWord();
    char* string;

    do {
        string = passWord();
        if (!isPassWord(string, realString)) {
            printf("\n****** Mot de passe incorrect ******");
            free(string);
        }
    } while (!isPassWord(string, realString));

    printf("\n****** Mot de passe correct ******\n");
    printf("\n****** SUCCES *****\n");

    free(string);
    free(realString);
    return 0;
}
