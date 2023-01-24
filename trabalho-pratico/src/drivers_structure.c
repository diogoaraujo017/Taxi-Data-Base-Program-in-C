#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drivers_structure.h"
#include "rides_structure.h"
#include "parsing.h"
#include <stdint.h>
#include <stdbool.h>


// Hash table dos drivers
drivers *hash_table_drivers[N_LINHAS_DRIVERS];


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

    hash_table_drivers[atoi(id)-1] = d;
    return true;
    }



// Procura um determinado driver na hash table. Esta função é bastante rápida a executar, mesmo
// existindo muitas linhas de hash, devido à existência de keys que estão associadas, uma a cada
// input colocado na hash table. Se encontrar a função dará return à linha da hash correspondente
// em forma de struct, caso contrário dará return a NULL.
drivers *procura_hash_drivers(char *id){
    return hash_table_drivers[atoi(id)-1];
}