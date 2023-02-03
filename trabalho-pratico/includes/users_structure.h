#ifndef USERS_STRUCTURE_H
#define USERS_STRUCTURE_H

#include <stdbool.h>
#include "parsing.h"
#include "rides_structure.h"

typedef struct Users users;

unsigned int hash_users(char *username);

bool insert_hash_users(char *us,char *n,char *g,char *b,char *ac,char *s);

users *procura_hash_users(char *username);

void getUserFields(char **username, char **name, char **gender, char **birth_day, char **account_creation, char **account_status);

void free_hash_users();
void allocate_users();

#endif