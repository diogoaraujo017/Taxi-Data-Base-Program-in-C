#ifndef PARSING_DRIVERS_H
#define PARSING_DRIVERS_H

#define MAX_INFO 100
#define N_LINHAS2 10000

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

void read_store_drivers(char *dir);
void analisa_linha_drivers(char *line);

#endif