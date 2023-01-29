#ifndef RIDES_STRUCTURE_H
#define RIDES_STRUCTURE_H

#include <stdbool.h>
#include "parsing.h"

extern int n_linhas;
extern int n_linhas_drivers; 
extern int n_linhas_users; 
extern int n_linhas_gender;


bool insert_hash_rides(char *id,char *dt,char *dr,char *user,char *c,int dist,double su,double sd,double tip);
rides *procura_rides(int id);
void free_hash_rides();

void sortQ2();
bool insert_hash_rides_drivers(char *data,char *condutor,double avaliacao_media);
rides_driver *procura_rides_driver(int ind);
int compareDrivers(const void *elem1, const void *elem2);
void free_hash_rides_drivers();


void sortQ3();
bool insert_hash_rides_users(int distance,char *date,char *user);
rides_user *procura_rides_users(int ind);
int compareUsers(const void *elem1, const void *elem2);
void free_hash_rides_users();

void sortQ7();
bool insert_hash_rides_drivers_city(char* city);
rides_driver_city *procura_rides_driver_city(int ind);
int compareCity(const void *elem1, const void *elem2);
void free_hash_rides_driver_city();

void init_hash_rides_gender(int aux);
bool insert_hash_rides_gender(char genero,int idade);
rides_gender *procura_rides_gender();
void free_hash_rides_gender();

bool insert_hash_rides_date(char *date1,char *date2);
rides_date *procura_rides_date();
void free_hash_rides_date();

void allocate_rides();

#endif