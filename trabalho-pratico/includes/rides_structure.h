#ifndef RIDES_STRUCT_H
#define RIDES_STRUCT_H

#include <stdbool.h>
#include "parsing_rides.h"



unsigned int hash_user_rides(char *user);
void init_hash_table_rides();
bool insert_hash_rides(rides *r);
rides *procura_hash_user_rides(char *user);

#endif
