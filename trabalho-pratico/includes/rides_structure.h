#ifndef RIDES_STRUCTURE_H
#define RIDES_STRUCTURE_H

#include <stdbool.h>
#include "parsing.h"

extern int n_lines;
extern int n_lines_drivers; 
extern int n_lines_users; 
extern int n_lines_gender;


typedef struct Rides rides;
void allocate_rides();
bool insert_hash_rides(char *id,char *date,char *driver_id,char *username,char *city,int distance,
                       double score_user,double score_driver,double tip);
void getRideFields(int *id, char **date, char **driver, char **user, char **city,
                   int *distance, double *score_user, double *score_driver, double *tip);
void free_hash_rides();


typedef struct Rides_driver rides_driver;
void allocate_rides_drivers();
void sortQ2();
bool insert_hash_rides_drivers(char *data,char *driver,double score_driver);
void getRideDriverFields(int *id,char **date, char **driver, double *score_driver, 
                         char **nome, int *numero_viagens, double *score_total);
int compareDrivers(const void *elem1, const void *elem2);
void free_hash_rides_drivers();


typedef struct Rides_user rides_user;
void allocate_rides_users();
void sortQ3();
bool insert_hash_rides_users(int distance,char *date,char *user);
void getRideUserFields(int *ind, int *distance, char **date, char **username, char **name);
int compareUsers(const void *elem1, const void *elem2);
void free_hash_rides_users();


typedef struct Rides_driver_city rides_driver_city;
void allocate_rides_drivers_city();
void sortQ7();
bool insert_hash_rides_drivers_city(char* city);
void getRideDriverCityFields(int *ind, double *average_score, char **id, int *trip_counter, 
                             char **name, double *total_score);
int compareCity(const void *elem1, const void *elem2);
void free_hash_rides_driver_city();


typedef struct Rides_gender rides_gender;
void allocate_rides_drivers_gender();
void init_hash_rides_gender(int aux);
bool insert_hash_rides_gender(char genero,int idade);
rides_gender *search_rides_gender();
void getRideGenderFields(char **driver_id, char **name_driver, char **username, 
                         char **nome_user, char **date_driver, char **date_user, 
                         char **id_trip, int *isValid);
void free_hash_rides_gender();


typedef struct Rides_date rides_date;
void allocate_rides_date();
bool insert_hash_rides_date(char *date1,char *date2);
rides_date *search_rides_date();
void getRideDateFields (int *distance, char **date, char **id, char **city, double *tip, 
                        char **id_trip, int *isValid);
void free_hash_rides_date();

#endif