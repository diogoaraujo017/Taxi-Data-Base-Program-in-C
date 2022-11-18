#ifndef PARSING_DRIVERS_H
#define PARSING_DRIVERS_H

#define MAX_INFO 50
#define N_LINHAS2 10000


typedef struct{
    char id[MAX_INFO];
    char name[MAX_INFO];
    char birth_day[MAX_INFO];
    char gender;
    char car_class[MAX_INFO];
    char license_plate[MAX_INFO];
    char account_creation[MAX_INFO];  
    char account_status[MAX_INFO];
} drivers;


void read_store_drivers();
void analisa_linha_drivers(char line[150]);

#endif