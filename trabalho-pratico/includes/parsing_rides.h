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
}rides;

typedef struct drivers_q1{
    char name[MAX_INFO];
    char gender;
    int age;
    double avaliacao_media;
    int numero_viagens;
    double total_auferido;      
}drivers_q1;

typedef struct users_q1{
    char name[MAX_INFO];
    char gender;
    int age;
    double avaliacao_media;
    int numero_viagens;
    double total_gasto; 
}users_q1;

void read_store_rides();
void analisa_linha_rides(char line[150]);

#endif