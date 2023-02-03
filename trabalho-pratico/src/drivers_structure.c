#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drivers_structure.h"
#include "rides_structure.h"
#include "parsing.h"
#include <stdint.h>
#include <stdbool.h>


struct Drivers{

    char *id;                // Id do condutor.
    char *name;              // Nome do condutor.
    char *birth_day;         // Data de nascimento do condutor.
    char *gender;            // Sexo do condutor.
    char *car_class;         // Classe do carro do condutor.
    char *city;              // Cidade de residencia do condutor.
    char *account_creation;  // Data de criação da conta do condutor.
    char *account_status;    // Status da conta do condutor.

};

// Hash table dos drivers
drivers **hash_table_drivers;

void allocate_drivers(){ 
    int i;
    
    hash_table_drivers = (drivers**)malloc(n_lines_drivers*sizeof(drivers*));
    
    for(i=0;i<n_lines_drivers;i++){
        hash_table_drivers[i]=NULL;
    }

}

// Esta função insere uma determinada linha na hash_table se essa linha não estiver ocupada.
// Uma linha está ocupada quando não está a NULL e vice-versa, daí a importância da função
// init_hash_table_drivers. Se a linha for adicionada com sucesso a função dará return a true,
// não dando qualquer problema, caso contrário dará return a false significando que a 
// função não conseguiu adicionar a linha.
bool insert_hash_drivers(char *id,char *name,char *birth_day,
                         char *gender,char *car_class,char *city,char *account_creation,
                         char *account_status){

    drivers *d = malloc(sizeof(drivers));
    
    d->id = id;
    d->name = name;
    d->gender = gender;
    d->birth_day = birth_day;
    d->car_class = car_class;
    d->city=city;
    d->account_creation=account_creation;
    d->account_status = account_status;

    hash_table_drivers[atoi(id)-1] = d;

    return true;

}

void getDriverFields(char **id, char **name, char **birth_day,
                     char **gender, char **car_class, char **city, char **account_creation,
                     char **account_status) {
  
  drivers *d = NULL;
  
  d = hash_table_drivers[atoi(*id)-1];
  
  if(d==NULL){
  
      *name=NULL;
      
      return;
  }

  *name = d->name;
  *birth_day = d->birth_day;
  *gender = d->gender;
  *car_class = d->car_class;
  *city = d->city;
  *account_creation = d->account_creation;
  *account_status = d->account_status;

}

void free_hash_drivers(){
    
    int i;
    
    for(i=0;i<n_lines_drivers;i++){
        
        if(hash_table_drivers[i]!=NULL){
        
            free(hash_table_drivers[i]->account_creation);
            free(hash_table_drivers[i]->account_status);
            free(hash_table_drivers[i]->birth_day);
            free(hash_table_drivers[i]->car_class);
            free(hash_table_drivers[i]->city);
            free(hash_table_drivers[i]->gender);
            free(hash_table_drivers[i]->id);
            free(hash_table_drivers[i]->name);
        
        }
        
            free(hash_table_drivers[i]);
    
    }
    
    free(hash_table_drivers);

}