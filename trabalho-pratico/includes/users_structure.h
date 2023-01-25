#ifndef USERS_STRUCTURE_H
#define USERS_STRUCTURE_H

#include <stdbool.h>
#include "parsing.h"
#include "rides_structure.h"

unsigned int hash_users(char *username);
bool insert_hash_users(char *us,char *n,char *g,char *b,char *ac,char *s);
users *procura_hash_users(char *username);
void free_hash_users();

#endif