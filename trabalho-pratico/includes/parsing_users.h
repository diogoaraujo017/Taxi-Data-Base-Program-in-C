#ifndef PARSING_USERS_H
#define PARSING_USERS_H

#define MAX_INFO 100
#define N_LINHAS1 100000

typedef struct{
    char *username;
    char *name;
    char gender;
    char *birth_day;
    char *account_creation; 
    char *pay_method;
    char *account_status;
}users;

char* filtra(char dest[]);
void read_store_users();
void analisa_linha_users(char line[150]);

#endif