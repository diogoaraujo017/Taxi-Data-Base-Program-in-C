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




typedef struct{
    char *date;
    char *driver;
    double score_driver;
    char *nome;
    int numero_viagens;
}rides_driver;




typedef struct{
    int distancia;
    char *data;
    char *username;
    char *nome;
}rides_user;



typedef struct{
    char* id;
    char *nome;
    double avalicao_media;
}rides_driver_city;

////////////////////////////////////////////////////////////////////

#endif