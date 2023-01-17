#ifndef RIDES_STRUCTURE_H
#define RIDES_STRUCTURE_H

#include <stdbool.h>
#include "parsing.h"

#define MAX_INFO 100
#define N_LINHAS 1000000
#define N_LINHAS_DRIVERS 10000
#define N_LINHAS_USERS 100000


bool insert_hash_rides(char *id,char *dt,char *dr,char *user,char *c,int dist,int su,int sd,double tip);
rides *procura_rides(int id);

bool insert_hash_rides_drivers(char *data,char *condutor,int avaliacao_media);
rides_driver *procura_rides_driver();
void restore_hash_rides_drivers();

unsigned int hash_rides_users_key(char *user);
bool insert_hash_rides_users(int distance,char *date,char *user);
rides_user *procura_rides_users();
void restore_hash_rides_users();

#endif
