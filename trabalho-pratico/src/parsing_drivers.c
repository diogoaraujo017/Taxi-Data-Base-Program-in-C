#include "drivers_structure.h"
#include <stdio.h>
#include "parsing_users.h"
#include "parsing_drivers.h"
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

void read_store_drivers(){
    FILE *driversF;
    char line[250];
    driversF = fopen("drivers.csv", "r");

    fgets(line, 250, driversF);

    while (fgets(line, 250, driversF)!=NULL){
        analisa_linha_drivers(line);
    }
    fclose(driversF);
}

void analisa_linha_drivers(char *line){
    char a[100], a1[100],a2[100],a3[100],a4[100],a5[100],a6[100],a7[100];
    int i,j;
    int aux=1;
    for(i=0,j=0;line[i]!='\0';i++,j++){
        if (line[i]==';'){

            a[j]='\0';

            switch (aux)
            {
            case 1:
                strcpy(a1,a);
                break;
            case 2:    
                strcpy(a2,a);
                break;
            case 3:
                strcpy(a3,a);
                break;
            case 4:    
                strcpy(a4,a);
                break;
            case 5:
                strcpy(a5,a);
                break;
            case 6:    
                strcpy(a6,a);
                break;
            case 7:    
                strcpy(a7,a);
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
    insert_hash_drivers(filtra(a1),filtra(a2),filtra(a3),a4[0],filtra(a5),filtra(a6),filtra(a7),filtra(a));

}
