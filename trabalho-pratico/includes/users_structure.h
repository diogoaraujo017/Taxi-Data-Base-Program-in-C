#ifndef USERS_STRUCTURE_H
#define USERS_STRUCTURE_H

#include <stdbool.h>
#include "parsing.h"

#define MAX_INFO 100
#define N_LINHAS1 100000

unsigned int hash_users(char *username);
void init_hash_table_users();
bool insert_hash_users(char *us,char *n,char g,char *b,char *ac,char *p,char *s);
users *procura_hash_users(char *username);

#endif