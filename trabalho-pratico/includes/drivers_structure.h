#include <stdbool.h>
#define MAX_INFO 50
#define N_LINHAS 10000

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


unsigned int hash_drivers(char *id);
void init_hash_table_drivers();
bool insert_hash_drivers(drivers *d);
drivers *procura_hash_drivers (char *id);
