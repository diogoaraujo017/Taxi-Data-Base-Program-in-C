#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users_structure.h"

hash_table *create_hash(void){
    // allocate table
    ht_t *hashtable = malloc(sizeof(ht_t) * 1);

    // allocate table entries
    hashtable->entries = malloc(sizeof(entry_t*) * TABLE_SIZE);

    // set each to null (needed for proper operation)
    int i = 0;
    for (; i < TABLE_SIZE; ++i) {
        hashtable->entries[i] = NULL;
    }

    return hashtable;
}

hash_table new_user();
hash_table insert_users(hash_table t, char *username, char *name, char *birth_day, char *account_creation, char *pay_method, char *account_status);
void write_user(Users u);
