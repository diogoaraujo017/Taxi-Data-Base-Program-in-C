#ifndef DRIVERS_STRUCTURE_H
#define DRIVERS_STRUCTURE_H
#include <stdbool.h>
#include "parsing.h"
#include "rides_structure.h"

typedef struct Drivers drivers;

bool insert_hash_drivers(char *id,char *n,char *b,char *g,char *cc,char *c,char *ac,char *as);
void getDriverFields(char **id, char **name, char **birth_day,
                     char **gender, char **car_class, char **city, char **account_creation,
                     char **account_status);

void free_hash_drivers();
void allocate_drivers();

#endif