#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drivers_structure.h"
#include "rides_structure.h"
#include "parsing.h"
#include <stdint.h>
#include <stdbool.h>


struct Drivers{

    char *id;                // Driver's ID
    char *name;              // Driver's name
    char *birth_day;         // Driver's birth day
    char *gender;            // Driver's gender
    char *car_class;         // Driver's car class
    char *city;              // Driver's city
    char *account_creation;  // Date of account creation
    char *account_status;    // Account status

};
 


// Driver's hash table
//  The hashing key is the drivers id, because in the .csv file the id
// is incremented in order, which allow us to use it as the hashing key.
drivers **hash_table_drivers;



// This function allocates memory in the heap for the Driver's Hash Table
void allocate_drivers(){ 
    int i;
    
    // Alocating the nedded space in the heap 
    hash_table_drivers = (drivers**)malloc(n_lines_drivers*sizeof(drivers*));
    
    // Initializing the pointers in the hash table to NULL
    for(i=0;i<n_lines_drivers;i++){
        hash_table_drivers[i]=NULL;
    }

}



// Function that inserts the driver in the respective hash table spot.
bool insert_hash_drivers(char *id,char *name,char *birth_day,
                         char *gender,char *car_class,char *city,char *account_creation,
                         char *account_status){

    // Getting the data ready to be inserted
    drivers *d = malloc(sizeof(drivers));
    d->id = id;
    d->name = name;
    d->gender = gender;
    d->birth_day = birth_day;
    d->car_class = car_class;
    d->city=city;
    d->account_creation=account_creation;
    d->account_status = account_status;

    // Using the driver's id we're able to insert the driver in the respective place.
    hash_table_drivers[atoi(id)-1] = d;

    return true;
}



//  This function is used, in different files, to get the respective driver field.
//  We have to use this function because our driver struct is an opaque type, which means that the
// other files in the project don't recognize the defenition of the struct. Therefore we have
// to call this function so we're able to access the hash table content.
void getDriverFields(char **id, char **name, char **birth_day,
                     char **gender, char **car_class, char **city, char **account_creation,
                     char **account_status) {
  
  // Getting the respective driver
  drivers *d = NULL;
  d = hash_table_drivers[atoi(*id)-1];
  
  // Verifies if the ride is NULL
  if(d==NULL){
  
      *name=NULL;
      return;
  }
  
  // Updating the function arguments if r is not NULL
  *name = d->name;
  *birth_day = d->birth_day;
  *gender = d->gender;
  *car_class = d->car_class;
  *city = d->city;
  *account_creation = d->account_creation;
  *account_status = d->account_status;

}



// This function frees the memory that was allocaded before.
void free_hash_drivers(){
    int i;
    
    for(i=0;i<n_lines_drivers;i++){
        
        if(hash_table_drivers[i]!=NULL){
            // Freeing the contents of a certain hash table spot
            free(hash_table_drivers[i]->account_creation);
            free(hash_table_drivers[i]->account_status);
            free(hash_table_drivers[i]->birth_day);
            free(hash_table_drivers[i]->car_class);
            free(hash_table_drivers[i]->city);
            free(hash_table_drivers[i]->gender);
            free(hash_table_drivers[i]->id);
            free(hash_table_drivers[i]->name);
        
        }
            // Freeing a certain hash table spot
            free(hash_table_drivers[i]);
    
    }
    // Freeing the entire hash table
    free(hash_table_drivers);
}