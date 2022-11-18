#ifndef RIDES_STRUCTURE_H
#define RIDES_STRUCTURE_H

#include <stdbool.h>
#include "parsing_rides.h"


int calculaIdade (char line[]);
const char* converte(char str[]);
unsigned int hash_drivers_rides(char *id);
unsigned int hash_user_rides(char *user);
void init_hash_rides_drivers();
void init_hash_rides_users();
bool insert_rides_drivers(rides *r);
bool insert_rides_users(rides *r);
drivers_q1 calcula_hash_rides_drivers(char *id);
users_q1 calcula_hash_rides_users(char *user);

#endif
