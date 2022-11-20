#include "users_structure.h"
#include <stdio.h>
#include "parsing_users.h"
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

char* filtra(char *init,char *dest){
    int i;
    for(i=0;init[i]!='\0';i++){
        dest[i]=init[i];
    }
    dest[i]='\0';
    return dest;
}

void read_store_users(){
    FILE *usersF;
    char line[250];
    usersF = fopen("users.csv", "r");

    fgets(line, 250, usersF);

    while (fgets(line, 250, usersF)!=NULL){
        analisa_linha_users(line);
       }
    fclose(usersF);
}

void analisa_linha_users(char *line){
    char *a,*a1,*a2,*a4,*a5,*a6;
    char a3;
    a=malloc(sizeof(line));
    a1=malloc(sizeof(line));
    a2=malloc(sizeof(line));
    a4=malloc(sizeof(line));
    a5=malloc(sizeof(line));
    a6=malloc(sizeof(line));

    int i,j;
    int aux=1;
    for(i=0,j=0;line[i]!='\0';i++,j++){
        if (line[i]==';'){

            a[j]='\0';

            switch (aux)
            {
            case 1:
                filtra(a,a1);
                break;
            case 2:    
                filtra(a,a2);
                break;
            case 3:
                a3=a[0];
                break;
            case 4:    
                filtra(a,a4);
                break;
            case 5:
                filtra(a,a5);
                break;
            case 6:
                filtra(a,a6);
                break;
            default:
                break;
            }
            aux++;
            j=-1;
        }
        else a[j]=line[i];

    }
    a[j-1]='\0';
    insert_hash_users(a1,a2,a3,a4,a5,a6,a);
}

