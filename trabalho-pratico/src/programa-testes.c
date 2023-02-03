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

extern int correct; // Determina o número de queries que estão com o output correto
extern int incorrect; // Determina o número de queries que estão com o output incorreto

// MODO: Teste -> Neste modo, o programa é executado com três argumentos, o primero é o caminho
// para a pasta onde estão os ficheiros de entrada. Já o segundo corresponde ao
// caminho para um ficheiro de texto que contém uma lista de comandos (queries) a serem executados e o terceiro
// para a pasta onde se encontram os ficheiros que contêm o output correto de cada query
int main(int argc, char* argv[]){
    
    printf("\n\n          >> PROGRAM TESTS <<");
    
    printf ("\n\n-----------------------------------------\n\n");
    
    printf(">> INSERT PATH TO DATA FILES: ");
    char *data = malloc (250*sizeof(char));
    scanf("%s",data);
    printf("\n>> INSERT PATH TO QUERY INPUTS: ");
    char *inputs = malloc (250*sizeof(char));
    scanf("%s",inputs);
    printf("\n>> INSERT PATH TO QUERY OUTPUTS: ");
    char *outputs = malloc (250*sizeof(char));
    scanf("%s",outputs);

    clock_t start_main = clock();
    // Criação do path para o ficheiro drivers.csv.
    char *file_d = malloc (100*sizeof(char));
    strcpy(file_d,data);
    strcat(file_d,"/drivers.csv");
    // Criação do path para o ficheiro users.csv.
    char *file_u = malloc (100*sizeof(char));
    strcpy(file_u,data);
    strcat(file_u,"/users.csv");
    // Criação do path para o ficheiro rides.csv.
    char *file_r = malloc (100*sizeof(char));
    strcpy(file_r,data);
    strcat(file_r,"/rides.csv");

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
    printf ("\n-----------------------------------------\n\n");
    printf("Time hash table drivers: %fs\n\n", time_hash(read_store,file_d,'d'));
    printf("Time hash table users: %fs\n\n", time_hash(read_store,file_u,'u'));
    printf("Time hash table rides: %fs\n\n", time_hash(read_store,file_r,'r'));
    printf ("-----------------------------------------\n\n");

    sortQ2();
    sortQ3();

    clock_t start = clock();
    // Esta função trata os inputs e envia os mesmos para a respetiva querie.
    read_exe_queries(inputs,0,outputs);
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
    free(data);
    free(outputs);
    free(inputs);
    
    free_hash_drivers();
    free_hash_users();
    free_hash_rides();
    free_hash_rides_drivers();
    free_hash_rides_users();
    free_hash_rides_date();

    printf ("-----------------------------------------\n\n");
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Memory usage: %ld MegaBytes\n\n", usage.ru_maxrss/1000);
    printf ("-----------------------------------------\n\n");

    clock_t end_main = clock();
    printf("Executed the entire program in %f seconds.\n\n",(double)(end_main - start_main) / CLOCKS_PER_SEC);

    return 0;
}

