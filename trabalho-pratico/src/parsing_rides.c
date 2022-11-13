#include "rides_structure.h"
#include <stdio.h>
#include "parsing_rides.h"
#include <string.h>


typedef struct{
    char id[MAX_INFO];
    char date[MAX_INFO];
    char driver[MAX_INFO];
    char user[MAX_INFO];
    char city[MAX_INFO];
    int distance;
    int score_user;
    int score_driver;
    double tip;
    char comment[MAX_INFO];  
} rides;

void rides_file_open(){
    FILE *rides;
    char line[150];
    init_hash_table();
    rides = fopen("rides.scv", "r");

    if(rides == NULL) return 1;

    fgets(line, 150, rides);

    while (fgets(line, 150, rides)){
        analisa_linha(line);
    }
}

void analisa_linha_rides(char line[150]){
    char a[100], a1[50],a2[50],a3[50],a4[50],a5[50],a6[50],a7[50],a8[50],a9[50];
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
            j=0;
        }
        a[j]=line[i];

    }
    rides r = {.id=convertToString(a1,50/sizeof(char)),
                 .date=convertToString(a2,50/sizeof(char)),
                 .driver=convertToString(a3,50/sizeof(char)),
                 .user=convertToString(a4,50/sizeof(char)),
                 .city=convertToString(a5,50/sizeof(char)),
                 .distance=a6[0],
                 .score_user=a7[0],
                 .score_driver=a8[0],
                 .tip=a9[0],
                 .comment=convertToString(a,50/sizeof(char))
                 };

    insert_hash_drivers(&r);

}



