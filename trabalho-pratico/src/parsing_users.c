#include "users_structure.h"
#include <stdio.h>
#include "parsing_users.h"
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

char* filtra(char dest[]){
    int i,N=0;
    for(i=0;dest[i]!='\0';i++){
        N++;
    }
    char *str = malloc(N+1);
    for(i=0;dest[i]!='\0';i++){
        str[i]=dest[i];
    }
    str[i]='\0';
    return str;
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

void analisa_linha_users(char line[]){
    char a[100], a1[100],a2[100],a3[100],a4[100],a5[100],a6[100];
    int i,j;
    int aux=1;
    for(i=0,j=0;line[i]!='\0';i++,j++){
        if (line[i]==';'){

            a[j]='\0';

            switch (aux)
            {
            case 1:
                strcpy(a1, a);
                break;
            case 2:    
                strcpy(a2, a);
                break;
            case 3:
                strcpy(a3, a);
                break;
            case 4:    
                strcpy(a4, a);
                break;
            case 5:
                strcpy(a5, a);
                break;
            case 6:
                strcpy(a6, a);
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
    insert_hash_users(filtra(a1),filtra(a2),a3[0],filtra(a4),filtra(a5),filtra(a6),filtra(a));
}


