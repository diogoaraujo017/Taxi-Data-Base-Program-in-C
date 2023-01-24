#ifndef DRIVERS_STRUCTURE_H
#define DRIVERS_STRUCTURE_H
#include <stdbool.h>
#include "parsing.h"
#include "rides_structure.h"

bool insert_hash_drivers(char *id,char *n,char *b,char g,char *cc,char *lp,char *c,char *ac,char *as);
drivers *procura_hash_drivers (char *id);

#endif