#ifndef PARSING_RIDES_H
#define PARSING_RIDES_H

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

void read_store_drivers();
void analisa_linha_rides(char line[150]);

#endif