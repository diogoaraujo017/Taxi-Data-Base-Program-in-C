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
rides **hash_rides;

bool insert_hash_rides(char *id,char *dt,char *dr,char *user,char *c,int dist,double su,double sd,double tip){
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
    return hash_rides[id];                                                                      
}


void free_hash_rides(){
    int i;
    for(i=0;i<n_linhas;i++){
        if(hash_rides[i]!=NULL){
            free(hash_rides[i]->id);
            free(hash_rides[i]->date);
            free(hash_rides[i]->driver);
            free(hash_rides[i]->user);
            free(hash_rides[i]->city);
        }
            free(hash_rides[i]);
    }
    free(hash_rides);
}


//// DRIVERS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rides_driver **hash_rides_drivers;


void sortQ2(){
    int i;
    for (i=0;i < n_linhas_drivers;i++){
         if(hash_rides_drivers[i]==NULL){
            rides_driver *rd = malloc(sizeof(rides_driver));
            rd->score_driver = 0;
            rd->date = "01/01/1000";
            rd->driver = "1000000";

            hash_rides_drivers[i] = rd;
         }
    }

    qsort(hash_rides_drivers, n_linhas_drivers, sizeof(rides_driver*), compareDrivers);
}


bool insert_hash_rides_drivers(char *data,char *condutor,double avaliacao_media){

    int linha_hash = atoi (condutor)-1;

    if (hash_rides_drivers[linha_hash] == NULL){

        drivers *d =procura_hash_drivers(condutor);

        if(d==NULL || !strcmp(d->account_status,"inactive")) return true;

        rides_driver *rd = malloc(sizeof(rides_driver));
        rd->date = data;
        rd->driver = condutor;
        rd->score_driver = avaliacao_media;
        rd->numero_viagens = 1;
        rd->score_total=avaliacao_media;
        rd->nome = d->name;

        hash_rides_drivers[linha_hash] = rd;
        return true;
    }

    
            
    if((calculaData(data,hash_rides_drivers[linha_hash]->date)==0)) hash_rides_drivers[linha_hash]->date = data;
           
    hash_rides_drivers[linha_hash]->score_total += avaliacao_media;
    hash_rides_drivers[linha_hash]->numero_viagens ++;
    hash_rides_drivers[linha_hash]->score_driver = hash_rides_drivers[linha_hash]->score_total/hash_rides_drivers[linha_hash]->numero_viagens;

    return true;
        
}


rides_driver *procura_rides_driver(int ind){
    return hash_rides_drivers[ind];
}

int compareDrivers(const void *elem1, const void *elem2){
    rides_driver **rd1 = (rides_driver**)elem1;
    rides_driver **rd2 = (rides_driver**)elem2;               

    if((*rd1)->score_driver > (*rd2)->score_driver) {
        return 1;
    } else if ((*rd1)->score_driver < (*rd2)->score_driver) {
        return -1;
    } else if (calculaData((*rd1)->date, (*rd2)->date) == 0) {
        return 1;
    } else if (calculaData((*rd2)->date, (*rd1)->date) == 0) {
        return -1;
    } else if (atoi((*rd1)->driver) < atoi((*rd2)->driver)){
        return 1;
    } else return -1;
  
}


void free_hash_rides_drivers(){
    int i;
    for(i=0;i<n_linhas_drivers;i++){
        free(hash_rides_drivers[i]);
    }
    free(hash_rides_drivers);
}


//// USERS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rides_user **hash_rides_users;

void sortQ3(){
    int i;
    for (i=0;i < n_linhas_users;i++){
         if(hash_rides_users[i]==NULL){
            rides_user *ru = malloc(sizeof(rides_user));
            ru->distancia = 0;
            ru->data = "01/01/1000";
            ru->username = "null";
            ru->nome = "null";

            hash_rides_users[i] = ru;
         }
    }

    qsort(hash_rides_users, n_linhas_users, sizeof(rides_user*), compareUsers);
}

bool insert_hash_rides_users(int distance,char *date,char *user){
    register int i, linha_hash=0;
    int aux = hash_users(user);
    users *u = procura_hash_users(user);

    if(u==NULL || strcmp(u->account_status,"inactive")==0) return true;

    for (i=0;i < n_linhas_users;i++){

        linha_hash = (i + aux) % n_linhas_users;

        if (hash_rides_users[linha_hash] == NULL){
            rides_user *ru = malloc(sizeof(rides_user));
            ru->distancia = distance;
            ru->data = date;
            ru->username = user;
            ru->nome = u->name;

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

rides_user *procura_rides_users(int ind){
    return hash_rides_users[ind];
}

int compareUsers(const void *elem1, const void *elem2){
    rides_user **ru1 = (rides_user**)elem1;
    rides_user **ru2 = (rides_user**)elem2;               

    
    if((*ru1)->distancia > (*ru2)->distancia) {
        return 1;
    } else if ((*ru1)->distancia < (*ru2)->distancia) {
        return -1;
    } else if (calculaData((*ru1)->data, (*ru2)->data) == 0) {
        return 1;
    } else if (calculaData((*ru2)->data, (*ru1)->data) == 0) {
        return -1;
    } else if (strcmp((*ru2)->username, (*ru1)->username)<0){
        return -1;
    } else return 1;
  
}


void free_hash_rides_users(){
    int i;
    for(i=0;i<n_linhas_users;i++){
        free(hash_rides_users[i]);
    }
    free(hash_rides_users);
}


//// DRIVERS CITY  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rides_driver_city **hash_rides_drivers_city;

void sortQ7(){
    int i;
    for (i=0;i < n_linhas_drivers;i++){
         if(hash_rides_drivers_city[i]==NULL){
            rides_driver_city *rdc = malloc(sizeof(rides_driver_city));
            rdc->avaliacao_media = 0;
            rdc->id = "0";
            rdc->numero_viagens = 0;
            rdc->nome = "null";
            rdc->avaliacao_media = 0.000;

            hash_rides_drivers_city[i] = rdc;
         }
    }

    qsort(hash_rides_drivers_city, n_linhas_drivers, sizeof(rides_driver_city*), compareCity);
}

bool insert_hash_rides_drivers_city(char* city){
    register int i;
    int id_driver;
    drivers *d;
    for(i=0;i<n_linhas;i++){
        if(hash_rides[i]!=NULL){

            d = procura_hash_drivers(hash_rides[i]->driver);

            if(d!=NULL){

            
                id_driver= atoi(d->id)-1;

                if(strcmp(d->account_status,"active")==0 && strcmp(hash_rides[i]->city,city)==0){

                    if(hash_rides_drivers_city[id_driver]==NULL){

                        rides_driver_city *rdc = malloc(sizeof(rides_driver_city));
                        rdc->numero_viagens=1;
                        rdc->id=d->id;
                        rdc->avaliacao_media=hash_rides[i]->score_driver;
                        rdc->nome=d->name;
                        rdc->avaliacao_total=hash_rides[i]->score_driver;
                        hash_rides_drivers_city[id_driver]=rdc;
                    }

                    else{
                        hash_rides_drivers_city[id_driver]->numero_viagens++;
                        hash_rides_drivers_city[id_driver]->avaliacao_total+=hash_rides[i]->score_driver;
                        hash_rides_drivers_city[id_driver]->avaliacao_media=hash_rides_drivers_city[id_driver]->avaliacao_total/hash_rides_drivers_city[id_driver]->numero_viagens;
                    }
                }
            }
        }
    }
    return true;
}

rides_driver_city *procura_rides_driver_city(int ind){
    return hash_rides_drivers_city[ind];
}

int compareCity(const void *elem1, const void *elem2){
    rides_driver_city **rdc1 = (rides_driver_city**)elem1;
    rides_driver_city **rdc2 = (rides_driver_city**)elem2;               

    
    if((*rdc1)->avaliacao_media > (*rdc2)->avaliacao_media) {
        return 1;
    } else if ((*rdc1)->avaliacao_media < (*rdc2)->avaliacao_media) {
        return -1;
    } else if (atoi((*rdc1)->id) > atoi((*rdc2)->id)) {
        return 1;
    } else return -1;
  
}

void free_hash_rides_driver_city(){
    register int i;
    for(i=0;i<n_linhas_drivers;i++){
        if(hash_rides_drivers_city[i]!=NULL){
            free(hash_rides_drivers_city[i]);
            hash_rides_drivers_city[i]=NULL;
        }
    }
}


//// RIDES_GENDER /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rides_gender **hash_rides_gender;

void init_hash_rides_gender(int aux){
    int i;

    for(i=aux;i<n_linhas_gender;i++){
        hash_rides_gender[i]=NULL;
    } 
}

bool insert_hash_rides_gender(char genero,int idade){
    int i, j, cont=0;
    drivers *d;
    users *u;
    
    for(i=0;i<n_linhas;i++){
        if(hash_rides[i]!=NULL){

            d = procura_hash_drivers(hash_rides[i]->driver);
            u = procura_hash_users(hash_rides[i]->user);
            
            if(d!=NULL && u!=NULL){
                
                if(strcmp(u->account_status,"active")==0 && strcmp(d->account_status,"active")==0 && d->gender[0]==genero && u->gender[0]==genero && calculaIdade(u->account_creation)>=idade && calculaIdade(d->account_creation)>=idade){
                    
                    cont++;
                    
                    if(cont>=n_linhas_gender-1) {
                        n_linhas_gender = n_linhas_gender*5;
                        hash_rides_gender = realloc(hash_rides_gender,n_linhas_gender*sizeof(rides_gender*));
                        init_hash_rides_gender(cont-1);
                    }

                    for(j=0;j<n_linhas_gender;j++){
                        if(hash_rides_gender[j]==NULL) break;
                    }
            
                    rides_gender *rg = malloc(sizeof(rides_gender));
                    rg->id_condutor=d->id;
                    rg->nome_condutor=d->name;
                    rg->username_utilizador=u->username;
                    rg->nome_utilizador=u->name;
                    rg->data_driver=d->account_creation;
                    rg->data_user=u->account_creation;
                    rg->isValid=1;
                    rg->id_viagem=hash_rides[i]->id;
                    
                    hash_rides_gender[j]=rg;
                }
            }
        }
    }
    return true;
}

rides_gender *procura_rides_gender(){
    register int i,aux;
    char* data_atual_user="00/00/2222";
    char* data_atual_driver="00/00/2222";
    int data_registo_user,data_registo_driver;
    int end=0,id_atual=99999999;
    
    for(i=0;i<n_linhas_gender;i++){

        if(hash_rides_gender[i]!=NULL){

            data_registo_user=calculaData(hash_rides_gender[i]->data_user,data_atual_user);
            data_registo_driver=calculaData(hash_rides_gender[i]->data_driver,data_atual_driver);
        
            if (hash_rides_gender[i]->isValid==1 && (data_registo_driver==1 || (data_registo_driver==-1 && data_registo_user==1) || (data_registo_driver==-1 && data_registo_user==-1 && atoi(hash_rides_gender[i]->id_viagem)<id_atual))){
                end=1;
                data_atual_user=hash_rides_gender[i]->data_user;
                data_atual_driver=hash_rides_gender[i]->data_driver;
                id_atual=atoi(hash_rides_gender[i]->id_viagem);
                aux=i;
            }
        }
    }

    if(end==0) return NULL;

    hash_rides_gender[aux]->isValid=0;
    return hash_rides_gender[aux];
}


void free_hash_rides_gender(){
    register int i;
    for(i=0;i<n_linhas_gender;i++){
        if(hash_rides_gender[i]!=NULL){
            free(hash_rides_gender[i]);
            hash_rides_gender[i]=NULL;
        }
    }
}

//// RIDES_DATE /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rides_date **hash_rides_date;

bool insert_hash_rides_date(char *date1,char *date2){
    register int i,j;
    
    for(i=0;i<n_linhas;i++){

        if(hash_rides[i]!=NULL && (hash_rides[i]->tip != 0.0) && calculaData(hash_rides[i]->date,date1)<=0 && calculaData(date2,hash_rides[i]->date)<=0){

         for(j=0;j<n_linhas_drivers;j++){
                if(hash_rides_date[j]==NULL) break;
            }

                rides_date *rd = malloc(sizeof(rides_date));
                rd->distance=hash_rides[i]->distance;
                rd->date=hash_rides[i]->date;
                rd->id=hash_rides[i]->id;
                rd->city=hash_rides[i]->city;
                rd->tip=hash_rides[i]->tip;
                rd->id_viagem=hash_rides[i]->id;
                rd->isValid=1;

                hash_rides_date[j]=rd;
       }
    }
    return true;
}

rides_date *procura_rides_date(){
    register int i,aux;
    char* recent_date = "00/00/0000";
    int dist=0,end=0,id_atual=0;

    for(i=0;i<n_linhas_drivers;i++){

        if(hash_rides_date[i]!=NULL && hash_rides_date[i]->isValid==1 && (dist<hash_rides_date[i]->distance || (dist==hash_rides_date[i]->distance && calculaData(hash_rides_date[i]->date,recent_date)<=0) || (dist==hash_rides_date[i]->distance && calculaData(hash_rides_date[i]->date,recent_date)==-1 && atoi(hash_rides_date[i]->id_viagem)>id_atual))){
                
                end=1;
                dist=hash_rides_date[i]->distance;
                recent_date=hash_rides_date[i]->date;
                id_atual=atoi(hash_rides_date[i]->id_viagem);
                aux=i;
        }
    }
 
    if(end==0) return NULL;

    hash_rides_date[aux]->isValid=0;
    return hash_rides_date[aux];
}


void free_hash_rides_date(){
    int i;
    for(i=0;i<n_linhas_drivers;i++){
        free(hash_rides_date[i]);
    }
    free(hash_rides_date);
    free(hash_rides_drivers_city);
    free(hash_rides_gender);
}



void allocate_rides(){ 
    hash_rides = (rides**)malloc(n_linhas*sizeof(rides*));

    int i;
    for(i=0;i<n_linhas;i++){
        hash_rides[i]=NULL;
    } 
}


void allocate_rides_drivers(){
    hash_rides_drivers = (rides_driver**)malloc(n_linhas_drivers*sizeof(rides_driver*));
        
    int i;
    for(i=0;i<n_linhas_drivers;i++){
        hash_rides_drivers[i]=NULL;
    }
}


void allocate_rides_users(){
    hash_rides_users = (rides_user**)malloc(n_linhas_users*sizeof(rides_user*));

    int i;
    for(i=0;i<n_linhas_users;i++){
        hash_rides_users[i]=NULL;
    }
}


void allocate_rides_drivers_city(){
    hash_rides_drivers_city = (rides_driver_city**)malloc(n_linhas_drivers*sizeof(rides_driver_city*));

    int i;
    for(i=0;i<n_linhas_drivers;i++){
        hash_rides_drivers_city[i]=NULL;
    }
}


void allocate_rides_drivers_gender(){
    hash_rides_gender = (rides_gender**)malloc(n_linhas_gender*sizeof(rides_gender*));

    int i;
    for(i=0;i<n_linhas_gender;i++){
        hash_rides_gender[i]=NULL;
    }
}


void allocate_rides_date(){
    hash_rides_date = (rides_date**)malloc(n_linhas_users*sizeof(rides_date*));

    int i;
    for(i=0;i<n_linhas_drivers;i++){
        hash_rides_date[i]=NULL;
    }
}