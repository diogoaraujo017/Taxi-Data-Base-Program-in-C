#ifndef RIDES_STRUCTURE_H
#define RIDES_STRUCTURE_H

#include <stdbool.h>
#include "parsing.h"

extern int n_linhas;
extern int n_linhas_drivers; 
extern int n_linhas_users; 
extern int n_linhas_gender;

typedef struct Rides rides;
void allocate_rides();
bool insert_hash_rides(char *id,char *dt,char *dr,char *user,char *c,int dist,double su,double sd,double tip);
void getRideFields(int *id, char **date, char **driver, char **user, char **city, int *distance, double *score_user, double *score_driver, double *tip);
void free_hash_rides();

typedef struct Rides_driver rides_driver;
void allocate_rides_drivers();
void sortQ2();
bool insert_hash_rides_drivers(char *data,char *condutor,double avaliacao_media);
void getRideDriverFields(int *id,char **date, char **driver, double *score_driver, char **nome, int *numero_viagens, double *score_total);
int compareDrivers(const void *elem1, const void *elem2);
void free_hash_rides_drivers();

typedef struct Rides_user rides_user;
void allocate_rides_users();
void sortQ3();
bool insert_hash_rides_users(int distance,char *date,char *user);
void getRideUserFields(int *ind, int *distancia, char **date, char **username, char **nome);
int compareUsers(const void *elem1, const void *elem2);
void free_hash_rides_users();

typedef struct Rides_driver_city rides_driver_city;
void allocate_rides_drivers_city();
void sortQ7();
bool insert_hash_rides_drivers_city(char* city);
void getRideDriverCityFields(int *ind, double *avaliacao_media, char **id, int *numero_viagens, char **nome, double *avaliacao_total);
int compareCity(const void *elem1, const void *elem2);
void free_hash_rides_driver_city();

typedef struct Rides_gender rides_gender;
void allocate_rides_drivers_gender();
void init_hash_rides_gender(int aux);
bool insert_hash_rides_gender(char genero,int idade);
rides_gender *procura_rides_gender();
void getRideGenderFields(char **id_condutor, char **nome_condutor, char **username_utilizador, char **nome_utilizador, char **data_driver, char **data_user, char **id_viagem, int *isValid);
void free_hash_rides_gender();

typedef struct Rides_date rides_date;
void allocate_rides_date();
bool insert_hash_rides_date(char *date1,char *date2);
rides_date *procura_rides_date();
void getRideDateFields (int *distance, char **date, char **id, char **city, double *tip, char **id_viagem, int *isValid);
void free_hash_rides_date();

#endif