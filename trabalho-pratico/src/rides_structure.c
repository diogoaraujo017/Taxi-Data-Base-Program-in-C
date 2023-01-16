#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rides_structure.h"
#include "users_structure.h"
#include "drivers_structure.h"
#include "parsing.h"
#include <stdint.h>
#include <stdbool.h>
#include "func_auxiliares.h"


// Hash Table das rides com a key das rides.
rides *hash_rides[N_LINHAS];


bool insert_hash_rides(char *id,char *dt,char *dr,char *user,char *c,int dist,int su,int sd,double tip){
    rides *r = malloc(sizeof(rides));
    r->id=id;
    r->date=dt;
    r->driver=dr;
    r->user=user;
    r->city=c;
    r->distance=dist;
    r->score_user=su;
    r->score_driver=sd;
    r->tip=tip;   
    
    hash_rides[atoi(id)-1] = r;
    return true;
}

// Procura um determinado username na hash table city. Esta função é bastante rápida a executar, mesmo
// existindo muitas linhas de hash, devido à existência de keys que estão associadas, uma a cada
// input colocado na hash table. Se encontrar a função dará return à linha da hash correspondente
// em forma de struct, caso contrário dará return a NULL.
rides *procura_rides(int id){
    if(id>=0 && id<1000001){ 
        return hash_rides[id];
        }
    // Return a NULL se não encontrar o user na hash table.
    return NULL;                                                                        
}




//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////

// DRIVERS




rides_driver *hash_rides_drivers[N_LINHAS_DRIVERS];


void init_hash_rides_driver(){
    for (int i = 0; i < N_LINHAS_DRIVERS; i++)
    {
        hash_rides_drivers[i] = NULL; 
    }   
}



bool insert_hash_rides_drivers(char *data,char *condutor,int avaliacao_media){

    int linha_hash = atoi (condutor)-1;

    if (hash_rides_drivers[linha_hash] == NULL){

        drivers d = *procura_hash_drivers(condutor);
        rides_driver *rd = malloc(sizeof(rides_driver));

        rd->date = data;
        rd->driver = condutor;
        rd->score_driver = (double) avaliacao_media;
        rd->numero_viagens = 1;
        rd->nome = d.name;

        hash_rides_drivers[linha_hash] = rd;
        return true;
    }

    
            
    if((calculaData(data,hash_rides_drivers[linha_hash]->date)==0)) hash_rides_drivers[linha_hash]->date = data;
           
    hash_rides_drivers[linha_hash]->score_driver = ((avaliacao_media+(hash_rides_drivers[linha_hash]->score_driver * hash_rides_drivers[linha_hash]->numero_viagens))/(hash_rides_drivers[linha_hash]->numero_viagens+1));
    hash_rides_drivers[linha_hash]->numero_viagens ++;
    return true;
        
}


rides_driver *procura_rides_driver(){
    double aval=0;
    char* data="00/00/0000";
    int aux=0,i,id=0;
    for(i=0;i<N_LINHAS_DRIVERS;i++){
        if((hash_rides_drivers[i]->score_driver>aval) || (hash_rides_drivers[i]->score_driver==aval && calculaData(hash_rides_drivers[i]->date,data)==0) || (hash_rides_drivers[i]->score_driver==aval && calculaData(hash_rides_drivers[i]->date,data)==(-1) && (atoi(hash_rides_drivers[i]->driver)<id))){
            data = hash_rides_drivers[i]->date;  
            aval = hash_rides_drivers[i]->score_driver;
            aux = i;
            id = atoi(hash_rides_drivers[i]->driver);
        }
    }
    hash_rides_drivers[aux]->score_driver-=10;

    return hash_rides_drivers[aux];
}



// rides_driver *procura_rides_driver(){
//     double aval=0,score_driver_linha;
//     char* data="00/00/0000";
//     int aux=0,i,id=0,driver_linha;
//     char* data_linha;
//     for(i=0;i<N_LINHAS_DRIVERS;i++){

//         score_driver_linha = hash_rides_drivers[i]->score_driver;
//         data_linha = hash_rides_drivers[i]->date;
//         driver_linha = atoi(hash_rides_drivers[i]->driver);
//         if((score_driver_linha>aval) || (score_driver_linha==aval && calculaData(data_linha,data)==0) || (score_driver_linha==aval && calculaData(data_linha,data)==(-1) && driver_linha<id)){
//             data = data_linha; 
//             aval = score_driver_linha;
//             aux = i;
//             id = driver_linha;
//         }
//     }
//     hash_rides_drivers[aux]->score_driver-=10;

//     return hash_rides_drivers[aux];
// }


void restore_hash_rides_drivers(){

    int i;
    for(i=0;i<N_LINHAS_DRIVERS;i++)
        if(hash_rides_drivers[i]->score_driver<0) hash_rides_drivers[i]->score_driver+=10;
}




//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////

// USERS









rides_user *hash_rides_users[N_LINHAS_USERS];


unsigned int hash_rides_users_key(char *user){
    int comp = strnlen(user,MAX_INFO);
    unsigned int num_hash = 0;
    for (int i = 0; i < comp; i++)
    {
        num_hash += user[i];
        num_hash = (num_hash * user[i]) % N_LINHAS_USERS;
    }
    return num_hash;
}



void init_hash_rides_users(){
    for (int i = 0; i < N_LINHAS_USERS; i++)
    {
        hash_rides_users[i] = NULL; 
    }   
}



bool insert_hash_rides_users(int distance,char *date,char *user){
    int i, linha_hash=0;
    int aux = hash_rides_users_key(user);
    for (i=0;i < N_LINHAS_USERS;i++){

        linha_hash = (i + aux) % N_LINHAS_USERS;

        if (hash_rides_users[linha_hash] == NULL){

            users u = *procura_hash_users(user);

            rides_user *ru = malloc(sizeof(rides_user));
            ru->distancia = distance;
            ru->data = date;
            ru->username = user;
            ru->nome = u.name;

            hash_rides_users[linha_hash] = ru;
            return true;
        }
        
        if(strcmp(hash_rides_users[linha_hash]->username,user)==0) {

            if((calculaData(date,hash_rides_users[linha_hash]->data)==0)) hash_rides_users[linha_hash]->data = date;

            hash_rides_users[linha_hash]->distancia += distance;

            return true;
        }
    }
    
    return false;
}


// rides_user *procura_rides_users(){
//     int dist=0;
//     char* data="00/00/0000";
//     int aux=0,i;
//     char *user="zzzz";
//     for(i=0;i<N_LINHAS_USERS;i++){
//         if((hash_rides_users[i]->distancia>dist) || (hash_rides_users[i]->distancia==dist && calculaData(hash_rides_users[i]->data,data)==0) || (hash_rides_users[i]->distancia==dist && calculaData(hash_rides_users[i]->data,data)==(-1) && ((hash_rides_users[i]->username)<user))){
//             dist=hash_rides_users[i]->distancia;
//             data= hash_rides_users[i]->data;  
//             user= hash_rides_users[i]->username;
//             aux = i;
//         }
//     }
//     hash_rides_users[aux]->distancia-=1000;

//     return hash_rides_users[aux];
// }


rides_user *procura_rides_users(){
    int dist=0;
    char* data="00/00/0000";
    int aux=0,i;
    char *user="zzzz";
    for(i=0;i<N_LINHAS_USERS;i++){
        if((hash_rides_users[i]->distancia>dist) || (hash_rides_users[i]->distancia==dist && calculaData(hash_rides_users[i]->data,data)==0) || (hash_rides_users[i]->distancia==dist && calculaData(hash_rides_users[i]->data,data)==(-1) && ((hash_rides_users[i]->username)<user))){
            dist=hash_rides_users[i]->distancia;
            data= hash_rides_users[i]->data;  
            user= hash_rides_users[i]->username;
            aux = i;
        }
    }
    hash_rides_users[aux]->distancia-=1000;

    return hash_rides_users[aux];
}



void restore_hash_rides_users(){

    int i;
    for(i=0;i<N_LINHAS_USERS;i++)
        if(hash_rides_users[i]->distancia<0) hash_rides_users[i]->distancia+=1000;
}