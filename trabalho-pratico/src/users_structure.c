#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "users_structure.h"
#include "rides_structure.h"
#include "parsing_users.h"
#include <stdint.h>
#include <stdbool.h>



//Inicia a hash_table
users *hash_table_users[N_LINHAS1];


//Associa um número da hash a cada linha
unsigned int hash_users(char *username){
    int comp = strnlen(username,MAX_INFO);
    unsigned int num_hash = 0;
    for (int i = 0; i < comp; i++)
    {
        num_hash += username[i];
        num_hash = (num_hash * username[i]) % N_LINHAS1;
    }
    return num_hash;
}

void init_hash_table_users() {
    for (int i = 0; i < N_LINHAS1; i++) {
        hash_table_users[i] = NULL;
    }
}


//Insere linhas na hash_table se essa linhas não estiver ocupada (Se return for true)
bool insert_hash_users(char *us,char *n,char g,char *b,char *ac,char *p,char *as){
    users *u = malloc(sizeof(users));
    u->username = us;
    u->name = n;
    u->gender = g;
    u->birth_day = b;
    u->account_creation = ac;
    u->pay_method = p;
    u->account_status = as;
    int aux = hash_users(us);
    for (int i=0;i < N_LINHAS1;i++){
        int next_position = (i + aux) % N_LINHAS1;
    
        if ((hash_table_users[next_position] == NULL)){
            hash_table_users[next_position] = u;
            return true;
        }
    }
    return false;
}

//Procura o username na hash table
users *procura_hash_users(char *username){
    int aux = hash_users(username);
    for (int i = 0; i < N_LINHAS1; i++){
        int next_position = (i + aux) % N_LINHAS1;
        if (strncmp(hash_table_users[next_position]->username, username, MAX_INFO)==0){
            return hash_table_users[next_position];
        }
    }
    return NULL;
}

