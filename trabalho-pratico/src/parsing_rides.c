#include "rides_structure.h"
#include "parsing_rides.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


void read_store_rides(){
    FILE *ridesF;
    char line[150];
    ridesF = fopen("rides.scv", "r");

    fgets(line, 150, ridesF);

    while (fgets(line, 150, ridesF)){
        analisa_linha_rides(line);
    }
    fclose(ridesF);
}

void analisa_linha_rides(char line[150]){
    char a[100], a1[50],a2[50],a3[50],a4[50],a5[50],a6[50],a7[50],a8[50],a9[50];
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
            case 8:    
                strcpy(a8,a);
                if (a[i+1]=='\0'){
                    a9[0]='\0';
                }
                break;
            case 9:    
                strcpy(a9,a);
                break;
            default:
                break;
            }

            aux++;
            j=0;
        }
        a[j]=line[i];

    }
    char *ptr;
    rides r = {  .id={*a1},
                 .date={*a2},
                 .driver={*a3},
                 .user={*a4},
                 .city={*a5},
                 .distance=atoi(a6),
                 .score_user=(a7[0]-'0'),
                 .score_driver=(a8[0]-'0'),
                 .tip=strtod(a9,&ptr),
                 .comment={*a}
                 };

    insert_rides_drivers(&r);
    insert_rides_users(&r);

}



