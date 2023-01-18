#ifndef PARSING_H
#define PARSING_H

void read_store(char *dir, char file_aux);

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
    char *id;
    char *date;
    char *driver;
    char *user;
    char *city;
    int distance;
    int score_user;
    int score_driver;
    double tip;     
}rides;

void analisa_linha_rides(char *line);

// RIDES_DRIVERS /////////////////////////////////////////////////////////////

typedef struct{
    char *date;
    char *driver;
    double score_driver;
    char *nome;
    int numero_viagens;
    double score_total;
}rides_driver;

// RIDES_USER /////////////////////////////////////////////////////////////

typedef struct{
    int distancia;
    char *data;
    char *username;
    char *nome;
}rides_user;

// RIDES_DRIVER_CITY /////////////////////////////////////////////////////////////

typedef struct{
    double avaliacao_media;
    char *id;
    int numero_viagens;
    char *nome;
    double avaliacao_total;
}rides_driver_city;

// RIDES_GENDER /////////////////////////////////////////////////////////////

typedef struct{
    char *id_condutor;
    char *nome_condutor;
    char *username_utilizador;
    char *nome_utilizador;
    char *data_driver;
    char *data_user;
    int isValid;
}rides_gender;

// RIDES_DATE //////////////////////////////////////////////////////////////////

typedef struct{
    int distance;
    char *date;
    char *id;
    char *city;
    double tip;
    int isValid;
}rides_date;

#endif