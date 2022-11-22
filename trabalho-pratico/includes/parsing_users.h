#ifndef PARSING_USERS_H
#define PARSING_USERS_H

#define MAX_INFO 100
#define N_LINHAS1 100000

typedef struct{
    char *username;          // Username do user.
    char *name;              // Nome do user.
    char gender;             // Sexo do user.
    char *birth_day;         // Data de nascimento do user.
    char *account_creation;  // Data da criacao da conta do user.
    char *pay_method;        // Metodo de pagamentos do user.
    char *account_status;    // Status da conta do user.
}users;

char* filtra(char *init,char *dest);
void read_store_users(char *dir);
void analisa_linha_users(char *line);

#endif