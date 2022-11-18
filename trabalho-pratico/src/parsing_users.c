#include "users_structure.h"
#include <stdio.h>
#include "parsing_users.h"
#include <string.h>
#include <dirent.h>

void read_store_users(){
    FILE *usersF;
    char line[150];
    usersF = fopen("users.scv", "r");

    fgets(line, 150, usersF);

    while (fgets(line, 150, usersF)){
        analisa_linha_users(line);
       }
    fclose(usersF);
}

void analisa_linha_users(char line[150]){
    char a[50], a1[50],a2[50],a3[50],a4[50],a5[50],a6[50];
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
            default:
                break;
            }

            aux++;
            j=0;
        }
        a[j]=line[i];

    }
    users u = {.username={*a1},
               .name={*a2},
               .gender=a3[0],
               .birth_day={*a4},
               .account_creation={*a5},
               .pay_method={*a6},
               .account_status={*a}
              };

    insert_hash_users(&u);

}


