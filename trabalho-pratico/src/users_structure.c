#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users_structure.h"

typedef struct{
    char username[MAX_INFO];
    char name[MAX_INFO];
    char birth_day[MAX_INFO];
    char account_creation[MAX_INFO]; 
    char pay_method[MAX_INFO];
    char account_status[MAX_INFO];
}users;

//Inicia a hash_table
users *hash_table_users[N_LINHAS];


//Associa um número da hash a cada linha
unsigned int hash_users(char *username){
    int comp = strnlen(username,MAX_INFO);
    unsigned int num_hash = 0;
    for (int i = 0; i < comp; i++)
    {
        num_hash += username[i];
        num_hash = (num_hash * username[i]) % N_LINHAS;
    }
    return num_hash;
}

//Inicia a hash_table colocando todas as linhas a NULL
void init_hash_table(){
    for (int i = 0; i < N_LINHAS; i++)
    {
        hash_table_users[i] = NULL;
    }   
}

//Insere linhas na hash_table se essa linhas não estiver ocupada (Se return for true)
bool insert_hash_users(users *u){
    if (u==NULL) return false;
    int aux = hash_users(u->username);
    for (int i=0;i < N_LINHAS;i++){
        int next_position = (i + aux) % N_LINHAS;
    
        if (hash_table_users[next_position] == NULL){
            hash_table_users[next_position] = u;
            return true;
        }
    }
    return false;
}

//Procura o username na hash table
users *procura_hash_users(char *username){
    int aux = hash_users(username);
    for (int i = 0; i < N_LINHAS; i++){
        int next_position = (i + aux) % N_LINHAS;
        if (hash_table_users[next_position] == NULL) return false;
        if (hash_table_users[next_position] != NULL && strncmp(hash_table_users[aux]->username, username, MAX_INFO)==0){
            return hash_table_users[aux];
        }
    }
    return NULL;
}

void write_user_Q1(users u);
users create_user(char *username, char *name, char *birth_day, char *account_creation, char *pay_method, char *account_status);