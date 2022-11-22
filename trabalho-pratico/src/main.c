#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "queries.h"
#include "drivers_structure.h"
#include "rides_structure.h"
#include "users_structure.h"
#include "parsing_drivers.h"
#include "parsing_rides.h"
#include "parsing_users.h"
#include <stdlib.h>


// MODO: Batch -> Neste modo, o programa é executado com dois argumentos, o primero é o caminho
// para a pasta onde estão os ficheiros de entrada. Já o segundo corresponde ao
// caminho para um ficheiro de texto que contém uma lista de comandos (queries) a serem executados.
int main(int argc, char* argv[]){
    

// Estas funções iniciam as hash tables com os tamanho respetivos, colocando todas as
// suas linhas a NULL. Fazemos isto, para quando existirem colisões, estas não serem um problema.
    init_hash_table_drivers();
    init_hash_table_users();
    init_hash_rides_drivers();
    init_hash_rides_users();
    init_hash_rides_city();
    

    char *aux = malloc (100*sizeof(char));
    strcpy(aux,argv[1]);
    strcat(aux,"/drivers.csv");

    char *aux2 = malloc (100*sizeof(char));
    strcpy(aux2,argv[1]);
    strcat(aux2,"/users.csv");

    char *aux3 = malloc (100*sizeof(char));
    strcpy(aux3,argv[1]);
    strcat(aux3,"/rides.csv");

    char *aux4 = malloc (100*sizeof(char));
    strcpy(aux4,argv[2]);


// Estas funções são responsáveis pelo parsing de cada linha dos ficheiros .csv. Para além disso,
// também inserem os valores lidos (organizados numa struct) para a hash table, linha a linha. 
    read_store_drivers(aux);
    read_store_users(aux2);
    read_store_rides(aux3);


// Com este comando, temos acesso ao caminho que leva ao ficheiro .txt para ler os inputs.
    read_exe_queries(aux4);


    return 0;
}