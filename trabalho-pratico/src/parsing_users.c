#include "users_structure.h"
#include <stdio.h>
#include "parsing_users.h"
#include <string.h>


typedef struct{
    char username[MAX_INFO];
    char name[MAX_INFO];
    char birth_day[MAX_INFO];
    char account_creation[MAX_INFO]; 
    char pay_method[MAX_INFO];
    char account_status[MAX_INFO];
}users;

void users_file_open(){
    FILE *users;
    char line[150];
    init_hash_table_users();
    users = fopen("drivers.scv", "r");

    if(users == NULL) return 1;

    fgets(line, 150, users);

    while (fgets(line, 150, users)){
        analisa_linha(line);
       }
}

void analisa_linha(char line[150]){
    char a[50], a1[50],a2[50],a3[50],a4[50],a5[50];
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
            default:
                break;
            }

            aux++;
            j=0;
        }
        a[j]=line[i];

    }
    users u = {.username=convertToString(a1,50/sizeof(char)),
               .name=convertToString(a2,50/sizeof(char)),
               .birth_day=convertToString(a3,50/sizeof(char)),
               .account_creation=convertToString(a4,50/sizeof(char)),
               .pay_method=convertToString(a5,50/sizeof(char)),
               .account_status=convertToString(a,50/sizeof(char))
              };

    insert_hash_drivers(&u);

}


