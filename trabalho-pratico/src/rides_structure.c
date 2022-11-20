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

// return True: Data1>Data2
// return False: Data2>=Data1
int calculaData (char *line,char *line2){

    int dia1,mes1,ano1;
    int dia2,mes2,ano2;

    dia1 = (line[0]-'0')*10+(line[1]-'0');
    mes1 = (line[3]-'0')*10+(line[4]-'0');
    ano1 = (line[6]-'0')*1000+(line[7]-'0')*100+(line[8]-'0')*10+(line[9]-'0');

    dia2 = (line2[0]-'0')*10+(line2[1]-'0');
    mes2 = (line2[3]-'0')*10+(line2[4]-'0');
    ano2 = (line2[6]-'0')*1000+(line2[7]-'0')*100+(line2[8]-'0')*10+(line2[9]-'0');

    if (ano1>ano2) return 0;
    else if (mes1>mes2) return 0;
    else if (dia1>dia2) return 0;
    return 1;
}

int calculaIdade (char *line){

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

drivers_q1 *hash_rides_drivers[N_LINHASD];

users_q1 *hash_rides_users[N_LINHASU];

unsigned int hash_drivers_rides(char *id){
    int comp = strnlen(id,MAX_INFO);
    unsigned int num_hash = 0;
    for (int i = 0; i < comp; i++)
    {
        num_hash += id[i];
        num_hash = (num_hash * id[i]) % N_LINHASD;
    }
    return num_hash;
}

unsigned int hash_user_rides(char *user){
    int comp = strnlen(user,MAX_INFO);
    unsigned int num_hash = 0;
    for (int i = 0; i < comp; i++)
    {
        num_hash += user[i];
        num_hash = (num_hash * user[i]) % N_LINHASU;
    }
    return num_hash;
}

void init_hash_rides_drivers(){
    for (int i = 0; i < N_LINHASD; i++)
    {
        hash_rides_drivers[i] = NULL;
    }   
}

void init_hash_rides_users(){
    for (int i = 0; i < N_LINHASU; i++)
    {
        hash_rides_users[i] = NULL;
    }   
}

bool insert_rides_drivers(char *id,char *dt,char *dr,char *u,char *ac,int dist,int su,int sd,double tip,char *cm){
    drivers d = *procura_hash_drivers(dr);
    drivers_q1 *d1 = malloc(sizeof(drivers_q1));
    d1->id = dr;
    d1->date = dt;
    d1->avaliacao_media = (double) sd;
    d1->numero_viagens = 1;
    if ((strcmp(converte(d.car_class),"basic"))==0) d1->total_auferido = 3.25 + 0.62*dist + tip;
    else if ((strcmp(converte(d.car_class),"green"))==0) d1->total_auferido = 4.00 + 0.79*dist + tip;
    else if ((strcmp(converte(d.car_class),"premium"))==0) d1->total_auferido = 5.20 + 0.94*dist + tip;
    int aux = hash_drivers_rides(dr);
    for (int i=0;i < N_LINHASD;i++){
        int next_position = (i + aux) % N_LINHASD;
    
        if (hash_rides_drivers[next_position] == NULL){
            hash_rides_drivers[next_position] = d1;
            return true;
        }

        if(strcmp(hash_rides_drivers[next_position]->id,dr)==0) {
            if((calculaData(d1->date,hash_rides_drivers[next_position]->date)==0)) hash_rides_drivers[next_position]->date = d1->date;
            hash_rides_drivers[next_position]->avaliacao_media += sd;
            hash_rides_drivers[next_position]->numero_viagens += 1;
            hash_rides_drivers[next_position]->total_auferido += d1->total_auferido;
            return true;
        }
    }
    return false;
}

bool insert_rides_users(char *id,char *dt,char *dr,char *user,char *ac,int dist,int su,int sd,double tip,char *cm){
    drivers d = *procura_hash_drivers(dr);
    users_q1 *u1 = malloc(sizeof(users_q1));
    u1->username = user;
    u1->date = dt;
    u1->avaliacao_media = (double) su;
    u1->numero_viagens = 1;
    if ((strcmp(converte(d.car_class),"basic"))==0) u1->total_gasto = 3.25 + 0.62*dist + tip;
    else if ((strcmp(converte(d.car_class),"green"))==0) u1->total_gasto = 4.00 + 0.79*dist + tip;
    else if ((strcmp(converte(d.car_class),"premium"))==0) u1->total_gasto = 5.20 + 0.94*dist + tip;
    int aux = hash_user_rides(user);
    for (int i=0;i < N_LINHASU;i++){
        int next_position = (i + aux) % N_LINHASU;
    
        if (hash_rides_users[next_position] == NULL){
            hash_rides_users[next_position] = u1;
            return true;
        }

        if(strcmp(hash_rides_users[next_position]->username,user)==0) {
            if((calculaData(u1->date,hash_rides_users[next_position]->date)==0)) hash_rides_users[next_position]->date = u1->date;
            hash_rides_users[next_position]->avaliacao_media += su;
            hash_rides_users[next_position]->numero_viagens += 1;
            hash_rides_users[next_position]->total_gasto += u1->total_gasto;
            return true;
        }
    }
    return false;
}

drivers_q1 *procura_rides_drivers(char *id){
    int aux = hash_drivers_rides(id);
    for (int i = 0; i < N_LINHASD; i++){
        int next_position = (i + aux) % N_LINHASD;
        if (strncmp(hash_rides_drivers[next_position]->id, id, MAX_INFO)==0){
            return hash_rides_drivers[next_position];
        }
    }
    return NULL;
}

users_q1 *procura_rides_users(char *username){
    int aux = hash_user_rides(username);
    for (int i = 0; i < N_LINHASU; i++){
        int next_position = (i + aux) % N_LINHASU;
        if (strncmp(hash_rides_users[next_position]->username, username, MAX_INFO)==0){
            return hash_rides_users[next_position];
        }
    }
    return NULL;
}



