#ifndef RIDES_STRUCTURE_H
#define RIDES_STRUCTURE_H

#include <stdbool.h>
#include "parsing.h"

#define N_LINHAS 15000000
#define N_LINHAS_DRIVERS 150000
#define N_LINHAS_USERS 1500000
#define N_LINHAS_GENDER 10000


bool insert_hash_rides(char *id,char *dt,char *dr,char *user,char *c,int dist,double su,double sd,double tip);
rides *procura_rides(int id);
void free_hash_rides();

bool insert_hash_rides_drivers(char *data,char *condutor,double avaliacao_media);
rides_driver *procura_rides_driver();
void restore_hash_rides_drivers();
void free_hash_rides_drivers();

bool insert_hash_rides_users(int distance,char *date,char *user);
rides_user *procura_rides_users();
void restore_hash_rides_users();
void free_hash_rides_users();

bool insert_hash_rides_drivers_city(char* city);
rides_driver_city *procura_rides_driver_city();
void free_hash_rides_driver_city();

bool insert_hash_rides_gender(char genero,int idade);
rides_gender *procura_rides_gender();
void free_hash_rides_gender();

bool insert_hash_rides_date(char *date1,char *date2);
rides_date *procura_rides_date();
void free_hash_rides_date();

#endif