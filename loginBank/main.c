#include <stdio.h>
#include <stdlib.h>
#include "bank.h"


int main(void)
{
    const short returnFirstMenu = menu();
    account person;
    person.gender = 'M';
    const char* filename = "client.txt";
    if(returnFirstMenu == 1) {

        person = putInformation(person);
        writeToFile(person,filename);
        int menuAfter = menuAfterInformation(person);
        choiceAfterInformation(menuAfter,person);
    }else {
        printf("Please put your username and password to be connect to your account\n");
        char* realUsername = realUser();
        char* realPass = realPassword();
        //debug : printf("username : %s and password : %s \n",realUsername,realPass);
        bool loggedIn = false;

        do {
            char* connectName = username();
            char* connectPass = passWordToConnect();
            //debug : printf("connectName : %s and connectPass : %s \n",connectName,connectPass);
            if(!isTrue(connectName,realUsername) || !isTrue(connectPass,realPass)) {
                printf("\n**************** the password or username is not correct *****************\n\n");

                printf("please put the correct password or username\n");
            }else {
                loggedIn = true;
            }
            free(connectName);
            free(connectPass);
        }while(!loggedIn);
        printf("\n\n************ Good morning %s ***************\n",person.username);
        person = readFromFile(person,filename);

        choiceAfterInformation(menuAfterInformation(person),person);
    }

    return 0;
}

//je suis au niveau de la fonction readFromFile pour recuperer le informations du fichier
//
