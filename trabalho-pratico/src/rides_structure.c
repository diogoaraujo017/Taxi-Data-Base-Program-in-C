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
    
    char *id;            // Ride ID
    char *date;          // Ride date
    char *driver;        // Driver ID
    char *user;          // Username of user
    char *city;          // City the ride took place
    int distance;        // Distance of the ride
    double score_user;   // Score given to the user by the driver
    double score_driver; // Score given to the driver to the user 
    double tip;          // Tip the user gave to the driver

};



//  Hash Table of the rides.
//  The hashing key is the ride id, because in the .csv file the id
// is incremented in order, which allow us to use it as the hashing key.
rides **hash_rides;



// This function allocates memory in the heap for the Rides Hash Table
void allocate_rides(){ 
    int i;

    // Alocating the nedded space in the heap 
    hash_rides = (rides**)malloc(n_lines*sizeof(rides*));
    
    // Initializing the pointers in the hash table to NULL
    for(i=0; i < n_lines; i++){
        hash_rides[i]=NULL;
    } 
}



// Function that inserts the rides in the respective hash table spot.
bool insert_hash_rides(char *id,char *date,char *driver_id,char *username,char *city,int distance,
                       double score_user,double score_driver,double tip){
    
    // Getting the data ready to be inserted
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
    
    // Using the ride id we're able to insert the ride in the respective place.
    hash_rides[atoi(id)-1] = r;
    
    return true;
}



//  This function is used, in different files, to get the respective ride field.
//  We have to use this function because our ride struct is an opaque type, which means that the
// other files in the project don't recognize the defenition of the struct. Therefore we have
// to call this function so we're able to access the hash table content.
void getRideFields(int *id, char **date, char **driver, char **user, char **city, int *distance, 
                   double *score_user, double *score_driver, double *tip) {
  
  // Getting the respective ride
  rides *r = NULL;
  r = hash_rides[*id];
  
  // Verifies if the ride is NULL
  if(r==NULL){
  
      *date=NULL;
      return;
  }
  
  // Updating the function arguments if r is not NULL
  *date = r->date;
  *driver = r->driver;
  *user = r->user;
  *city = r->city;
  *distance = r->distance;
  *score_user = r->score_user;
  *score_driver = r->score_driver;
  *tip = r->tip;
}



// This function frees the memory that was allocaded before.
void free_hash_rides(){
    int i;
    
    for(i=0;i<n_lines;i++){
    
        if(hash_rides[i]!=NULL){
            // Freeing the contents of a certain hash table spot
            free(hash_rides[i]->id);
            free(hash_rides[i]->date);
            free(hash_rides[i]->driver);
            free(hash_rides[i]->user);
            free(hash_rides[i]->city);
        }
            // Freeing a certain hash table spot
            free(hash_rides[i]);
    }
    
    // Freeing the entire hash table
    free(hash_rides);
}






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// DRIVERS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



struct Rides_driver{
    
    char *date;          // Date of the most recent ride executed by the driver
    char *driver;        // Driver ID 
    double score_driver; // Driver's score
    char *nome;          // Driver's name
    int numero_viagens;  // Number of trips by the driver
    double score_total;  // Average of the scores given by users

};



//  Hash Table of the rides driver.
//  The hashing key is the driver id, because in the .csv file the driver id
// is incremented in order, which allow us to use it as the hashing key.
rides_driver **hash_rides_drivers;



// This function allocates memory in the heap for the Rides Driver Hash Table
void allocate_rides_drivers(){
    int i;
    
    // Alocating the nedded space in the heap 
    hash_rides_drivers = (rides_driver**)malloc(n_lines_drivers*sizeof(rides_driver*));
        
    // Initializing the pointers int the hash table to NULL   
    for(i=0; i < n_lines_drivers; i++){
        hash_rides_drivers[i]=NULL;
    }
}



//  This function sorts the hash table using the qsort function present in
// the standard c library.
void sortQ2(){
    int i;
    
    //  Setting the NULL inner contents to a default value if the hash table 
    // pointer is set to NULL, so the qsort funtion doesn't display segmentation
    // fault. :)
    for (i=0; i < n_lines_drivers; i++){
    
         if(hash_rides_drivers[i]==NULL){
            
            // Getting the data ready to be inserted
            rides_driver *rd = malloc(sizeof(rides_driver));
            rd->score_driver = 0;
            rd->date = "01/01/1000";
            rd->driver = "1000000000000";
            rd->nome = "null";

            hash_rides_drivers[i] = rd;
         }
    }
    // Calling the 'qsort' function that uses the function 'compareDrivers' to compare two elements.
    qsort(hash_rides_drivers, n_lines_drivers, sizeof(rides_driver*), compareDrivers);
}



// This function inserts the rides_driver in the respective hash table spot.
bool insert_hash_rides_drivers(char *data,char *driver,double score_driver){
    
    // Creating the arguments that change when called in the get function.
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, 
         *car_class_driver = NULL, *city_driver = NULL, *account_creation_driver = NULL, 
         *account_status_driver = NULL; 

    // Calculating the hash table spot where the driver will be inserted.
    int linha_hash = atoi(driver)-1;

    // Checking if data from that driver was not previosly inserted.
    if (hash_rides_drivers[linha_hash] == NULL){
        
        // Getting the respective driver fields 
        getDriverFields(&driver, &name_driver, &birth_day_driver, &gender_driver, 
                        &car_class_driver, &city_driver, &account_creation_driver, 
                        &account_status_driver); 

        // Checking if the driver is NULL or inactive
        if(name_driver==NULL || !strcmp(account_status_driver,"inactive")) return true;

        // Getting the data ready to be inserted
        rides_driver *rd = malloc(sizeof(rides_driver));
        rd->date = data;
        rd->driver = driver;
        rd->score_driver = score_driver;
        rd->numero_viagens = 1;
        rd->score_total = score_driver;
        rd->nome = name_driver;

        // Inserting the data in the respective hash table spot.
        hash_rides_drivers[linha_hash] = rd;
        
        // Returning true so the rest of the code does not execute
        return true;
    }
    
    //  This code only executes if we are inserting a driver that already was inserted before
    // therfore we need to update the contents of the hash table.

    // Checks if the date that we want to insert is more recent than the date present in the hash table.
    if((calculateData(data,hash_rides_drivers[linha_hash]->date)==0)){ 
          hash_rides_drivers[linha_hash]->date = data;
    }   

    // Updating the rest of the contents in the hash table
    hash_rides_drivers[linha_hash]->score_total += score_driver;
    hash_rides_drivers[linha_hash]->numero_viagens ++;
    hash_rides_drivers[linha_hash]->score_driver = hash_rides_drivers[linha_hash]->score_total/hash_rides_drivers[linha_hash]->numero_viagens;

    return true;
}



//  This function is used, in different files, to get the respective ride driver field.
//  We have to use this function because our ride_driver struct is an opaque type, which means that the
// other files in the project don't recognize the defenition of the struct. Therefore we have
// to call this function so we're able to access the hash table content.
void getRideDriverFields(int *id,char **date, char **driver, double *score_driver, char **nome, 
                         int *numero_viagens, double *score_total) {
  
  // Getting the respective rides_driver
  rides_driver *rd = NULL;
  rd =  hash_rides_drivers[*id];
  
  // Verifies if the rides_driver is NULL
  if(strcmp(rd->nome,"null")==0 || rd==NULL){
  
      *date=NULL;
      return;
  }

  // Updating the contents of the arguments
  *date = rd->date;
  *driver = rd->driver;
  *score_driver = rd->score_driver;
  *nome = rd->nome;
  *numero_viagens = rd->numero_viagens;
  *score_total = rd->score_total;

}



//  This is the funtion that 'qsort' utilizes to sort the rides driver hash table.
//  This function utilizes some if statements to determin which hash table
// element should come before the other, therefore the 'qsort' function is able
// to sort the hash table.
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



// Function that frees the memory allocated by the rides_driver hash table.
void free_hash_rides_drivers(){
    int i;
    
    for(i=0;i<n_lines_drivers;i++){
        // Freeing a respective hash table element.
        free(hash_rides_drivers[i]);
    }
    // Freeing the entire hash table.
    free(hash_rides_drivers);
}






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// USERS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



struct Rides_user{
    
    int distance;   // Total distance covered by user 
    char *date;     // Date of the most recent ride
    char *username; // Username of the user
    char *nome;     // Name of the user

};



//  Hash Table of the rides user.
rides_user **hash_rides_users;



// This function allocates memory in the heap for the Rides User Hash Table
void allocate_rides_users(){
    int i;

    // Alocating the nedded space in the heap
    hash_rides_users = (rides_user**)malloc(n_lines_users*sizeof(rides_user*));
    
    // Initializing the pointers int the hash table to NULL 
    for(i=0; i < n_lines_users; i++){

        hash_rides_users[i]=NULL;
    }
}



//  This function sorts the hash table using the qsort function present in
// the standard c library.
void sortQ3(){
    int i;
    
    //  Setting the inner contents to a default value if the hash table 
    // pointer is set to NULL, so the qsort funtion doesn't display segmentation
    // fault. :)
    for (i=0;i < n_lines_users;i++){
         
         if(hash_rides_users[i]==NULL){
            
            rides_user *ru = malloc(sizeof(rides_user));
            ru->distance = 0;
            ru->date = "01/01/1000";
            ru->username = "null";
            ru->nome = "null";

            hash_rides_users[i] = ru;
         
         }
    
    }
    // Calling the 'qsort' function that uses the function 'compareUsers' to compare two elements.
    qsort(hash_rides_users, n_lines_users, sizeof(rides_user*), compareUsers);
}



// This function inserts the rides_user in the respective hash table spot.
bool insert_hash_rides_users(int distance,char *date,char *user){
    int i, line_hash=0;
    
    // Calculating the first hash table spot where the rides_user could be inserted.
    int aux = hash_users(user);
    
    // Creating the arguments that change when called in the get function.
    char *name_user = NULL, *gender_user = NULL, *birth_day_user = NULL, 
         *account_creation_user = NULL, *account_status_user = NULL;

    // Getting the respective user fields 
    getUserFields(&user, &name_user, &gender_user, &birth_day_user, 
                  &account_creation_user, &account_status_user);
    
    // Checking if the user is NULL or inactive
    if(name_user==NULL || strcmp(account_status_user,"inactive")==0) return true;

    //  For loop that checks every posible spot the the rides_user
    // could be inserted ultil it find a NULL hash table spot
    // or data from that same user and then updates it.
    for (i=0; i < n_lines_users; i++){

        line_hash = (i + aux) % n_lines_users;
        
        // Checking if data from that rides_user was not previosly inserted.
        if (hash_rides_users[line_hash] == NULL){
            
            // Getting the data ready to be inserted
            rides_user *ru = malloc(sizeof(rides_user));
            ru->distance = distance;
            ru->date = date;
            ru->username = user;
            ru->nome = name_user;
            
            // Inserting the data in the respective hash table spot.
            hash_rides_users[line_hash] = ru;
            
            // Returning true so the rest of the code does not execute
            return true;
        }
        
        if(strcmp(hash_rides_users[line_hash]->username,user)==0) {
            
            // Checks if the date that we want to insert is more recent than the date present in the hash table.
            if((calculateData(date,hash_rides_users[line_hash]->date)==0)){
                 hash_rides_users[line_hash]->date = date;
            }
            
            // Updating the rest of the contents in the hash table
            hash_rides_users[line_hash]->distance += distance;
            
            // Returning true so the rest of the code does not execute
            return true;
        }
    
    }
    
    // Returning false if it was not possible to inserte the rides_user
    return false;
}



//  This function is used, in different files, to get the respective rides_user field.
//  We have to use this function because our ride_user struct is an opaque type, which means that the
// other files in the project don't recognize the defenition of the struct. Therefore we have
// to call this function so we're able to access the hash table content.
void getRideUserFields(int *ind, int *distance, char **date, char **username, char **name) {
  
  // Getting the respective rides_user
  rides_user *ru = NULL;
  ru =  hash_rides_users[*ind];
  
  // Verifies if the rides_user is NULL
  if(strcmp(ru->nome,"null")==0 || ru==NULL){
  
      *date=NULL;
      return;
  }
 
  // Updating the contents of the arguments
  *distance = ru->distance;
  *date = ru->date;
  *username = ru->username;
  *name = ru->nome;

}



//  This is the funtion that 'qsort' utilizes to sort the rides user hash table.
//  This function utilizes some if statements to determin which hash table
// element should come before the other, therefore the 'qsort' function is able
// to sort the hash table.
int compareUsers(const void *elem1, const void *elem2){
    rides_user **ru1 = (rides_user**)elem1;
    rides_user **ru2 = (rides_user**)elem2;               

    if((*ru1)->distance > (*ru2)->distance) {
        return 1;
    } else if ((*ru1)->distance < (*ru2)->distance) {
        return -1;
    } else if (calculateData((*ru1)->date, (*ru2)->date) == 0) {
        return 1;
    } else if (calculateData((*ru2)->date, (*ru1)->date) == 0) {
        return -1;
    } else if (strcmp((*ru2)->username, (*ru1)->username)<0){
        return -1;
    } else return 1;
  
}



// Function that frees the memory allocated by the rides_user hash table.
void free_hash_rides_users(){
    int i;
    
    for(i=0;i<n_lines_users;i++){
        // Freeing a respective hash table element.
        free(hash_rides_users[i]);
    }
    // Freeing the entire hash table.
    free(hash_rides_users);
}






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// DRIVERS CITY  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



struct Rides_driver_city{
    
    double average_score;  // Average score given to the driver
    char *id;              // Driver's ID
    int trip_counter;      // Driver's trip counter
    char *name;            // Driver's name
    double total_score;    // Total score given to the driver

};



//  Hash Table of the rides driver city.
//  The hashing key is the driver id, because in the .csv file the driver id
// is incremented in order, which allow us to use it as the hashing key.
rides_driver_city **hash_rides_drivers_city;



// This function allocates memory in the heap for the Rides Driver City Hash Table
void allocate_rides_drivers_city(){
    int i;

    // Alocating the nedded space in the heap 
    hash_rides_drivers_city = (rides_driver_city**)malloc(n_lines_drivers*sizeof(rides_driver_city*));
    
    // Initializing the pointers int the hash table to NULL   
    for(i=0; i < n_lines_drivers; i++){
        hash_rides_drivers_city[i]=NULL;
    }
}



//  This function sorts the hash table using the qsort function present in
// the standard c library.
void sortQ7(){
    int i;
     
    //  Setting the NULL inner contents to a default value if the hash table 
    // pointer is set to NULL, so the qsort funtion doesn't display segmentation
    // fault. :) 
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
    
    // Calling the 'qsort' function that uses the function 'compareCity' to compare two elements.
    qsort(hash_rides_drivers_city, n_lines_drivers, sizeof(rides_driver_city*), compareCity);
}



//  This function inserts in the rides_driver_city hash table all
// the drivers trips information from operating in a given city.
bool insert_hash_rides_drivers_city(char* city){
    int i;
    int id_driver = 0;
    
    // Creating the arguments that change when called in the get function.
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, 
         *car_class_driver = NULL, *city_driver = NULL, *account_creation_driver = NULL, 
         *account_status_driver = NULL;
    
    //  For loop that iterrates throught the rides hash table 
    // checking if in a certain ride the driver belongs to the 
    // input city.
    for(i=0; i < n_lines; i++){
        
        // Checking if the ride is not NULL
        if(hash_rides[i]!=NULL){

            // Getting the respective driver fields 
            getDriverFields(&hash_rides[i]->driver, &name_driver, &birth_day_driver, 
                            &gender_driver, &car_class_driver, &city_driver, 
                            &account_creation_driver, &account_status_driver);
            
            // Checking if the driver is not NULL
            if(name_driver!=NULL){
                
                // Calculating the hash table key
                id_driver = atoi(hash_rides[i]->driver)-1;
                
                // Checking if the driver's account is active and if he belongs to the respective city.
                if(strcmp(account_status_driver,"active")==0 && strcmp(hash_rides[i]->city,city)==0){
                    
                    // Checking if data from that rides_driver_city was not previosly inserted.
                    if(hash_rides_drivers_city[id_driver]==NULL){
                        
                        // Getting the data ready to be inserted
                        rides_driver_city *rdc = malloc(sizeof(rides_driver_city));
                        rdc->trip_counter = 1;
                        rdc->id = hash_rides[i]->driver;
                        rdc->average_score = hash_rides[i]->score_driver;
                        rdc->name = name_driver;
                        rdc->total_score = hash_rides[i]->score_driver;
                        // Inserting the data in the respective hash table spot.
                        hash_rides_drivers_city[id_driver]=rdc;
                    }

                    else {
                        // Updating the rest of the contents in the hash table
                        hash_rides_drivers_city[id_driver]->trip_counter++;
                        hash_rides_drivers_city[id_driver]->total_score += hash_rides[i]->score_driver;
                        hash_rides_drivers_city[id_driver]->average_score = hash_rides_drivers_city[id_driver]->total_score/hash_rides_drivers_city[id_driver]->trip_counter;
                    }
                }
            }
        }
    }
    // Returning true after creating the hash table for the city passed as an argument.
    return true;
}



//  This function is used, in different files, to get the respective rides_driver_city field.
//  We have to use this function because our rides_driver_city struct is an opaque type, which means that the
// other files in the project don't recognize the defenition of the struct. Therefore we have
// to call this function so we're able to access the hash table content.
void getRideDriverCityFields(int *ind, double *average_score, char **id, int *trip_counter, 
                             char **name, double *total_score) {
  
  // Getting the respective rides_driver_city
  rides_driver_city *rdc = NULL;
  rdc =  hash_rides_drivers_city[*ind];
  
  // Verifies if the rides_driver_city is NULL
  if(strcmp(rdc->name,"null")==0 || rdc==NULL){
      
      *id=NULL;
      return;
  }

  // Updating the contents of the arguments
  *average_score = rdc->average_score;
  *id = rdc->id;
  *trip_counter = rdc->trip_counter;
  *name = rdc->name;
  *total_score = rdc->total_score;

}



//  This is the funtion that 'qsort' utilizes to sort the rides_driver_city hash table.
//  This function utilizes some if statements to determin which hash table
// element should come before the other, therefore the 'qsort' function is able
// to sort the hash table.
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



// Function that frees the memory allocated by the rides_user hash table.
void free_hash_rides_driver_city(){
    int i;
    
    for(i=0; i < n_lines_drivers; i++){
    
        if(hash_rides_drivers_city[i]!=NULL){
            // Freeing a respective hash table element.
            free(hash_rides_drivers_city[i]);
            // Setting the freed pointer back to NULL
            hash_rides_drivers_city[i]=NULL;
        }
    }
}






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// RIDES_GENDER /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



struct Rides_gender{
    
    char *id_driver;   // Driver's ID
    char *name_driver; // Driver's name
    char *username;    // User's username
    char *name_user;   // User's name
    char *date_driver; // Date that the driver created his account
    char *date_user;   // Date that the user created his account
    char *id_trip;     // Trip ID
    int isValid;       // Auxiliar value to sort the outputs

};



//  Hash Table of the rides gender.
rides_gender **hash_rides_gender;



// This function allocates memory in the heap for the Rides Gender Hash Table
void allocate_rides_drivers_gender(){
    int i;
    
    // Alocating the nedded space in the heap 
    hash_rides_gender = (rides_gender**)malloc(n_lines_gender*sizeof(rides_gender*));
    
    // Initializing the pointers int the hash table to NULL   
    for(i=0; i < n_lines_gender; i++){
        hash_rides_gender[i]=NULL;
    }
}



// This function sets all the pointers in the rides gender hash table to NULL 
void init_hash_rides_gender(int aux){
    int i;

    for(i=aux; i < n_lines_gender; i++){
       hash_rides_gender[i]=NULL;
    } 
}



//  This function inserts in the rides_driver_city hash table all
// the drivers trips information from operating in a given city.
bool insert_hash_rides_gender(char genero,int idade){
    int i, j, cont=0;
    
    // Creating the arguments that change when called in the get function.
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, *car_class_driver = NULL, 
         *city_driver = NULL, *account_creation_driver = NULL, *account_status_driver = NULL;
    
    // Creating the arguments that change when called in the get function.
    char *name_user = NULL, *gender_user = NULL, *birth_day_user = NULL, 
         *account_creation_user = NULL, *account_status_user = NULL;
    
    //  For loop that iterrates throught the rides hash table 
    // checking if in a certain ride the driver an the user
    // belongs to the inputed gender and are over the inputed age.
    for(i=0;i<n_lines;i++){
        
        // Checking if the ride is not NULL
        if(hash_rides[i]!=NULL){
            
             // Getting the respective driver fields 
            getDriverFields(&hash_rides[i]->driver, &name_driver, &birth_day_driver, 
                            &gender_driver, &car_class_driver, &city_driver, 
                            &account_creation_driver, &account_status_driver);
            
             // Getting the respective user fields 
            getUserFields(&hash_rides[i]->user, &name_user, &gender_user, &birth_day_user, 
                          &account_creation_user, &account_status_user);
            
            // Checking if the driver and the user are not NULL
            if(name_driver!=NULL && name_user!=NULL){
                
                //  Checking if the driver and user are active, if they are the gender passed as an
                // argument and if they are over the aged passed as an input.
                if(strcmp(account_status_user,"active")==0 && strcmp(account_status_driver,"active")==0 && gender_driver[0]==genero && gender_user[0]==genero && calculateAge(account_creation_user)>=idade && calculateAge(account_creation_driver)>=idade){
                    
                    cont++;
                    
                    // Checking if the program needs to allocate more memory for the hash table.
                    if(cont>=n_lines_gender-1) {
                        
                        n_lines_gender = n_lines_gender*5;
                        
                        // Allocating more memory for the hash table
                        hash_rides_gender = realloc(hash_rides_gender,n_lines_gender*sizeof(rides_gender*));
                        
                        // Setting the nearly created hash table spot to a not NULL value
                        init_hash_rides_gender(cont-1);
                    }
                    
                    // Finding a place in the hash table to store the information
                    for(j=0;j<n_lines_gender;j++){
                        if(hash_rides_gender[j]==NULL) break;
                    }
                    
                    // Getting the data ready to be inserted
                    rides_gender *rg = malloc(sizeof(rides_gender));
                    rg->id_driver = hash_rides[i]->driver;
                    rg->name_driver = name_driver;
                    rg->username = hash_rides[i]->user;
                    rg->name_user = name_user;
                    rg->date_driver = account_creation_driver;
                    rg->date_user = account_creation_user;
                    rg->isValid = 1;
                    rg->id_trip = hash_rides[i]->id;
                    
                    // Inserting the data in the respective hash table spot.
                    hash_rides_gender[j]=rg;
                }
            }
        }
    }
    // Returning true when the hash table has been created.
    return true;
}



//  This function when called searches for the next rides_gender to be printed
// and switches the isValid parameter to 0 so the next time this function is
// called, the function knows that that hash table element was already been 
// outputed.
rides_gender *search_rides_gender(){
    int i, aux;
    char* date_actual_user = "00/00/2222";
    char* date_actual_driver = "00/00/2222";
    int date_regist_user, date_regist_driver;
    int end = 0, id_actual = 99999999;
    
    // For loop that iterates throught the rides gender hash table.
    for(i=0; i < n_lines_gender; i++){

        // Verifying if the element is not NULL
        if(hash_rides_gender[i]!=NULL){
            
            // Calculating the parameter to verify if this element is the next being outputed.
            date_regist_user = calculateData(hash_rides_gender[i]->date_user,date_actual_user);
            date_regist_driver = calculateData(hash_rides_gender[i]->date_driver,date_actual_driver);
            
            //  Verifying if the current hash table element is gonna be printed first
            // that the current stored element in the variables. 
            if (hash_rides_gender[i]->isValid==1 && (date_regist_driver==1 || (date_regist_driver==-1 
                && date_regist_user==1) || (date_regist_driver==-1 && date_regist_user==-1 
                && atoi(hash_rides_gender[i]->id_trip)<id_actual))){
                
                //  Updating the contents of the variables that make it possible
                // to verify if the next rides_gender is gonna be printed first
                // than the rides_gender that is being stored.
                end=1;
                date_actual_user = hash_rides_gender[i]->date_user;
                date_actual_driver = hash_rides_gender[i]->date_driver;
                id_actual = atoi(hash_rides_gender[i]->id_trip);
                aux=i;
            }
        }
    }

    if(end==0) return NULL;
    
    // Setting the isValid parameter to 0
    hash_rides_gender[aux]->isValid=0;
    
    // Returning the next rides_gender to be outputed
    return hash_rides_gender[aux];
}



//  This function is used, in different files, to get the respective rides_gender field.
//  We have to use this function because our rides_gender struct is an opaque type, which means that the
// other files in the project don't recognize the defenition of the struct. Therefore we have
// to call this function so we're able to access the hash table content.
void getRideGenderFields(char **driver_id, char **name_driver, char **username, 
                         char **name_user, char **date_driver, char **date_user, 
                         char **id_trip, int *isValid) {
  
  // Getting the respective rides_gender
  rides_gender *rg = NULL;
  rg = search_rides_gender();
  
  // Verifies if the rides_gender is NULL
  if(rg==NULL){
      
      *driver_id = NULL;
      return;
  }
   
  // Updating the contents of the arguments 
  *driver_id = rg->id_driver;
  *name_driver = rg->name_driver;
  *username = rg->username;
  *name_user = rg->name_user;
  *date_driver = rg->date_driver;
  *date_user = rg->date_user;
  *id_trip = rg->id_trip;
  *isValid = rg->isValid;
}



// Function that frees the memory allocated by the rides_user hash table.
void free_hash_rides_gender(){
    int i;
    
    for(i=0;i<n_lines_gender;i++){
    
        if(hash_rides_gender[i]!=NULL){
            // Freeing a respective hash table element.
            free(hash_rides_gender[i]);
            // Setting the freed pointer back to NULL
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



//  Hash Table of the rides date.
rides_date **hash_rides_date;



// This function allocates memory in the heap for the Rides Date Hash Table
void allocate_rides_date(){
    int i;
    
    // Alocating the nedded space in the heap 
    hash_rides_date = (rides_date**)malloc(n_lines_users*sizeof(rides_date*));

    // Initializing the pointers int the hash table to NULL 
    for(i=0; i < n_lines_drivers; i++){
        hash_rides_date[i]=NULL;
    }
}



//  This function inserts in the rides_date hash table all
// the information about the trips that happened between two 
// dates and if the user tipped the driver.
bool insert_hash_rides_date(char *date1,char *date2){
    int i,j;
    
    // For loop that iterrates throught the rides hash table.
    for(i=0; i < n_lines; i++){

        // Verifing if the ride is between the two dates and if the user tipped.
        if(hash_rides[i]!=NULL && (hash_rides[i]->tip != 0.0) && 
          calculateData(hash_rides[i]->date,date1)<=0 && 
          calculateData(date2,hash_rides[i]->date)<=0){

            // Finding a spot to insert the rides_date
            for(j=0; j < n_lines_drivers; j++){
                if(hash_rides_date[j]==NULL) break;
            }
            
            // Getting the data ready to be inserted
            rides_date *rd = malloc(sizeof(rides_date));
            rd->distance = hash_rides[i]->distance;
            rd->date = hash_rides[i]->date;
            rd->id = hash_rides[i]->id;
            rd->city = hash_rides[i]->city;
            rd->tip = hash_rides[i]->tip;
            rd->id_trip = hash_rides[i]->id;
            rd->isValid = 1;
            
            // Inserting the data in the respective hash table spot.
            hash_rides_date[j]=rd;
        }
    }
    // Returning true when the hash table has been created.
    return true;
}



//  This function when called searches for the next rides_date to be printed
// and switches the isValid parameter to 0 so the next time this function is
// called, the function knows that that hash table element was already been
// outputed.
rides_date *search_rides_date(){
    int i, aux;
    char* recent_date = "00/00/0000";
    int dist = 0, end = 0, id_actual = 0;

    // For loop that iterates throught the rides date hash table.
    for(i=0; i < n_lines_drivers; i++){
        
        //  Verifying if the rides_date is not NULL, and if the current hash table element
        // is gonna be printed first that the current stored element in the variables. 
        if(hash_rides_date[i]!=NULL && hash_rides_date[i]->isValid==1 && 
          (dist<hash_rides_date[i]->distance || 
          (dist==hash_rides_date[i]->distance && calculateData(hash_rides_date[i]->date,recent_date)<=0) || 
          (dist==hash_rides_date[i]->distance && calculateData(hash_rides_date[i]->date,recent_date)==-1 && atoi(hash_rides_date[i]->id_trip)>id_actual))){
                
                //  Updating the contents of the variables that make it possible
                // to verify if the next rides_date is gonna be printed first
                // than the rides_date that is being stored.
                end = 1;
                dist = hash_rides_date[i]->distance;
                recent_date = hash_rides_date[i]->date;
                id_actual = atoi(hash_rides_date[i]->id_trip);
                aux = i;
        }
    }
 
    if(end==0) return NULL;
    
    // Setting the isValid parameter to 0
    hash_rides_date[aux]->isValid=0;
    
    // Returning the next rides_date to be outputed
    return hash_rides_date[aux];
}



//  This function is used, in different files, to get the respective rides_date field.
//  We have to use this function because our rides_date struct is an opaque type, which means that the
// other files in the project don't recognize the defenition of the struct. Therefore we have
// to call this function so we're able to access the hash table content.
void getRideDateFields(int *distance, char **date, char **id, char **city, double *tip, 
                       char **id_trip, int *isValid) {
  
  // Getting the respective rides_date
  rides_date *rd = NULL;
  rd = search_rides_date();
  
  // Verifies if the rides_date is NULL
  if(rd==NULL){
      
      *date=NULL;
      return;
  }

  // Updating the contents of the arguments 
  *distance = rd->distance;
  *date = rd->date;
  *id = rd->id;
  *city = rd->city;
  *tip = rd->tip;
  *id_trip = rd->id_trip;
  *isValid = rd->isValid;
}



//  Function that frees the memory allocated by the rides_user hash table.
//  This function also frees the entirity of the rides_drivers_city 
// and rides_gender hash tables because the free functions of these hash table
// are called before the end of the program, because they will be used again,
// with makes it impossible to free the entirity of thoose hash tables in their
// respective free function.
void free_hash_rides_date(){
    
    int i;
    
    for(i=0;i<n_lines_drivers;i++){
        // Freeing a respective hash table element.
        free(hash_rides_date[i]);
    }
    // Freeing the entirity of these hash table
    free(hash_rides_date);
    free(hash_rides_drivers_city);
    free(hash_rides_gender);
}

