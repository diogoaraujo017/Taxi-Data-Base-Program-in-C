#include "rides_structure.h"
#include "parsing_rides.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


void read_store_rides(){
    FILE *ridesF;
    char line[150];
    ridesF = fopen("rides.csv", "r");

    fgets(line, 150, ridesF);

    while (fgets(line, 150, ridesF)!=NULL){
        analisa_linha_rides(line);
    }
    fclose(ridesF);
}

void analisa_linha_rides(char line[]){
    char a[100], a1[100],a2[100],a3[100],a4[100],a5[100],a6[100],a7[100],a8[100],a9[100];
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
            case 8:    
                strcpy(a8,a);
                break;
            case 9:    
                strcpy(a9,a);
                break;
            default:
                break;
            }

            aux++;
            j=-1;
        }
        else a[j]=line[i];

    }
    a[j]='\0';
    char *ptr;
    rides r = {  .id=a1,
                 .date=a2,
                 .driver=a3,
                 .user=a4,
                 .city=a5,
                 .distance=atoi(a6),
                 .score_user=(a7[0]-'0'),
                 .score_driver=(a8[0]-'0'),
                 .tip=strtod(a9,&ptr),
                 .comment=a
                 };

    insert_rides_drivers(&r);
    insert_rides_users(&r);

}



