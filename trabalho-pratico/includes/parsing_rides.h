#ifndef PARSING_RIDES_H
#define PARSING_RIDES_H

#define MAX_INFO 100
#define N_LINHASU 100000  
#define N_LINHASD 10000  
#define N_LINHASC 500
#define N_LINHASRC 1000000

typedef struct{
    char *username;            // Username do user.
    char *date;                // Data da viagem mais recente.
    double avaliacao_media;    // Avaliacao media do user.
    int numero_viagens;        // Numero de viagens que o user ja fez.
    double total_gasto;        // Total gasto pelo user.
}users_q1;

typedef struct{
    char *id;                  // Id do drivers.
    char *date;                // Data da viagem mais recente.
    double avaliacao_media;    // Avaliacao media do driver.
    int numero_viagens;        // Numero de viagem efetuados pelo driver.
    double total_auferido;     // Total ganho pelo driver. 
}drivers_q1;

typedef struct{
    char *city;             // Cidade que correspondem os seguintes parametro.
    int numero_viagens;     // Numero de viagens acumuladas por uma cidade.
    double custo;           // Custo acumulado de uma certa cidade.
}city_c1;

void read_store_rides(char *dir);
void analisa_linha_rides(char *line);

#endif