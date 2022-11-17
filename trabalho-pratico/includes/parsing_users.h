#ifndef PARSING_USERS_H
#define PARSING_USERS_H

#define MAX_INFO 50
#define N_LINHAS1 100000

typedef struct{
    char username[MAX_INFO];
    char name[MAX_INFO];
    char birth_day[MAX_INFO];
    char account_creation[MAX_INFO]; 
    char pay_method[MAX_INFO];
    char account_status[MAX_INFO];
}users;


void read_store_users();
void analisa_linha_users(char line[150]);

#endif