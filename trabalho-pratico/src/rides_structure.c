#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rides_structure.h"
#include <stdint.h>
#include <stdbool.h>


typedef struct{
    char id[MAX_INFO];
    char date[MAX_INFO];
    char driver[MAX_INFO];
    char user[MAX_INFO];
    char city[MAX_INFO];
    int distance;
    int score_user;
    int score_driver;
    double tip;
    char comment[MAX_INFO];  
} rides;

//Inicia a hash_table
rides *hash_table[N_LINHAS];


//Associa um número da hash a cada linha
unsigned int hash(char *user){
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
void init_hash_table(){
    for (int i = 0; i < N_LINHAS; i++)
    {
        hash_table[i] = NULL;
    }   
}

//Insere linhas na hash_table se essa linhas não estiver ocupada (Se return for true)
bool insert_hash_table(rides *r){
    if (r==NULL) return false;
    int aux = hash(r->user);
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
rides *procura_hash_table (char *user){
    int aux = hash(user);
    for (int i = 0; i < N_LINHAS; i++){
        int next_position = (i + aux) % N_LINHAS;
        if (hash_table[next_position] == NULL) return false;
        if (hash_table[next_position] != NULL && strncmp(hash_table[aux]->user, user, MAX_INFO)==0){
            return hash_table[aux];
        }
    }
    return NULL;
}



    // init_hash_table();

    // rides test = {.user="TEST"};
    // insert_hash_table(&test);