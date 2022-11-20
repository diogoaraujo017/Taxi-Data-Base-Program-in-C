#ifndef DRIVERS_STRUCTURE_H
#define DRIVERS_STRUCTURE_H

#include <stdbool.h>
#include "parsing_drivers.h"



unsigned int hash_drivers(char *id);
void init_hash_table_drivers();
bool insert_hash_drivers(char *id,char *n,char *b,char g,char *cc,char *lp,char *ac,char *as);
drivers *procura_hash_drivers (char *id);


#endif