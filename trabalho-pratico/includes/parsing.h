#ifndef PARSING_H
#define PARSING_H

void read_store(char *dir, char file_aux);
char* filtra(char *init,char *dest);

// DRIVERS //////////////////////////////////

typedef struct{
    char *id;                // Id do condutor.
    char *name;              // Nome do condutor.
    char *birth_day;         // Data de nascimento do condutor.
    char gender;             // Sexo do condutor.
    char *car_class;         // Classe do carro do condutor.
    char *license_plate;     // Matricula do carro do condutor.
    char *city;              // Cidade de residencia do condutor.
    char *account_creation;  // Data de criação da conta do condutor.
    char *account_status;    // Status da conta do condutor.
} drivers;

void analisa_linha_drivers(char *line);



// USERS ///////////////////////////////////////////////////////////

typedef struct{
    char *username;          // Username do user.
    char *name;              // Nome do user.
    char gender;             // Sexo do user.
    char *birth_day;         // Data de nascimento do user.
    char *account_creation;  // Data da criacao da conta do user.
    char *pay_method;        // Metodo de pagamentos do user.
    char *account_status;    // Status da conta do user.
}users;

void analisa_linha_users(char *line);



// RIDES /////////////////////////////////////////////////////////////

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

void analisa_linha_rides(char *line);


////////////////////////////////////////////////////////////////////



#endif