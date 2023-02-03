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


struct Rides{
    char *id;
    char *date;
    char *driver;
    char *user;
    char *city;
    int distance;
    double score_user;
    double score_driver;
    double tip;     
};

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

void getRideFields(int *id, char **date, char **driver, char **user, char **city, int *distance, double *score_user, double *score_driver, double *tip) {
  rides *r = NULL;
  r =  hash_rides[*id];
  
  if(r==NULL){
      *date=NULL;
      return;
  }

  *date = r->date;
  *driver = r->driver;
  *user = r->user;
  *city = r->city;
  *distance = r->distance;
  *score_user = r->score_user;
  *score_driver = r->score_driver;
  *tip = r->tip;
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

struct Rides_driver{
    char *date;
    char *driver;
    double score_driver;
    char *nome;
    int numero_viagens;
    double score_total;
};

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
    
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, 
         *car_class_driver = NULL, *city_driver = NULL, *account_creation_driver = NULL, 
         *account_status_driver = NULL; 

    int linha_hash = atoi (condutor)-1;

    if (hash_rides_drivers[linha_hash] == NULL){

        getDriverFields(&condutor, &name_driver, &birth_day_driver, &gender_driver, &car_class_driver, &city_driver, &account_creation_driver, &account_status_driver); 

        if(name_driver==NULL || !strcmp(account_status_driver,"inactive")) return true;

        rides_driver *rd = malloc(sizeof(rides_driver));
        rd->date = data;
        rd->driver = condutor;
        rd->score_driver = avaliacao_media;
        rd->numero_viagens = 1;
        rd->score_total=avaliacao_media;
        rd->nome = name_driver;

        hash_rides_drivers[linha_hash] = rd;
        return true;
    }

    
            
    if((calculaData(data,hash_rides_drivers[linha_hash]->date)==0)) hash_rides_drivers[linha_hash]->date = data;
           
    hash_rides_drivers[linha_hash]->score_total += avaliacao_media;
    hash_rides_drivers[linha_hash]->numero_viagens ++;
    hash_rides_drivers[linha_hash]->score_driver = hash_rides_drivers[linha_hash]->score_total/hash_rides_drivers[linha_hash]->numero_viagens;

    return true;
        
}

void getRideDriverFields(int *id,char **date, char **driver, double *score_driver, char **nome, int *numero_viagens, double *score_total) {
  rides_driver *rd = NULL;
  rd =  hash_rides_drivers[*id];
  
  if(rd==NULL){
      *date=NULL;
      return;
  }

  *date = rd->date;
  *driver = rd->driver;
  *score_driver = rd->score_driver;
  *nome = rd->nome;
  *numero_viagens = rd->numero_viagens;
  *score_total = rd->score_total;

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

struct Rides_user{
    int distancia;
    char *date;
    char *username;
    char *nome;
};

rides_user **hash_rides_users;

void sortQ3(){
    int i;
    for (i=0;i < n_linhas_users;i++){
         if(hash_rides_users[i]==NULL){
            rides_user *ru = malloc(sizeof(rides_user));
            ru->distancia = 0;
            ru->date = "01/01/1000";
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

    char *name_user = NULL, *gender_user = NULL, *birth_day_user = NULL, 
         *account_creation_user = NULL, *account_status_user = NULL;

    getUserFields(&user, &name_user, &gender_user, &birth_day_user, &account_creation_user, &account_status_user);

    if(name_user==NULL || strcmp(account_status_user,"inactive")==0) return true;

    for (i=0;i < n_linhas_users;i++){

        linha_hash = (i + aux) % n_linhas_users;

        if (hash_rides_users[linha_hash] == NULL){
            rides_user *ru = malloc(sizeof(rides_user));
            ru->distancia = distance;
            ru->date = date;
            ru->username = user;
            ru->nome = name_user;

            hash_rides_users[linha_hash] = ru;
            return true;
        }
        
        if(strcmp(hash_rides_users[linha_hash]->username,user)==0) {

            if((calculaData(date,hash_rides_users[linha_hash]->date)==0)) hash_rides_users[linha_hash]->date = date;

            hash_rides_users[linha_hash]->distancia += distance;

            return true;
        }
    }
    
    return false;
}

void getRideUserFields(int *ind, int *distancia, char **date, char **username, char **nome) {
  rides_user *ru = NULL;
  ru =  hash_rides_users[*ind];
  
  if(ru==NULL){
      *date=NULL;
      return;
  }

  *distancia = ru->distancia;
  *date = ru->date;
  *username = ru->username;
  *nome = ru->nome;

}

int compareUsers(const void *elem1, const void *elem2){
    rides_user **ru1 = (rides_user**)elem1;
    rides_user **ru2 = (rides_user**)elem2;               

    
    if((*ru1)->distancia > (*ru2)->distancia) {
        return 1;
    } else if ((*ru1)->distancia < (*ru2)->distancia) {
        return -1;
    } else if (calculaData((*ru1)->date, (*ru2)->date) == 0) {
        return 1;
    } else if (calculaData((*ru2)->date, (*ru1)->date) == 0) {
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

struct Rides_driver_city{
    double avaliacao_media;
    char *id;
    int numero_viagens;
    char *nome;
    double avaliacao_total;
};

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
    int i;
    int id_driver = 0;
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, *car_class_driver = NULL, 
         *city_driver = NULL, *account_creation_driver = NULL, *account_status_driver = NULL;

    for(i=0;i<n_linhas;i++){
        if(hash_rides[i]!=NULL){

            getDriverFields(&hash_rides[i]->driver, &name_driver, &birth_day_driver, &gender_driver, &car_class_driver, &city_driver, &account_creation_driver, &account_status_driver);

            if(name_driver!=NULL){

            
                id_driver = atoi(hash_rides[i]->driver)-1;

                if(strcmp(account_status_driver,"active")==0 && strcmp(hash_rides[i]->city,city)==0){

                    if(hash_rides_drivers_city[id_driver]==NULL){

                        rides_driver_city *rdc = malloc(sizeof(rides_driver_city));
                        rdc->numero_viagens=1;
                        rdc->id=hash_rides[i]->driver;
                        rdc->avaliacao_media=hash_rides[i]->score_driver;
                        rdc->nome=name_driver;
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

void getRideDriverCityFields(int *ind, double *avaliacao_media, char **id, int *numero_viagens, char **nome, double *avaliacao_total) {
  rides_driver_city *rdc = NULL;
  rdc =  hash_rides_drivers_city[*ind];
  
  if(rdc==NULL){
      *id=NULL;
      return;
  }

  *avaliacao_media = rdc->avaliacao_media;
  *id = rdc->id;
  *numero_viagens = rdc->numero_viagens;
  *nome = rdc->nome;
  *avaliacao_total = rdc->avaliacao_total;
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

struct Rides_gender{
    char *id_condutor;
    char *nome_condutor;
    char *username_utilizador;
    char *nome_utilizador;
    char *data_driver;
    char *data_user;
    char *id_viagem;
    int isValid;
};

rides_gender **hash_rides_gender;

void init_hash_rides_gender(int aux){
    int i;

    for(i=aux;i<n_linhas_gender;i++){
        hash_rides_gender[i]=NULL;
    } 
}

bool insert_hash_rides_gender(char genero,int idade){
    int i, j, cont=0;
    
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, *car_class_driver = NULL, 
         *city_driver = NULL, *account_creation_driver = NULL, *account_status_driver = NULL;
    
    char *name_user = NULL, *gender_user = NULL, *birth_day_user = NULL, 
         *account_creation_user = NULL, *account_status_user = NULL;
    
    for(i=0;i<n_linhas;i++){
        if(hash_rides[i]!=NULL){

            getDriverFields(&hash_rides[i]->driver, &name_driver, &birth_day_driver, &gender_driver, &car_class_driver, &city_driver, &account_creation_driver, &account_status_driver);
            getUserFields(&hash_rides[i]->user, &name_user, &gender_user, &birth_day_user, &account_creation_user, &account_status_user);

            if(name_driver!=NULL && name_user!=NULL){
                
                if(strcmp(account_status_user,"active")==0 && strcmp(account_status_driver,"active")==0 && gender_driver[0]==genero && gender_user[0]==genero && calculaIdade(account_creation_user)>=idade && calculaIdade(account_creation_driver)>=idade){
                    
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
                    rg->id_condutor = hash_rides[i]->driver;
                    rg->nome_condutor = name_driver;
                    rg->username_utilizador = hash_rides[i]->user;
                    rg->nome_utilizador = name_user;
                    rg->data_driver = account_creation_driver;
                    rg->data_user = account_creation_user;
                    rg->isValid = 1;
                    rg->id_viagem = hash_rides[i]->id;
                    
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

void getRideGenderFields(char **id_condutor, char **nome_condutor, char **username_utilizador, char **nome_utilizador, char **data_driver, char **data_user, char **id_viagem, int *isValid) {
  rides_gender *rg = NULL;
  rg = procura_rides_gender();
  
  if(rg==NULL){
      *nome_condutor=NULL;
      return;
  }

  *id_condutor = rg->id_condutor;
  *nome_condutor = rg->nome_condutor;
  *username_utilizador = rg->username_utilizador;
  *nome_utilizador = rg->nome_utilizador;
  *data_driver = rg->data_driver;
  *data_user = rg->data_user;
  *id_viagem = rg->id_viagem;
  *isValid = rg->isValid;
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

struct Rides_date{
    int distance;
    char *date;
    char *id;
    char *city;
    double tip;
    char *id_viagem;
    int isValid;
};

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

void getRideDateFields(int *distance, char **date, char **id, char **city, double *tip, char **id_viagem, int *isValid) {
  rides_date *rd = NULL;
  rd = procura_rides_date();
  
  if(rd==NULL){
      *date=NULL;
      return;
  }

  *distance = rd->distance;
  *date = rd->date;
  *id = rd->id;
  *city = rd->city;
  *tip = rd->tip;
  *id_viagem = rd->id_viagem;
  *isValid = rd->isValid;
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