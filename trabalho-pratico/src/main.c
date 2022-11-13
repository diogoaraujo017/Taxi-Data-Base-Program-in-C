#include <stdio.h>
#include <string.h>
#include "drivers_structure.h"
#include "rides_structure.h"
#include "users_structure.h"
#include "parsing_rides.h"
#include "parsing_rides.h"
#include "parsing_users.h"

int querie1(char line[100])
{
    char line2[100];
    int i;

    for (i = 2; line[i] != '>'; i++)
    {
        line2[i - 2] = line[i];
    }
    line2[i] = '\0';

    if (line2[0]=='0'){        //drivers
        drivers_file_open();
        procura_hash_drivers(line);
    }
    else{                      //username
        users_file_open();
        procura_hash_users(line);
    }                      
    //verifica_input(line);
}
void querie2(char line[100])
{
    char line2[100];
    int i;

    for (i = 2; line[i] != '>'; i++)
    {
        line2[i - 2] = line[i];
    }
    line2[i] = '\0';
}

void querie3(char line[100])
{
    char line2[100];
    int i;

    for (i = 2; line[i] != '>'; i++)
    {
        line2[i - 2] = line[i];
    }
    line2[i] = '\0';
}

int main(int argc, char const *argv[])
{
    char line[100];
    int querie = getchar();

    fgets(line, 100, stdin);

    switch (querie)
    {
    case '1':
        querie1(line);
        break;

    case '2':
        querie2(line);
        break;

    case '3':
        querie3(line);
        break;

    default:
        break;
    }

    return 0;
}

// FILE* drivers = fopen("drivers.csv", "r");

// int main (int argc, char const *argv[]){

//     char buffer[64];
//     int numero_linhas=0;
//     Parse x = init_user();

//     FILE* f = fopen("drivers.csv", "r");
//     if (f==NULL){
//         printf("Error opening file\n");
//         return 1;
//     }

//     while (fgets(buffer, 64, f)){
//         x = insert_user(x, strtok(buffer,"\n"));
//     }

//     char** user = get_all_users(x);

//     for (int i=1; i<=10000; i++){
//        //
//     }

//     return 0;
// }