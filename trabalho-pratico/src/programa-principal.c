#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "queries.h"
#include "drivers_structure.h"
#include "rides_structure.h"
#include "users_structure.h"
#include "parsing.h"
#include <stdlib.h>
#include "interactive_mode.h"


// MODE: Batch -> In this mode, the program is executed with two arguments, the first one is the path
// to the folder where the input files are. The second corresponds to the
// path to a text file that contains a list of commands (queries) to be executed.
int main(int argc, char* argv[]){
    
    // MODE: Interactive -> In this mode, the program is executed without arguments. When the file does not contain
    // arguments we land in this mode. When this happens, an interactive menu with all the
    // the information needed to execute each query
    if(argc<=1){
        
        interactive();
        return 0;
    }

    // Creating the path for the driver's data file.
    char *file_d = malloc (250*sizeof(char));
    strcpy(file_d,argv[1]);
    strcat(file_d,"/drivers.csv");
    // Creating the path for the user's data file.
    char *file_u = malloc (250*sizeof(char));
    strcpy(file_u,argv[1]);
    strcat(file_u,"/users.csv");
    // Creating the path for the rides data file.
    char *file_r = malloc (250*sizeof(char));
    strcpy(file_r,argv[1]);
    strcat(file_r,"/rides.csv");
    // Creating the path for the query inputs file.
    char *file_txt = malloc (250*sizeof(char));
    strcpy(file_txt,argv[2]);

    // Counting the lines in the data files
    count_lines(file_d,file_u,file_r);
    
    // Allocating memory for the hash tables
    allocate_drivers();
    allocate_users();
    allocate_rides();
    allocate_rides_drivers();
    allocate_rides_users();
    allocate_rides_drivers_city();
    allocate_rides_drivers_gender();
    allocate_rides_date();

    // These functions are responsible for parsing each line of the data files. Furthermore,
    // also inserts the read values ​​(organized in a struct) into the hash table, row by row.
    read_store(file_d,'d');
    read_store(file_u,'u');
    read_store(file_r,'r');
    
    // Sorting a couple of hash tables
    sortQ2();
    sortQ3();

    // This function treats the inputs and sends them to the respective query
    read_exe_queries(file_txt,1,NULL);
    
    // Freeing the strings used to open the data files.
    free(file_d);
    free(file_u);
    free(file_r);
    free(file_txt);
    
    // Frreeing the memory allocated for the hash tables
    free_hash_drivers();
    free_hash_users();
    free_hash_rides();
    free_hash_rides_drivers();
    free_hash_rides_users();
    free_hash_rides_date();

    return 0;
}

// Coisas a fazer:

// Inicializar os apontadores.


