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

extern int correct;   // Determine the number of queries that have the correct output
extern int incorrect; // Determine the number of queries that have the incorrect output

// MODE: Test -> In this mode the program ask the user in the terminal for the path to the data 
// files, the path to the inputs and the path to the correct outputs. Then the program prints in
// the terminal statisctics about the programs runtime and memory use and check if the queries
// outputs are correct or incorrect also displaying the time it took to execute them.
int main(int argc, char* argv[]){
    
    printf("\n\n          >> PROGRAM TESTS <<");
    printf ("\n\n-----------------------------------------\n\n");
    
    //  Asking the user, in the terminal, to indicate where the
    // needed files are locate.
    printf(">> INSERT PATH TO DATA FILES: ");
    char *data = malloc (250*sizeof(char));
    scanf("%s",data);
    printf("\n>> INSERT PATH TO QUERY INPUTS: ");
    char *inputs = malloc (250*sizeof(char));
    scanf("%s",inputs);
    printf("\n>> INSERT PATH TO QUERY OUTPUTS: ");
    char *outputs = malloc (250*sizeof(char));
    scanf("%s",outputs);

    // Starting the program timer.
    clock_t start_main = clock();

    // Creating the path for the driver's data file.
    char *file_d = malloc (100*sizeof(char));
    strcpy(file_d,data);
    strcat(file_d,"/drivers.csv");
    // Creating the path for the user's data file.
    char *file_u = malloc (100*sizeof(char));
    strcpy(file_u,data);
    strcat(file_u,"/users.csv");
    // Creating the path for the rides data file.
    char *file_r = malloc (100*sizeof(char));
    strcpy(file_r,data);
    strcat(file_r,"/rides.csv");

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

    printf ("\n-----------------------------------------\n\n");
    
    // Creating all of the hash tables an then printing the time it took for
    // each hash table to be created.
    printf("Time hash table drivers: %fs\n\n", time_hash(read_store,file_d,'d'));
    printf("Time hash table users: %fs\n\n", time_hash(read_store,file_u,'u'));
    printf("Time hash table rides: %fs\n\n", time_hash(read_store,file_r,'r'));
    
    printf ("-----------------------------------------\n\n");
    
    // Sorting a couple of hash tables
    sortQ2();
    sortQ3();

    // Starting the queries timer.
    clock_t start = clock();

    //  Executing all the queries in the input's file and verifting the outputs.
    read_exe_queries(inputs,0,outputs);
    
    // Stoping the queries timer.
    clock_t end = clock();

    // Printing in the terminal the queries execution time.
    printf("\nExecuted all queries in %f seconds.\n\n",(double)(end - start) / CLOCKS_PER_SEC);
    
    // Printing in the terminal, in green, the number of correct queries
    printf("\033[0;32m");
    printf("Correct Queries: %d",correct);

    // Printing in the terminal, in red, the number of incorrect queries
    printf("\033[0;31m");
    printf("\nIncorrect Queries: %d\n\n",incorrect);
    printf("\033[0m");
    
    // Freeing the strings used to open the needed files.
    free(file_d);
    free(file_u);
    free(file_r);
    free(data);
    free(outputs);
    free(inputs);
    
    // Frreeing the memory allocated for the hash tables
    free_hash_drivers();
    free_hash_users();
    free_hash_rides();
    free_hash_rides_drivers();
    free_hash_rides_users();
    free_hash_rides_date();

    printf ("-----------------------------------------\n\n");
    
    // Printing in the terminal the ammount of memory that the program used.
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Memory usage: %ld MegaBytes\n\n", usage.ru_maxrss/1000);
    
    printf ("-----------------------------------------\n\n");

    // Stoping the program timer and printing that number in the terminal.
    clock_t end_main = clock();
    printf("Executed the entire program in %f seconds.\n\n",(double)(end_main - start_main) / CLOCKS_PER_SEC);

    return 0;
}

