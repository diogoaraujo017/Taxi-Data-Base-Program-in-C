#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rides_structure.h"
#include "users_structure.h"
#include "drivers_structure.h"
#include "parsing_rides.h"
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#define IDADE_DIA 9
#define IDADE_MES 10
#define IDADE_ANO 2022


int calculaIdade (char line[]){

    int dia,mes,ano;
    int idade;

    dia = (line[0]-'0')*10+(line[1]-'0');
    mes = (line[3]-'0')*10+(line[4]-'0');
    ano = (line[6]-'0')*1000+(line[7]-'0')*100+(line[8]-'0')*10+(line[9]-'0');

    idade = IDADE_ANO-ano-1;
    if (mes<IDADE_MES || (mes==IDADE_MES && dia<=IDADE_DIA)){
        idade++;
    }
    return idade;
}

const char* converte(char str[]){
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

rides *hash_rides_drivers[N_LINHAS];

rides *hash_rides_users[N_LINHAS];

unsigned int hash_drivers_rides(char *id){
    int comp = strnlen(id,MAX_INFO);
    unsigned int num_hash = 0;
    for (int i = 0; i < comp; i++)
    {
        num_hash += id[i];
        num_hash = (num_hash * id[i]) % N_LINHAS;
    }
    return num_hash;
}

unsigned int hash_user_rides(char *user){
    int comp = strnlen(user,MAX_INFO);
    unsigned int num_hash = 0;
    for (int i = 0; i < comp; i++)
    {
        num_hash += user[i];
        num_hash = (num_hash * user[i]) % N_LINHAS;
    }
    return num_hash;
}

void init_hash_rides_drivers(){
    for (int i = 0; i < N_LINHAS; i++)
    {
        hash_rides_drivers[i] = NULL;
    }   
}

void init_hash_rides_users(){
    for (int i = 0; i < N_LINHAS; i++)
    {
        hash_rides_users[i] = NULL;
    }   
}

bool insert_rides_drivers(rides *r){
    if (r==NULL) return false;
    int aux = hash_drivers_rides(r->driver);
    for (int i=0;i < N_LINHAS;i++){
        int next_position = (i + aux) % N_LINHAS;
    
        if (hash_rides_drivers[next_position] == NULL){
            hash_rides_drivers[next_position] = r;
            return true;
        }
    }
    return false;
}

bool insert_rides_users(rides *r){
    if (r==NULL) return false;
    int aux = hash_user_rides(r->user);
    for (int i=0;i < N_LINHAS;i++){
        int next_position = (i + aux) % N_LINHAS;
    
        if (hash_rides_users[next_position] == NULL){
            hash_rides_users[next_position] = r;
            return true;
        }
    }
    return false;
}

//Procura o user na hash table
drivers_q1 calcula_hash_rides_drivers(char *id){
    int aux = hash_drivers_rides(id);
    drivers d = *procura_hash_drivers(id);
    drivers_q1 result = {.name=d.name,
                         .gender=d.gender,
                         .age=calculaIdade((d.birth_day)),
                         .avaliacao_media=0.000,
                         .numero_viagens=0,
                         .total_auferido=0.000};
    for (int i = 0; i < N_LINHAS; i++){
        int next_position = (i + aux) % N_LINHAS;
        if (hash_rides_drivers[next_position] != NULL && strncmp(hash_rides_drivers[next_position]->driver, id, MAX_INFO)==0){
            result.avaliacao_media += hash_rides_drivers[next_position]->score_driver;    
            result.numero_viagens++;
            if ((strcmp (converte((*procura_hash_drivers(hash_rides_drivers[next_position]->driver)).car_class),"basic"))==0) result.total_auferido += 3.25 + 0.62*(hash_rides_drivers[next_position]->distance) + (hash_rides_drivers[next_position]->tip);
            else if ((strcmp (converte((*procura_hash_drivers(hash_rides_drivers[next_position]->driver)).car_class),"green"))==0) result.total_auferido += 4.00 + 0.79*(hash_rides_drivers[next_position]->distance) + (hash_rides_drivers[next_position]->tip);
            else if ((strcmp (converte((*procura_hash_drivers(hash_rides_drivers[next_position]->driver)).car_class),"premium"))==0) result.total_auferido += 5.20 + 0.94*(hash_rides_drivers[next_position]->distance) + (hash_rides_drivers[next_position]->tip);    
        }
    }
    
    if(result.numero_viagens != 0) result.avaliacao_media = result.avaliacao_media/result.numero_viagens;
    
    return result;
}

users_q1 calcula_hash_rides_users(char *user){
    int aux = hash_user_rides(user);
    users u = *procura_hash_users(user);
    users_q1 result = {.name=u.name,
                       .gender=u.gender,
                       .age=calculaIdade((u.birth_day)),
                       .avaliacao_media=0.000,
                       .numero_viagens=0,
                       .total_gasto=0.000};
    for (int i = 0; i < N_LINHAS; i++){
        int next_position = (i + aux) % N_LINHAS;
        if (hash_rides_users[next_position] != NULL && strncmp(hash_rides_users[next_position]->user, user, MAX_INFO)==0){
            result.avaliacao_media += hash_rides_users[next_position]->score_user;    
            result.numero_viagens++;
            if ((strcmp (converte((*procura_hash_drivers(hash_rides_users[next_position]->driver)).car_class),"basic"))==0) result.total_gasto += 3.25 + 0.62*(hash_rides_users[next_position]->distance);
            else if ((strcmp (converte((*procura_hash_drivers(hash_rides_users[next_position]->driver)).car_class),"green"))==0) result.total_gasto += 4.00 + 0.79*(hash_rides_users[next_position]->distance);
            else if ((strcmp (converte((*procura_hash_drivers(hash_rides_users[next_position]->driver)).car_class),"premium"))==0) result.total_gasto += 5.20 + 0.94*(hash_rides_users[next_position]->distance);    
        }
    }
    
    if(result.numero_viagens != 0) result.avaliacao_media = result.avaliacao_media/result.numero_viagens;
    
    return result;
}



