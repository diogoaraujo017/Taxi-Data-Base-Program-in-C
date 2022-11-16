#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "queries.h"
#include "drivers_structure.h"
#include "rides_structure.h"
#include "users_structure.h"
#include "parsing_rides.h"
#include "parsing_rides.h"
#include "parsing_users.h"



int main(int argc, char const *argv[]){
    
    init_hash_table_drivers();
    init_hash_table_users();
    init_hash_table_rides();

    DIR* dir = opendir(argv[1]);
    if (dir == NULL) {
        return;
    }
    read_store_drivers();
    read_store_users();
    read_store_rides();
    closedir(dir);
     
    DIR* dir2 = opendir(argv[2]);
    if (dir2 == NULL) {
        return;
    }
    read_exe_queries(argv[2]);
    closedir(dir2);
     
    return 0;
}

