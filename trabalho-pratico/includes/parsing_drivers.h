#ifndef PARSING_DRIVERS_H
#define PARSING_DRIVERS_H

#define MAX_INFO 100
#define N_LINHAS2 10000


typedef struct{
    char *id;
    char *name;
    char *birth_day;
    char gender;
    char *car_class;
    char *license_plate;
    char *account_creation;  
    char *account_status;
} drivers;


void read_store_drivers();
void analisa_linha_drivers(char line[150]);

#endif