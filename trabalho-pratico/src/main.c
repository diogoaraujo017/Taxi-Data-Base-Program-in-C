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


int main(int argc, char **argv){
    
    init_hash_table_drivers();
    init_hash_table_users();
    init_hash_rides_drivers();
    init_hash_rides_users();
    
    chdir(argv[0]);
   
    read_store_drivers();
    read_store_users();
    read_store_rides();
    
    chdir("trabalho-pratico");
    chdir(argv[1]);
   
    read_exe_queries(argv[1]);
    return 0;
}