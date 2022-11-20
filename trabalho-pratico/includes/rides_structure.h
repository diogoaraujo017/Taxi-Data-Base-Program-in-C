#ifndef RIDES_STRUCTURE_H
#define RIDES_STRUCTURE_H

#include <stdbool.h>
#include "parsing_rides.h"

int calculaData (char *line,char *line2);
int calculaIdade (char line[]);
const char* converte(char str[]);
unsigned int hash_drivers_rides(char *id);
unsigned int hash_user_rides(char *user);
void init_hash_rides_drivers();
void init_hash_rides_users();
bool insert_rides_drivers(char *id,char *dt,char *dr,char *u,char *ac,int dist,int su,int sd,double tip,char *cm);
bool insert_rides_users(char *id,char *dt,char *dr,char *u,char *ac,int dist,int su,int sd,double tip,char *cm);
drivers_q1 *procura_rides_drivers(char *id);
users_q1 *procura_rides_users(char *username);

#endif
