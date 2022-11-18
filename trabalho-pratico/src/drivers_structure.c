#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drivers_structure.h"
#include "parsing_drivers.h"
#include <stdint.h>
#include <stdbool.h>



//Inicia a hash_table
drivers *hash_table_drivers[N_LINHAS2];


//Associa um número da hash a cada linha
unsigned int hash_drivers(char *id){
    int comp = strnlen(id,MAX_INFO);
    unsigned int num_hash = 0;
    for (int i = 0; i < comp; i++)
    {
        num_hash += id[i];
        num_hash = (num_hash * id[i]) % N_LINHAS2;
    }
    return num_hash;
}

//Inicia a hash_table colocando todas as linhas a NULL
void init_hash_table_drivers(){
    for (int i = 0; i < N_LINHAS2; i++)
    {
        hash_table_drivers[i] = NULL;
    }   
}

//Insere linhas na hash_table se essa linhas não estiver ocupada (Se return for true)
bool insert_hash_drivers(drivers *d){
    if (d==NULL) return false;
    int aux = hash_drivers(d->id);
    for (int i=0;i < N_LINHAS2;i++){
        int next_position = (i + aux) % N_LINHAS2;
        if (hash_table_drivers[next_position] == NULL){
            hash_table_drivers[next_position] = d;
            return true;
        }
    }
    return false;
}

//Procura o id na hash table
drivers *procura_hash_drivers(char *id){
    int index = hash_drivers(id);
    for (int i = 0; i < N_LINHAS2; i++){
        int next_position = (i + index) % N_LINHAS2;
        if (hash_table_drivers[next_position] == NULL) return false;
        if (hash_table_drivers[next_position] != NULL && strncmp(hash_table_drivers[next_position]->id, id, MAX_INFO)==0){
            return hash_table_drivers[next_position];
        }
    }
    return NULL;
}
