#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rides_structure.h"
#include "parsing_rides.h"
#include <stdint.h>
#include <stdbool.h>



//Inicia a hash_table
rides *hash_table_rides[N_LINHAS];


//Associa um número da hash a cada linha
unsigned int hash_user_rides(char *user){
    int comp = strnlen(user,MAX_INFO);
    unsigned int num_hash = 0;
    for (int i = 0; i < comp; i++)
    {
        num_hash += user[i];
        num_hash = (num_hash * user[i]) % N_LINHAS;
    }
    return num_hash;
}

//Inicia a hash_table colocando todas as linhas a NULL
void init_hash_table_rides(){
    for (int i = 0; i < N_LINHAS; i++)
    {
        hash_table_rides[i] = NULL;
    }   
}

//Insere linhas na hash_table se essa linhas não estiver ocupada (Se return for true)
bool insert_hash_rides(rides *r){
    if (r==NULL) return false;
    int aux = hash_user_rides(r->user);
    for (int i=0;i < N_LINHAS;i++){
        int next_position = (i + aux) % N_LINHAS;
    
        if (hash_table_rides[next_position] == NULL){
            hash_table_rides[next_position] = r;
            return true;
        }
    }
    return false;
}

//Procura o user na hash table
rides *procura_hash_user_rides(char *user){
    int aux = hash_user_rides(user);
    for (int i = 0; i < N_LINHAS; i++){
        int next_position = (i + aux) % N_LINHAS;
        if (hash_table_rides[next_position] == NULL) return false;
        if (hash_table_rides[next_position] != NULL && strncmp(hash_table_rides[aux]->user, user, MAX_INFO)==0){
            return hash_table_rides[aux];
        }
    }
    return NULL;
}



    // init_hash_table();

    // rides test = {.user="TEST"};
    // insert_hash_table(&test);