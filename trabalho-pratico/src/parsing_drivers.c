#include "drivers_structure.h"
#include <stdio.h>
#include "parsing_drivers.h"
#include <string.h>


typedef struct{
    char id[MAX_INFO];
    char name[MAX_INFO];
    char birth_day[MAX_INFO];
    char gender;
    char car_class[MAX_INFO];
    char license_plate[MAX_INFO];
    char acount_creation[MAX_INFO];  
} drivers;

void drivers_file_open(){
    FILE *drivers;
    char line[150];
    init_hash_table();
    drivers = fopen("drivers.scv", "r");

    if(drivers == NULL) return 1;

    fgets(line, 150, drivers);

    while (fgets(line, 150, drivers)){
        analisa_linha(line);
        // func(analisa linha)
    }
}

void analisa_linha(char line[150]){
    char a[50], a1[50],a2[50],a3[50],a4[50],a5[50],a6[50];
    int i,j;
    int aux=1;
    for(i=0,j=0;i<=line[i]!='\0';i++,j++){
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
            default:
                break;
            }

            aux++;
            j=0;
        }
        a[j]=line[i];

    }
    drivers d = {.id=convertToString(a1,50/sizeof(char)),
                 .name=convertToString(a2,50/sizeof(char)),
                 .birth_day=convertToString(a3,50/sizeof(char)),
                 .gender=a4[0],
                 .car_class=convertToString(a5,50/sizeof(char)),
                 .license_plate=convertToString(a6,50/sizeof(char)),
                 .acount_creation=convertToString(a,50/sizeof(char))
                 };

    insert_hash_drivers(&d);

}


