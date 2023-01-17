#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "queries.h"
#include "drivers_structure.h"
#include "rides_structure.h"
#include "users_structure.h"
#include "parsing.h"
#include <stdlib.h>


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

    // Estas funções são responsáveis pelo parsing de cada linha dos ficheiros .csv. Para além disso,
    // também inserem os valores lidos (organizados numa struct) para a hash table, linha a linha. 
    read_store(file_d,'d');
    read_store(file_u,'u');
    read_store(file_r,'r');

    // Esta função trata os inputs e envia os mesmos para a respetiva querie.
    read_exe_queries(file_txt);




    return 0;
}