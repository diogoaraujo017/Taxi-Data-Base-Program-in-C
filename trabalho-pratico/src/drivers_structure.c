#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drivers_structure.h"
#include <stdint.h>
#include <stdbool.h>


typedef struct{
    char id[MAX_INFO];
    char name[MAX_INFO];
    char birth_day[MAX_INFO];
    char gender;
    char car_class[MAX_INFO];
    char license_plate[MAX_INFO];
    char acount_creation[MAX_INFO];  
} drivers;

//Inicia a hash_table
drivers *hash_table[N_LINHAS];


//Associa um número da hash a cada linha
unsigned int hash(char *id){
    int comp = strnlen(id,MAX_INFO);
    unsigned int num_hash = 0;
    for (int i = 0; i < comp; i++)
    {
        num_hash += id[i];
        num_hash = (num_hash * id[i]) % N_LINHAS;
    }
    return num_hash;
}

//Inicia a hash_table colocando todas as linhas a NULL
void init_hash_table(){
    for (int i = 0; i < N_LINHAS; i++)
    {
        hash_table[i] = NULL;
    }   
}

//Insere linhas na hash_table se essa linhas não estiver ocupada (Se return for true)
bool insert_hash_table(drivers *r){
    if (r==NULL) return false;
    int aux = hash(r->id);
    for (int i=0;i < N_LINHAS;i++){
        int next_position = (i + aux) % N_LINHAS;
    
        if (hash_table[next_position] == NULL){
            hash_table[next_position] = r;
            return true;
        }
    }
    return false;
}

//Procura o username na hash table
drivers *procura_hash_table (char *id){
    int aux = hash(id);
    for (int i = 0; i < N_LINHAS; i++){
        int next_position = (i + aux) % N_LINHAS;
        if (hash_table[next_position] == NULL) return false;
        if (hash_table[next_position] != NULL && strncmp(hash_table[aux]->id, id, MAX_INFO)==0){
            return hash_table[aux];
        }
    }
    return NULL;
}



    // init_hash_table();

    // rides test = {.user="TEST"};
    // insert_hash_table(&test);