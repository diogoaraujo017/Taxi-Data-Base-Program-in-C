#include "drivers_structure.h"
#include <stdio.h>
#include "parsing_drivers.h"
#include <string.h>
#include <dirent.h>



void read_store_drivers(){
    FILE *driversF;
    char line[150];
    driversF = fopen("drivers.scv", "r");

    fgets(line, 150, driversF);

    while (fgets(line, 150, driversF)){
        analisa_linha_drivers(line);
    }
    fclose(driversF);
}

void analisa_linha_drivers(char line[150]){
    char a[50], a1[50],a2[50],a3[50],a4[50],a5[50],a6[50],a7[50];
    int i,j;
    int aux=1;
    for(i=0,j=0;(i<=line[i])!='\0';i++,j++){
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
            j=0;
        }
        a[j]=line[i];

    }
    drivers d = {.id={*a1},
                 .name={*a2},
                 .birth_day={*a3},
                 .gender=a4[0],
                 .car_class={*a5},
                 .license_plate={*a6},
                 .account_creation={*a7},
                 .account_status={*a}
                 };

    insert_hash_drivers(&d);

}



