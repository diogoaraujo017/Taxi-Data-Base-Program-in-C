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


int main(int argc, char const *argv[]){
    
    init_hash_table_drivers();
    init_hash_table_users();
    init_hash_rides_drivers();
    init_hash_rides_users();

    // DIR* dir = opendir(argv[0]);
    // if (dir == NULL) {
    //     return 1;
    // }

    read_store_drivers();
    read_store_users();
    read_store_rides();

    //closedir(dir);
     
    // DIR* dir2 = opendir(argv[1]);
    // if (dir2 == NULL) {
    //     return 1;
    // }

    read_exe_queries("tests.txt");
    
    //closedir(dir2);
     
    return 0;
}
