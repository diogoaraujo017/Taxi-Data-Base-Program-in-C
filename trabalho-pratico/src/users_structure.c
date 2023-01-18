#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "users_structure.h"
#include "rides_structure.h"
#include "parsing.h"
#include <stdint.h>
#include <stdbool.h>


// Hash table dos users
users *hash_table_users[N_LINHAS1];


// Associa um número da hash a cada linha criando uma key que mais tarde pode ser utilizada para
// procurar esse user na hash table
unsigned int hash_users(char *username){
    unsigned int num_hash = 0;
    register int i;
    for (i = 0; username[i]!='\0'; i++)
    {
        num_hash += username[i];
        num_hash = (num_hash * username[i]) % N_LINHAS1;
    }
    return num_hash;
}

// Esta função insere uma determinada linha na hash_table se essa linha não estiver ocupada.
// Uma linha está ocupada quando não está a NULL e vice-versa, daí a importância da função
// init_hash_table_users. Se a linha for adicionada com sucesso a função dará return a true,
// não dando qualquer problema, caso contrário dará return a false significando que a 
// função não conseguiu adicionar a linha.
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
    register int i,next_position;
    for (i=0;i < N_LINHAS1;i++){
        next_position = (i + aux) % N_LINHAS1;
    
        if ((hash_table_users[next_position] == NULL)){
            hash_table_users[next_position] = u;
            return true;
        }
    }
    return false;
}

// Procura um determinado user na hash table. Esta função é bastante rápida a executar, mesmo
// existindo muitas linhas de hash, devido à existência de keys que estão associadas, uma a cada
// input colocado na hash table. Se encontrar a função dará return à linha da hash correspondente
// em forma de struct, caso contrário dará return a NULL.
users *procura_hash_users(char *username){
    register int i,next_position;
    int aux = hash_users(username);
    for (i = 0; i < N_LINHAS1; i++){
        // Calcula a possível key
        next_position = (i + aux) % N_LINHAS1;
        // Verifica se o user que está nessa posição da hash table e o que estamos à procura são iguais
        if (strcmp(hash_table_users[next_position]->username, username)==0){
            return hash_table_users[next_position];
        }
    }
    return NULL;
}