#include <stdbool.h>
#define MAX_INFO 50
#define N_LINHAS 1000000


typedef struct{
    char id[MAX_INFO];
    char date[MAX_INFO];
    char driver[MAX_INFO];
    char user[MAX_INFO];
    char city[MAX_INFO];
    int distance;
    int score_user;
    int score_driver;
    double tip;
    char comment[MAX_INFO];  
} rides;

unsigned int hash_user_rides(char *user);
void init_hash_table_rides();
bool insert_hash_rides(rides *r);
rides *procura_hash_user_rides(char *user);
