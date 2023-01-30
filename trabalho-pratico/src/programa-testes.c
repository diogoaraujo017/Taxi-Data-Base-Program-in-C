#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "queries.h"
#include "drivers_structure.h"
#include "rides_structure.h"
#include "users_structure.h"
#include "func_auxiliares.h"
#include "parsing.h"
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

extern int correct;
extern int incorrect;

// MODO: Batch -> Neste modo, o programa é executado com dois argumentos, o primero é o caminho
// para a pasta onde estão os ficheiros de entrada. Já o segundo corresponde ao
// caminho para um ficheiro de texto que contém uma lista de comandos (queries) a serem executados.
int main(int argc, char* argv[]){
    
    // Criação do path para o ficheiro drivers.csv.
    char *file_d = malloc (100*sizeof(char));
    strcpy(file_d,argv[1]);
    strcat(file_d,"/drivers.csv");
    // Criação do path para o ficheiro users.csv.
    char *file_u = malloc (100*sizeof(char));
    strcpy(file_u,argv[1]);
    strcat(file_u,"/users.csv");
    // Criação do path para o ficheiro rides.csv.
    char *file_r = malloc (100*sizeof(char));
    strcpy(file_r,argv[1]);
    strcat(file_r,"/rides.csv");
    // Criação do path para o ficheiro dos inputs.
    char *file_txt = malloc (100*sizeof(char));
    strcpy(file_txt,argv[2]);
    // Criação do path para o ficheiro dos inputs.
    char *outputs = malloc (100*sizeof(char));
    strcpy(outputs,argv[3]);

    count_lines(file_d,file_u,file_r);
    
    allocate_drivers();
    allocate_users();
    allocate_rides();
    allocate_rides_drivers();
    allocate_rides_users();
    allocate_rides_drivers_city();
    allocate_rides_drivers_gender();
    allocate_rides_date();

    // Estas funções são responsáveis pelo parsing de cada linha dos ficheiros .csv. Para além disso,
    // também inserem os valores lidos (organizados numa struct) para a hash table, linha a linha. 
    //double a = time_it_takes(read_store,file_d,'d');
    printf("\nTime hash table drivers: %fs\n", time_hash(read_store,file_d,'d'));
    printf("Time hash table users: %fs\n", time_hash(read_store,file_u,'u'));
    printf("Time hash table rides: %fs\n\n", time_hash(read_store,file_r,'r'));
    printf ("-----------------------------------------\n\n");

    sortQ2();
    sortQ3();



    clock_t start = clock();
    // Esta função trata os inputs e envia os mesmos para a respetiva querie.
    read_exe_queries(file_txt,0,outputs);
    clock_t end = clock();
    printf("\nExecuted all queries in %f seconds.\n\n",(double)(end - start) / CLOCKS_PER_SEC);

    printf("\033[0;32m");
    printf("Correct Queries: %d",correct);

    printf("\033[0;31m");
    printf("\nIncorrect Queries: %d\n\n",incorrect);
    printf("\033[0m");

    free(file_d);
    free(file_u);
    free(file_r);
    free(file_txt);
    
    free_hash_drivers();
    free_hash_users();
    free_hash_rides();
    free_hash_rides_drivers();
    free_hash_rides_users();
    free_hash_rides_date();

    printf ("-----------------------------------------\n\n");
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Memory usage: %ld MegaBytes\n", usage.ru_maxrss/1000);



    return 0;
}

// Coisas a fazer:

// Inicializar todos os pointers, dar init na main
// Nao utilizar o pointer original. fazer copias
// Modo iterativo
// Make file TIME
// Inicializar os apontadores
// Tipos opacos
