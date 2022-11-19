#include "users_structure.h"
#include <stdio.h>
#include "parsing_users.h"
#include <string.h>
#include <dirent.h>

void read_store_users(){
    FILE *usersF;
    char line[150];
    usersF = fopen("users.csv", "r");

    fgets(line, 150, usersF);

    while (fgets(line, 150, usersF)!=NULL){
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
            j=-1;
        }
        else a[j]=line[i];

    }
    a[j]='\0';
    users u = {.username=a1,
               .name=a2,
               .gender=a3[0],
               .birth_day=a4,
               .account_creation=a5,
               .pay_method=a6,
               .account_status=a
              };

    insert_hash_users(&u);

}


