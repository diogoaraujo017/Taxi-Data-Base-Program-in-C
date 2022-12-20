#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drivers_structure.h"
#include "rides_structure.h"
#include "parsing.h"
#include <stdint.h>
#include <stdbool.h>


// Hash table dos drivers
drivers *hash_table_drivers[N_LINHAS2];


// Associa um número da hash a cada linha criando uma key que mais tarde pode ser utilizada para
// procurar esse driver na hash table
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


// Esta função inicia a hash table com os tamanho respetivos, colocando todas as
// suas linhas a NULL. Fazemos isto, para quando existirem colisões, estas não serem um problema.
void init_hash_table_drivers(){
    for (int i = 0; i < N_LINHAS2; i++){
        hash_table_drivers[i] = NULL;
    }   
}


// Esta função insere uma determinada linha na hash_table se essa linha não estiver ocupada.
// Uma linha está ocupada quando não está a NULL e vice-versa, daí a importância da função
// init_hash_table_drivers. Se a linha for adicionada com sucesso a função dará return a true,
// não dando qualquer problema, caso contrário dará return a false significando que a 
// função não conseguiu adicionar a linha.
bool insert_hash_drivers(char *id,char *n,char *b,char g,char *cc,char *lp,char *c,char *ac,char *as){
    drivers *d = malloc(sizeof(drivers));
    d->id = id;
    d->name = n;
    d->gender = g;
    d->birth_day = b;
    d->account_creation = ac;
    d->car_class = cc;
    d->city=c;
    d->license_plate = lp;
    d->account_status = as;
    int aux = hash_drivers(id);
    for (int i=0;i < N_LINHAS2;i++){
        int next_position = (i + aux) % N_LINHAS2;
        if ((hash_table_drivers[next_position] == NULL)){
            hash_table_drivers[next_position] = d;
            return true;
        }
    }
    return false;
}

// Procura um determinado driver na hash table. Esta função é bastante rápida a executar, mesmo
// existindo muitas linhas de hash, devido à existência de keys que estão associadas, uma a cada
// input colocado na hash table. Se encontrar a função dará return à linha da hash correspondente
// em forma de struct, caso contrário dará return a NULL.
drivers *procura_hash_drivers(char *id){
    int index = hash_drivers(id);
    for (int i = 0; i < N_LINHAS2; i++){
        // Calcula a possível key
        int next_position = (i + index) % N_LINHAS2;
        // Verifica se o driver que está nessa posição da hash table e o que estamos à procura são iguais
        if (strncmp(hash_table_drivers[next_position]->id, id, MAX_INFO)==0){
            return hash_table_drivers[next_position];
        }
    }
    return NULL;
}
