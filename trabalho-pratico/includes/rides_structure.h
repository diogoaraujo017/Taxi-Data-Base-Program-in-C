#ifndef RIDES_STRUCTURE_H
#define RIDES_STRUCTURE_H

#include <stdbool.h>
#include "parsing.h"

#define MAX_INFO 100
#define N_LINHAS 1000000
#define N_LINHAS_DRIVERS 10000
#define N_LINHAS_USERS 100000
#define N_LINHAS_GENDER 2500


bool insert_hash_rides(char *id,char *dt,char *dr,char *user,char *c,int dist,double su,double sd,double tip);
rides *procura_rides(int id);

bool insert_hash_rides_drivers(char *data,char *condutor,double avaliacao_media);
rides_driver *procura_rides_driver();
void restore_hash_rides_drivers();

unsigned int hash_rides_users_key(char *user);
bool insert_hash_rides_users(int distance,char *date,char *user);
rides_user *procura_rides_users();
void restore_hash_rides_users();

bool insert_hash_rides_drivers_city(char* city);
rides_driver_city *procura_rides_driver_city();

bool insert_hash_rides_gender(char genero,int idade);
rides_gender *procura_rides_gender();

bool insert_hash_rides_date(char *date1,char *date2);
rides_date *procura_rides_date();

#endif