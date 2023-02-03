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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// RIDES  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

void allocate_rides(){ 
    
    int i;

    hash_rides = (rides**)malloc(n_lines*sizeof(rides*));

    for(i=0; i < n_lines; i++){

        hash_rides[i]=NULL;
    } 
}

bool insert_hash_rides(char *id,char *date,char *driver_id,char *username,char *city,int distance,
                       double score_user,double score_driver,double tip){
    
    rides *r = malloc(sizeof(rides));
    
    r->id = id;
    r->date = date;
    r->driver = driver_id;
    r->user = username;
    r->city = city;
    r->distance = distance;
    r->score_user = score_user;
    r->score_driver = score_driver;
    r->tip = tip;   
    
    hash_rides[atoi(id)-1] = r;
    
    return true;
}

void getRideFields(int *id, char **date, char **driver, char **user, char **city, int *distance, 
                   double *score_user, double *score_driver, double *tip) {
  
  rides *r = NULL;
  
  r = hash_rides[*id];
  
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
    
    for(i=0;i<n_lines;i++){
    
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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// DRIVERS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Rides_driver{
    
    char *date;
    char *driver;
    double score_driver;
    char *nome;
    int numero_viagens;
    double score_total;

};

rides_driver **hash_rides_drivers;

void allocate_rides_drivers(){
    
    int i;
    
    hash_rides_drivers = (rides_driver**)malloc(n_lines_drivers*sizeof(rides_driver*));
        
    for(i=0; i < n_lines_drivers; i++){
        
        hash_rides_drivers[i]=NULL;
    }
}

void sortQ2(){
    
    int i;
    
    for (i=0; i < n_lines_drivers; i++){
    
         if(hash_rides_drivers[i]==NULL){
    
            rides_driver *rd = malloc(sizeof(rides_driver));
    
            rd->score_driver = 0;
            rd->date = "01/01/1000";
            rd->driver = "1000000";

            hash_rides_drivers[i] = rd;
         }
    }

    qsort(hash_rides_drivers, n_lines_drivers, sizeof(rides_driver*), compareDrivers);
}


bool insert_hash_rides_drivers(char *data,char *driver,double score_driver){
    
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, 
         *car_class_driver = NULL, *city_driver = NULL, *account_creation_driver = NULL, 
         *account_status_driver = NULL; 

    int linha_hash = atoi(driver)-1;

    if (hash_rides_drivers[linha_hash] == NULL){

        getDriverFields(&driver, &name_driver, &birth_day_driver, &gender_driver, 
                        &car_class_driver, &city_driver, &account_creation_driver, 
                        &account_status_driver); 

        if(name_driver==NULL || !strcmp(account_status_driver,"inactive")) return true;

        rides_driver *rd = malloc(sizeof(rides_driver));
        
        rd->date = data;
        rd->driver = driver;
        rd->score_driver = score_driver;
        rd->numero_viagens = 1;
        rd->score_total = score_driver;
        rd->nome = name_driver;

        hash_rides_drivers[linha_hash] = rd;
        
        return true;
    }

    if((calculateData(data,hash_rides_drivers[linha_hash]->date)==0)){ 
          
        hash_rides_drivers[linha_hash]->date = data;
    }   

    hash_rides_drivers[linha_hash]->score_total += score_driver;
    hash_rides_drivers[linha_hash]->numero_viagens ++;
    hash_rides_drivers[linha_hash]->score_driver = hash_rides_drivers[linha_hash]->score_total/hash_rides_drivers[linha_hash]->numero_viagens;

    return true;
        
}

void getRideDriverFields(int *id,char **date, char **driver, double *score_driver, char **nome, 
                         int *numero_viagens, double *score_total) {
  
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
    } else if (calculateData((*rd1)->date, (*rd2)->date) == 0) {
        return 1;
    } else if (calculateData((*rd2)->date, (*rd1)->date) == 0) {
        return -1;
    } else if (atoi((*rd1)->driver) < atoi((*rd2)->driver)){
        return 1;
    } else return -1;
  
}


void free_hash_rides_drivers(){
    
    int i;
    
    for(i=0;i<n_lines_drivers;i++){
    
        free(hash_rides_drivers[i]);
    }
    
    free(hash_rides_drivers);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// USERS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Rides_user{
    
    int distancia;
    char *date;
    char *username;
    char *nome;

};

rides_user **hash_rides_users;

void allocate_rides_users(){
    
    int i;

    hash_rides_users = (rides_user**)malloc(n_lines_users*sizeof(rides_user*));

    for(i=0; i < n_lines_users; i++){

        hash_rides_users[i]=NULL;
    }
}

void sortQ3(){
    
    int i;
    
    for (i=0;i < n_lines_users;i++){
         
         if(hash_rides_users[i]==NULL){
            
            rides_user *ru = malloc(sizeof(rides_user));
            ru->distancia = 0;
            ru->date = "01/01/1000";
            ru->username = "null";
            ru->nome = "null";

            hash_rides_users[i] = ru;
         
         }
    
    }

    qsort(hash_rides_users, n_lines_users, sizeof(rides_user*), compareUsers);
}

bool insert_hash_rides_users(int distance,char *date,char *user){
    
    int i, line_hash=0;
    
    int aux = hash_users(user);

    char *name_user = NULL, *gender_user = NULL, *birth_day_user = NULL, 
         *account_creation_user = NULL, *account_status_user = NULL;

    getUserFields(&user, &name_user, &gender_user, &birth_day_user, 
                  &account_creation_user, &account_status_user);

    if(name_user==NULL || strcmp(account_status_user,"inactive")==0) return true;

    for (i=0; i < n_lines_users; i++){

        line_hash = (i + aux) % n_lines_users;

        if (hash_rides_users[line_hash] == NULL){
            
            rides_user *ru = malloc(sizeof(rides_user));
            ru->distancia = distance;
            ru->date = date;
            ru->username = user;
            ru->nome = name_user;

            hash_rides_users[line_hash] = ru;
            
            return true;
        }
        
        if(strcmp(hash_rides_users[line_hash]->username,user)==0) {

            if((calculateData(date,hash_rides_users[line_hash]->date)==0)){
             
                 hash_rides_users[line_hash]->date = date;
            }

            hash_rides_users[line_hash]->distancia += distance;

            return true;
        }
    
    }
    
    return false;
}

void getRideUserFields(int *ind, int *distance, char **date, char **username, char **name) {
  
  rides_user *ru = NULL;
  
  ru =  hash_rides_users[*ind];
  
  if(ru==NULL){
  
      *date=NULL;
      return;
  }

  *distance = ru->distancia;
  *date = ru->date;
  *username = ru->username;
  *name = ru->nome;

}

int compareUsers(const void *elem1, const void *elem2){
    
    rides_user **ru1 = (rides_user**)elem1;
    rides_user **ru2 = (rides_user**)elem2;               

    if((*ru1)->distancia > (*ru2)->distancia) {
        return 1;
    } else if ((*ru1)->distancia < (*ru2)->distancia) {
        return -1;
    } else if (calculateData((*ru1)->date, (*ru2)->date) == 0) {
        return 1;
    } else if (calculateData((*ru2)->date, (*ru1)->date) == 0) {
        return -1;
    } else if (strcmp((*ru2)->username, (*ru1)->username)<0){
        return -1;
    } else return 1;
  
}


void free_hash_rides_users(){
    
    int i;
    
    for(i=0;i<n_lines_users;i++){
    
        free(hash_rides_users[i]);
    }
    
    free(hash_rides_users);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// DRIVERS CITY  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Rides_driver_city{
    
    double average_score;
    char *id;
    int trip_counter;
    char *name;
    double total_score;

};

rides_driver_city **hash_rides_drivers_city;

void allocate_rides_drivers_city(){
    
    int i;

    hash_rides_drivers_city = (rides_driver_city**)malloc(n_lines_drivers*sizeof(rides_driver_city*));

    for(i=0; i < n_lines_drivers; i++){

        hash_rides_drivers_city[i]=NULL;
    }
}


void sortQ7(){
    
    int i;
    
    for (i=0;i < n_lines_drivers;i++){
    
        if(hash_rides_drivers_city[i]==NULL){
    
            rides_driver_city *rdc = malloc(sizeof(rides_driver_city));
            rdc->average_score = 0.000;
            rdc->id = "0";
            rdc->trip_counter = 0;
            rdc->name = "null";
            rdc->total_score = 0.000;

    
            hash_rides_drivers_city[i] = rdc;
        }
    
    }

    qsort(hash_rides_drivers_city, n_lines_drivers, sizeof(rides_driver_city*), compareCity);
}

bool insert_hash_rides_drivers_city(char* city){
    
    int i;
    int id_driver = 0;
    
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, 
         *car_class_driver = NULL, *city_driver = NULL, *account_creation_driver = NULL, 
         *account_status_driver = NULL;

    for(i=0; i < n_lines; i++){
        
        if(hash_rides[i]!=NULL){

            getDriverFields(&hash_rides[i]->driver, &name_driver, &birth_day_driver, 
                            &gender_driver, &car_class_driver, &city_driver, 
                            &account_creation_driver, &account_status_driver);

            if(name_driver!=NULL){
 
                id_driver = atoi(hash_rides[i]->driver)-1;

                if(strcmp(account_status_driver,"active")==0 && strcmp(hash_rides[i]->city,city)==0){

                    if(hash_rides_drivers_city[id_driver]==NULL){

                        rides_driver_city *rdc = malloc(sizeof(rides_driver_city));
                        
                        rdc->trip_counter = 1;
                        rdc->id = hash_rides[i]->driver;
                        rdc->average_score = hash_rides[i]->score_driver;
                        rdc->name = name_driver;
                        rdc->total_score = hash_rides[i]->score_driver;
                        
                        hash_rides_drivers_city[id_driver]=rdc;
                    }

                    else {
                        
                        hash_rides_drivers_city[id_driver]->trip_counter++;
                        hash_rides_drivers_city[id_driver]->total_score += hash_rides[i]->score_driver;
                        hash_rides_drivers_city[id_driver]->average_score = hash_rides_drivers_city[id_driver]->total_score/hash_rides_drivers_city[id_driver]->trip_counter;
                    }
                }
            }
        }
    }
    return true;
}

void getRideDriverCityFields(int *ind, double *average_score, char **id, int *trip_counter, 
                             char **name, double *total_score) {
  
  rides_driver_city *rdc = NULL;
  
  rdc =  hash_rides_drivers_city[*ind];
  
  if(rdc==NULL){
      
      *id=NULL;
      return;
  }

  *average_score = rdc->average_score;
  *id = rdc->id;
  *trip_counter = rdc->trip_counter;
  *name = rdc->name;
  *total_score = rdc->total_score;

}

int compareCity(const void *elem1, const void *elem2){
    
    rides_driver_city **rdc1 = (rides_driver_city**)elem1;
    rides_driver_city **rdc2 = (rides_driver_city**)elem2;               

    if((*rdc1)->average_score > (*rdc2)->average_score) {
        return 1;
    } else if ((*rdc1)->average_score < (*rdc2)->average_score) {
        return -1;
    } else if (atoi((*rdc1)->id) > atoi((*rdc2)->id)) {
        return 1;
    } else return -1;

}

void free_hash_rides_driver_city(){
    
    int i;
    
    for(i=0; i < n_lines_drivers; i++){
    
        if(hash_rides_drivers_city[i]!=NULL){
    
            free(hash_rides_drivers_city[i]);
            
            hash_rides_drivers_city[i]=NULL;
        }
    }

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// RIDES_GENDER /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

void allocate_rides_drivers_gender(){
    
    int i;

    hash_rides_gender = (rides_gender**)malloc(n_lines_gender*sizeof(rides_gender*));

    for(i=0; i < n_lines_gender; i++){
        
        hash_rides_gender[i]=NULL;
    }
}

void init_hash_rides_gender(int aux){

    int i;

    for(i=aux; i <n_lines_gender; i++){
       
        hash_rides_gender[i]=NULL;
    } 
}

bool insert_hash_rides_gender(char genero,int idade){
    int i, j, cont=0;
    
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, *car_class_driver = NULL, 
         *city_driver = NULL, *account_creation_driver = NULL, *account_status_driver = NULL;
    
    char *name_user = NULL, *gender_user = NULL, *birth_day_user = NULL, 
         *account_creation_user = NULL, *account_status_user = NULL;
    
    for(i=0;i<n_lines;i++){
        if(hash_rides[i]!=NULL){

            getDriverFields(&hash_rides[i]->driver, &name_driver, &birth_day_driver, &gender_driver, &car_class_driver, &city_driver, &account_creation_driver, &account_status_driver);
            getUserFields(&hash_rides[i]->user, &name_user, &gender_user, &birth_day_user, &account_creation_user, &account_status_user);

            if(name_driver!=NULL && name_user!=NULL){
                
                if(strcmp(account_status_user,"active")==0 && strcmp(account_status_driver,"active")==0 && gender_driver[0]==genero && gender_user[0]==genero && calculateAge(account_creation_user)>=idade && calculateAge(account_creation_driver)>=idade){
                    
                    cont++;
                    
                    if(cont>=n_lines_gender-1) {
                        n_lines_gender = n_lines_gender*5;
                        hash_rides_gender = realloc(hash_rides_gender,n_lines_gender*sizeof(rides_gender*));
                        init_hash_rides_gender(cont-1);
                    }

                    for(j=0;j<n_lines_gender;j++){
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

rides_gender *search_rides_gender(){
    
    int i, aux;
    
    char* date_actual_user = "00/00/2222";
    char* date_actual_driver = "00/00/2222";
    
    int date_regist_user, date_regist_driver;
    
    int end = 0, id_actual = 99999999;
    
    for(i=0; i < n_lines_gender; i++){

        if(hash_rides_gender[i]!=NULL){

            date_regist_user = calculateData(hash_rides_gender[i]->data_user,date_actual_user);
            date_regist_driver = calculateData(hash_rides_gender[i]->data_driver,date_actual_driver);
        
            if (hash_rides_gender[i]->isValid==1 && (date_regist_driver==1 || (date_regist_driver==-1 
                && date_regist_user==1) || (date_regist_driver==-1 && date_regist_user==-1 
                && atoi(hash_rides_gender[i]->id_viagem)<id_actual))){
                
                end=1;
                
                date_actual_user = hash_rides_gender[i]->data_user;
                date_actual_driver = hash_rides_gender[i]->data_driver;
                id_actual = atoi(hash_rides_gender[i]->id_viagem);
                
                aux=i;
            }
        }
    }

    if(end==0) return NULL;

    hash_rides_gender[aux]->isValid=0;
    
    return hash_rides_gender[aux];
}

void getRideGenderFields(char **driver_id, char **name_driver, char **username, 
                         char **nome_user, char **date_driver, char **date_user, 
                         char **id_trip, int *isValid) {
  
  rides_gender *rg = NULL;
  
  rg = search_rides_gender();
  
  if(rg==NULL){
      
      *driver_id=NULL;
      return;
  }

  *driver_id = rg->id_condutor;
  *name_driver = rg->nome_condutor;
  *username = rg->username_utilizador;
  *nome_user = rg->nome_utilizador;
  *date_driver = rg->data_driver;
  *date_user = rg->data_user;
  *id_trip = rg->id_viagem;
  *isValid = rg->isValid;
}


void free_hash_rides_gender(){
    
    int i;
    
    for(i=0;i<n_lines_gender;i++){
    
        if(hash_rides_gender[i]!=NULL){
    
            free(hash_rides_gender[i]);
            hash_rides_gender[i]=NULL;
        }
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// RIDES_DATE /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Rides_date{
    
    int distance;
    char *date;
    char *id;
    char *city;
    double tip;
    char *id_trip;
    int isValid;

};

rides_date **hash_rides_date;

void allocate_rides_date(){
    
    int i;
    
    hash_rides_date = (rides_date**)malloc(n_lines_users*sizeof(rides_date*));

    for(i=0; i < n_lines_drivers; i++){
        
        hash_rides_date[i]=NULL;
    }
}

bool insert_hash_rides_date(char *date1,char *date2){
    
    int i,j;
    
    for(i=0; i < n_lines; i++){

        if(hash_rides[i]!=NULL && (hash_rides[i]->tip != 0.0) && 
          calculateData(hash_rides[i]->date,date1)<=0 && 
          calculateData(date2,hash_rides[i]->date)<=0){

            for(j=0; j < n_lines_drivers; j++){
                
                if(hash_rides_date[j]==NULL) break;
            }

            rides_date *rd = malloc(sizeof(rides_date));
                
            rd->distance = hash_rides[i]->distance;
            rd->date = hash_rides[i]->date;
            rd->id = hash_rides[i]->id;
            rd->city = hash_rides[i]->city;
            rd->tip = hash_rides[i]->tip;
            rd->id_trip = hash_rides[i]->id;
            rd->isValid = 1;

            hash_rides_date[j]=rd;
        }
    }
    
    return true;
}

rides_date *search_rides_date(){
    
    int i, aux;
    
    char* recent_date = "00/00/0000";
    int dist = 0, end = 0, id_actual = 0;

    for(i=0; i < n_lines_drivers; i++){

        if(hash_rides_date[i]!=NULL && hash_rides_date[i]->isValid==1 && 
          (dist<hash_rides_date[i]->distance || 
          (dist==hash_rides_date[i]->distance && calculateData(hash_rides_date[i]->date,recent_date)<=0) || 
          (dist==hash_rides_date[i]->distance && calculateData(hash_rides_date[i]->date,recent_date)==-1 && atoi(hash_rides_date[i]->id_trip)>id_actual))){
                
                end = 1;
                
                dist = hash_rides_date[i]->distance;
                recent_date = hash_rides_date[i]->date;
                id_actual = atoi(hash_rides_date[i]->id_trip);
                
                aux = i;
        }
    }
 
    if(end==0) return NULL;

    hash_rides_date[aux]->isValid=0;
    
    return hash_rides_date[aux];
}

void getRideDateFields(int *distance, char **date, char **id, char **city, double *tip, 
                       char **id_trip, int *isValid) {
  
  rides_date *rd = NULL;
  
  rd = search_rides_date();
  
  if(rd==NULL){
      
      *date=NULL;
      return;
  }

  *distance = rd->distance;
  *date = rd->date;
  *id = rd->id;
  *city = rd->city;
  *tip = rd->tip;
  *id_trip = rd->id_trip;
  *isValid = rd->isValid;
}

void free_hash_rides_date(){
    
    int i;
    
    for(i=0;i<n_lines_drivers;i++){
    
        free(hash_rides_date[i]);
    }
    
    free(hash_rides_date);
    free(hash_rides_drivers_city);
    free(hash_rides_gender);
}






