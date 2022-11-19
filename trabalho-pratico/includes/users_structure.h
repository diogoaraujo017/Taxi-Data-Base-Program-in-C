#ifndef USERS_STRUCTURE_H
#define USERS_STRUCTURE_H

#include <stdbool.h>
#include "parsing_users.h"

unsigned int hash_users(char *username);
void init_hash_table_users();
bool insert_hash_users(users *u);
users *procura_hash_users(char *username);

#endif