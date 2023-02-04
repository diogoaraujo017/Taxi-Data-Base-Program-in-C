#include "drivers_structure.h"
#include "users_structure.h"
#include "rides_structure.h"
#include <stdio.h>
#include "parsing.h"
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "func_auxiliares.h"



//  Global variables to comunicate to the other files the 
// size of the hash tables.
int n_lines;
int n_lines_drivers; 
int n_lines_users; 
int n_lines_gender;



//  This function find out how many lines are int the data files
// and updates de global variables with the respective size.
int count_lines(char *drivers,char *users,char *rides){
    int d=0, u=0, r=0; 
    char line[250];
 
    FILE *file;

    // Counting the lines in the driver's file
    file = fopen(drivers, "r");
    if(file==NULL) return 1;
    while (fgets(line, 250, file)!=NULL){
            d++;
    }
    fclose(file);
    
    // Counting the lines in the user's file
    file = fopen(users, "r");
    if(file==NULL) return 1;  
    while (fgets(line, 250, file)!=NULL){
            u++;
    }
    fclose(file);
    
    // Counting the lines in the rides file
    file = fopen(rides, "r");
    if(file==NULL) return 1;  
    while (fgets(line, 250, file)!=NULL){
             r++;
    }
    fclose(file);
    
    // Updating the global variables
    n_lines=r*5;
    n_lines_drivers=d*5; 
    n_lines_users=u*5;
    n_lines_gender=r/1000;

    return 0;
}



// This function is responsible for parsing the data files and storing 
// the data in the hash table. It opens the respective data file, reads 
// every line of the file and analyzes it using the respective function.
void read_store(char *dir, char file_aux){
    
    FILE *file;
    char line[250];

    file = fopen(dir, "r");

    fgets(line, 250, file);
    
    // Reading every line in the driver's file
    if (file_aux == 'd'){
        while (fgets(line, 250, file)!=NULL){
            // Analyzing the current line
            analyze_line_drivers(line);
        }
    }
    // Reading every line in the user's file
    else if (file_aux == 'u'){
        while (fgets(line, 250, file)!=NULL){
            // Analyzing the current line
            analyze_line_users(line);
        }
    }
    // Reading every line in the rides file
    else if (file_aux == 'r'){
        while (fgets(line, 250, file)!=NULL){
            // Analyzing the current line
            analyze_line_rides(line);
        }
    }

    fclose(file);
}



// This function is responsible for handling a line from the driver's data file, that is, it has the role of
// read each driver parameter defined in the struct. This reading is easily performed due to
// the existence of the ';' that separate all the parameters. Then you need to enter
// all parameters relating to the driver (only from the driver's data file) in the hash table via
// from function insert_hash_drivers.
void analyze_line_drivers(char *line){
    
    char *id = NULL,*name = NULL,*birth_date = NULL,*gender = NULL,*car_class = NULL,
         *license_plate = NULL,*city = NULL,*acc_creation = NULL,*acc_status = NULL;
    int size_info = 35;
    
    // Allocating memory for the arguments.
    id=malloc(14);
    name=malloc(size_info);
    birth_date=malloc(12);
    gender=malloc(3);
    car_class=malloc(10);
    license_plate=malloc(10);
    city=malloc(12);
    acc_creation=malloc(12);
    acc_status=malloc(10);
    acc_status[0]='!';

    // Reading and dissecting the line
    sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", id,name,birth_date,gender,car_class,license_plate,city,acc_creation,acc_status);
    
    // Checking if the information is invalid
    if(acc_status[0]=='!' || check_data(birth_date) ==1 || check_data(acc_creation) ==1 || check_account(acc_status)==1 || check_class(car_class)==1){
        // Freeing the arguments if the line is invalid
        free(id);
        free(name);
        free(birth_date);
        free(gender);
        free(car_class);
        free(license_plate);
        free(city);
        free(acc_status);       
        
        return;
    }
    
    free(license_plate);

    //Function that inserts all driver parameters into the hash table
    insert_hash_drivers(id,name,birth_date,gender,convert(car_class),city,acc_creation,convert(acc_status));
}



// This function is responsible for handling a line from the users's data file, that is, it has the role of
// read each user parameter defined in the struct. This reading is easily performed due to
// the existence of the ';' that separate all the parameters. Then you need to enter
// all parameters relating to the user (only from the users's data file) in the hash table via
// from function insert_hash_user.
void analyze_line_users(char *line){
    
    char *username = NULL,*name = NULL,*gender = NULL,*birth_date = NULL,*acc_creation = NULL,
         *pay_method = NULL,*acc_status = NULL;
    int size_info = 35;
    
    // Allocating memory for the arguments.
    username=malloc(size_info);
    name=malloc(size_info);
    gender=malloc(3);
    birth_date=malloc(12);
    acc_creation=malloc(12);
    pay_method=malloc(12);
    acc_status=malloc(10);
    acc_status[0]='!';
    
    // Reading and dissecting the line
    sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", username,name,gender,birth_date,acc_creation,pay_method,acc_status);
    
    // Checking if the information is invalid
    if(acc_status[0]=='!' || check_data(birth_date) ==1 || check_account(acc_status)==1){
        // Freeing the arguments if the line is invalid
        free(username);
        free(name);
        free(gender);
        free(birth_date);
        free(acc_creation);
        free(pay_method);
        free(acc_status);
        
        return;
    }
    
    free(pay_method);

    //Function that inserts all user parameters into the hash table
    insert_hash_users(username,name,gender,birth_date,acc_creation,convert(acc_status));


}



//  This function is responsible for handling a line from the rides data file, that is, it has the role of
// read each rides parameter defined in the struct. This reading is easily performed due to
// the existence of the ';' that separate all the parameters. Then you need to enter
// all parameters relating to the ride (only from the rides data file) in the hash table via
// from function insert_hash_rides.
//  This function also inserts information on the rides_driver and rides_user hash table.
void analyze_line_rides(char *line){
    
    char *id = NULL,*date = NULL,*driver = NULL,*user = NULL,*city = NULL,*distance = NULL,
         *score_user = NULL,*score_driver = NULL,*tip = NULL,*ptr = NULL;
    int size_info = 35;
    
    // Allocating memory for the arguments.
    id=malloc(14);
    date=malloc(12);
    driver=malloc(14); 
    user=malloc(size_info);
    city=malloc(12);
    distance=malloc(6);
    score_user=malloc(6);
    score_driver=malloc(6);
    tip=malloc(6);
    tip[0]='!';
    
    // Reading and dissecting the line
    sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]", id,date,driver,user,city,distance,score_user,score_driver,tip);
    
    // Checking if the information is invalid
    if(tip[0]=='!' || check_data(date) ==1 || check_distance(distance)==1 || check_score(score_user)==1 || check_score(score_driver)==1|| check_tip(tip)==1){
        // Freeing the arguments if the line is invalid
        free(id);
        free(date);
        free(driver);
        free(user);
        free(city);
        free(distance);
        free(score_user);
        free(score_driver);
        free(tip);
        
        return;
    }
    
    // Creating arguments in the type the program needs 
    int distance_int = atoi(distance); 
    double score_user_double = atoi(score_user);
    double score_driver_double = atoi(score_driver);
    double tip_double = strtod(tip,&ptr);

    //Funções que inserem todos os parâmetros da ride nas hash tables 
    insert_hash_rides(id,date,driver,user,city,distance_int,score_user_double,score_driver_double,tip_double);
    insert_hash_rides_drivers(date,driver,score_driver_double);
    insert_hash_rides_users(distance_int,date,user);
    
    // Freeing the rest the arguments that are no longer needed
    free(distance);
    free(score_user);
    free(score_driver);
    free(tip);
}

