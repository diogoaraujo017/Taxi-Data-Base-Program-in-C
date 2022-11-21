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
#include <unistd.h>


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
    

   

// Estas funções são responsáveis pelo parsing de cada linha dos ficheiros .csv. Para além disso,
// também inserem os valores lidos (organizados numa struct) para a hash table, linha a linha. 
    read_store_drivers(argv[1]);
    read_store_users(argv[1]);
    read_store_rides(argv[1]);


// Com este comando, regressamos à pasta principal (trabalho-pratico), visto que já demos o parse dos 
// ficheiros .csv

   

// Com este comando, temos acesso ao caminho que leva ao ficheiro .txt para ler os inputs.
    read_exe_queries(argv[2]);


    return 0;
}