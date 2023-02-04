#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "users_structure.h"
#include "rides_structure.h"
#include "parsing.h"
#include <stdint.h>
#include <stdbool.h>



struct Users{
    
    char *username;          // User's username
    char *name;              // User's name
    char *gender;            // User's gender
    char *birth_day;         // User's birth day
    char *account_creation;  // Date of the account creation
    char *account_status;    // User's account status

};



// User's hash table
users **hash_table_users;



// This function allocates memory in the heap for the User's Hash Table
void allocate_users(){ 
    int i;
    
    // Alocating the nedded space in the heap 
    hash_table_users = (users**)malloc(n_lines_users*sizeof(users*));
    
    // Initializing the pointers in the hash table to NULL
    for(i = 0; i < n_lines_users; i++){
        hash_table_users[i]=NULL;
    }

}



//  This function calculates an user's hash table key, using the user's username,
// so we are able to store and search for a user.
unsigned int hash_users(char *username){
    unsigned int num_hash = 0;
    int i;
    
    //  For loop that calculates the key by iterating throught
    // the user's username caracthers.
    for (i = 0; username[i]!='\0'; i++){ 
        num_hash += username[i];
        num_hash = (num_hash * username[i]) % n_lines_users;
    }
    // Returning the key
    return num_hash;
}



// Function that inserts the rides in an hash table spot.
bool insert_hash_users(char *username,char *name,char *gender,char *birth_day,
                       char *account_creation,char *account_status){
    
    int i,next_position;
    
    // Getting the data ready to be inserted
    users *u = malloc(sizeof(users));
    u->username = username;
    u->name = name;
    u->gender = gender;
    u->birth_day = birth_day;
    u->account_creation = account_creation;
    u->account_status = account_status;
    
    // Calculating the first possible hahs table spot
    int aux = hash_users(username);
    
    // For loop that searches for a spot to store the user
    for (i = 0;i < n_lines_users; i++){
        
        // Calculating the next possible hash table spot.
        next_position = (i + aux) % n_lines_users;
    
        // Checking if the user is able to be stored
        if ((hash_table_users[next_position] == NULL)){
            hash_table_users[next_position] = u;
            return true;
        }
    }
    // Return false if it was impossible to store the user
    return false;
}



// This function searches for a certain user in the hash table
users *search_hash_users(char *username){
    int i, next_position;
    
    // Calculating the first possible spot
    int aux = hash_users(username);
    
    // For loop that searches for a spot the user is stored in
    for (i = 0; i < n_lines_users; i++){
    
        // Calculating the next possible hash table spot.
        next_position = (i + aux) % n_lines_users;
    
        // Verifying if the user is stored in that spot
        if (hash_table_users[next_position]!=NULL && strcmp(hash_table_users[next_position]->username, username)==0){
            // Returning the user information
            return hash_table_users[next_position];
        }
    
    }
    // Returning NULL if the user was not found
    return NULL;
}



//  This function is used, in different files, to get the respective user field.
//  We have to use this function because our user struct is an opaque type, which means that the
// other files in the project don't recognize the defenition of the struct. Therefore we have
// to call this function so we're able to access the hash table content.
void getUserFields(char **username, char **name, char **gender, char **birth_day,
                   char **account_creation, char **account_status){
  
  // Getting the respective user
  users *u = NULL;
  u = search_hash_users(*username);
  
  // Verifies if the user is NULL
  if(u==NULL){
      
      *name=NULL;
      return;
  }
  
  // Updating the function arguments if r is not NULL
  *name = u->name;
  *gender = u->gender;
  *birth_day = u->birth_day;
  *account_creation = u->account_creation;
  *account_status = u->account_status;
}



// This function frees the memory that was allocaded before.
void free_hash_users(){
    int i;
    
    for(i=0;i<n_lines_users;i++){
    
        if(hash_table_users[i]!=NULL){
            // Freeing the contents of a certain hash table spot
            free(hash_table_users[i]->account_creation);
            free(hash_table_users[i]->account_status);
            free(hash_table_users[i]->birth_day);
            free(hash_table_users[i]->gender);
            free(hash_table_users[i]->name);
            free(hash_table_users[i]->username);
    
        }
            // Freeing a certain hash table spot        
            free(hash_table_users[i]);
    }
    // Freeing the entire hash table
    free(hash_table_users);
}