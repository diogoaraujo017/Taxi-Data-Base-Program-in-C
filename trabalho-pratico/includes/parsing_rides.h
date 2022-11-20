#ifndef PARSING_RIDES_H
#define PARSING_RIDES_H

#define MAX_INFO 100
#define N_LINHAS 1000000  


typedef struct{
    char *id;
    char *date;
    char *driver;
    char *user;
    char *city;
    int distance;
    int score_user;
    int score_driver;
    double tip;
    char *comment;  
}rides;

typedef struct drivers_q1{
    char *name;
    char gender;
    int age;
    double avaliacao_media;
    int numero_viagens;
    double total_auferido;      
}drivers_q1;

typedef struct users_q1{
    char *name;
    char gender;
    int age;
    double avaliacao_media;
    int numero_viagens;
    double total_gasto; 
}users_q1;

void read_store_rides();
void analisa_linha_rides(char *line);

#endif