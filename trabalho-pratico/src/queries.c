#include <stdio.h>
#include <string.h>
#include "queries.h"
#include "drivers_structure.h"
#include "rides_structure.h"
#include "users_structure.h"
#include <parsing.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "func_auxiliares.h"




// Function responsible for executing query 1.
void query1(char *line,char *file){ 

    int i, trip_counter = 0;
    double carType[2] = {0.0, 0.0};
    double average_score = 0.000, total_payed = 0.000, total_spent = 0.000;
    
    // Creating the arguments that change when called in the get function.
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, 
         *car_class_driver = NULL, *city_driver = NULL, *account_creation_driver = NULL, 
         *account_status_driver = NULL;
    
    char *name_user = NULL, *gender_user = NULL, *birth_day_user = NULL, 
         *account_creation_user = NULL, *account_status_user = NULL;
    
    char *date_ride = NULL, *driver_ride = NULL, *user_ride = NULL, *city_ride = NULL; 
    int distance_ride = 0; 
    double score_user_ride = 0.000, score_driver_ride = 0.000, tip_ride = 0.000;

    
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Opening the output file, so the query is able to write the output
    
    // Checking if the input is a driver's id, else is an user's username
    if(line[0]=='0') {                                        

        // Getting the respective driver fields             
        getDriverFields(&line, &name_driver, &birth_day_driver, &gender_driver, 
                        &car_class_driver, &city_driver, &account_creation_driver, 
                        &account_status_driver); 
        
        // Checking if the driver is not NULL and has an active account.
        if(name_driver!=NULL && (strcmp((account_status_driver),"active")==0)){  
            
            // Calculating the driver's payment arguments by using is car class.
            if (strcmp(car_class_driver,"basic")==0) {carType[0]=3.25;carType[1]=0.62;}
            else if (strcmp(car_class_driver,"green")==0) {carType[0]=4.00;carType[1]=0.79;}
            else if (strcmp(car_class_driver,"premium")==0) {carType[0]=5.20;carType[1]=0.94;}
            
            //  For loop that iterates throught the rides hash table to
            // search for all the rides the driver was in
            for(i=0; i < n_lines; i++){
                 // Getting the the information of the current ride  
                 getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, 
                               &distance_ride, &score_user_ride, &score_driver_ride, &tip_ride);
                 // Checking if the ride in not NULL.
                 if(date_ride!=NULL){
                    // Checking if the ride was drived by the driver.
                    if(strcmp(driver_ride,line)==0){
                        // Updating the fields statistics
                        average_score += score_driver_ride;
                        trip_counter++;
                        total_payed += carType[0] + carType[1]*distance_ride + tip_ride;
                    }
                 }
               }

            if(trip_counter!=0){ 
             
                fprintf(NewFile,"%s;%c;%d;%.3f;%d;%.3f\n",name_driver,gender_driver[0]
                                                         ,calculateAge(birth_day_driver)
                                                         ,average_score/trip_counter
                                                         ,trip_counter,total_payed);

            }
        }
    }

    else {                                                                                          
        
        // Getting the respective user fields 
        getUserFields(&line, &name_user, &gender_user, &birth_day_user, 
                      &account_creation_user, &account_status_user);
        
        // Checking if the user is not NULL and has an active account.
        if(name_user!=NULL && (strcmp((account_status_user),"active")==0)){  
            
            //  For loop that iterates throught the rides hash table to
            // search for all the rides that the user was in
            for(i=0; i < n_lines; i++){
                 // Getting the the information of the current ride  
                 getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, 
                               &distance_ride, &score_user_ride, &score_driver_ride, 
                               &tip_ride);
                 // Checking if the ride in not NULL.
                 if(date_ride!=NULL){
                    // Checking if the user was a passanger in the current ride.
                    if(strcmp(user_ride,line)==0){
                        // Getting the respective driver fields   
                        getDriverFields(&driver_ride, &name_driver, &birth_day_driver, 
                                        &gender_driver, &car_class_driver, &city_driver, 
                                        &account_creation_driver, &account_status_driver); 
                        // Checking if the driver is not NULL.
                        if(name_driver==NULL) return;
                        
                        // Calculating the user's total spent by adding what he payed on this ride to the argument total_spent.
                        if (strcmp(car_class_driver,"basic")==0) total_spent += 3.25 + 0.62*distance_ride + tip_ride;
                        else if (strcmp(car_class_driver,"green")==0) total_spent += 4.00 + 0.79*distance_ride + tip_ride;
                        else if (strcmp(car_class_driver,"premium")==0) total_spent += 5.20 + 0.94*distance_ride + tip_ride;
                        
                        // Updating the fields 
                        average_score += score_user_ride;
                        trip_counter++;
                    
                    }
                 }
               }
         
         if(trip_counter!=0){ 
             
             fprintf(NewFile,"%s;%c;%d;%.3f;%d;%.3f\n",name_user,gender_user[0]
                                                      ,calculateAge(birth_day_user)
                                                      ,average_score/trip_counter
                                                      ,trip_counter,total_spent);
         }
      }
    }     

    fclose(NewFile);            // Closing the output file
    
     
}



// Function responsible for executing query 2.
void query2(char *line,char *file){
    
    // Creating the arguments that change when called in the get function.
    char *date = NULL, *driver = NULL, *name = NULL; 
    double score_driver = 0.000, score_total = 0.000;
    int trip_counter = 0;

   

    FILE * NewFile;
    NewFile = fopen(file, "w");  // Opening the output file, so the query is able to write the output

    // Calculating the first line to be printed on the output file
    int ind = n_lines_drivers-1;
    // Calculating how many lines the function is gonna print
    int n_drivers = atoi(line);

    while(n_drivers!=0){
        // Getting the the information of the current rides_driver 
        getRideDriverFields(&ind , &date, &driver, &score_driver, 
                            &name, &trip_counter, &score_total);
        
        if(date!=NULL){
        fprintf(NewFile,"%s;%s;%.3f\n", driver, name, score_driver);
        }

        // Updating the arguments
        n_drivers--;
        ind--;
    }

    fclose(NewFile);            // Closing the output file
  
     
}



// Function responsible for executing query 3.
void query3(char *line,char *file){
    
     // Creating the arguments that change when called in the get function.
    char *date = NULL, *username = NULL, *nome = NULL;
    int distance = 0;
   
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Opening the output file, so the query is able to write the output

    // Calculating the first line to be printed on the output file
    int ind = n_lines_users-1;

    // Calculating how many lines the function is gonna print
    int n_users = atoi(line);

    while(n_users!=0){
        // Getting the the information of the current rides_user 
        getRideUserFields(&ind, &distance, &date, &username, &nome);   
        
        if(date!=NULL){
        fprintf(NewFile,"%s;%s;%d\n",username, nome, distance);
        }
        
        // Updating the arguments
        n_users--;
        ind--;
    }

    fclose(NewFile);            // Closing the output file
  
     
}



// Function responsible for executing query 4.
void query4(char *line,char *file){
    
    // Creating the arguments that change when called in the get function.
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, 
         *car_class_driver = NULL, *city_driver = NULL, *account_creation_driver = NULL, 
         *account_status_driver = NULL;
    
    char *date_ride = NULL, *driver_ride = NULL, *user_ride = NULL, 
         *city_ride = NULL; 
    int distance_ride = 0; 
    double score_user_ride = 0.000, score_driver_ride = 0.000, tip_ride = 0.000;
    
    double price_average = 0.000;
    int i, trip_counter = 0;

  
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Opening the output file, so the query is able to write the output
    
    //  For loop that iterates throught the rides hash table to
    // search for all the rides that took place in the city 
    // passed as an argument.
    for(i=0; i < n_lines; i++){
            // Getting the the information of the current ride  
            getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, &distance_ride, 
                               &score_user_ride, &score_driver_ride, &tip_ride); 
            // Checking if the ride in not NULL.
            if(date_ride!=NULL){
                //  Checking if the city the current ride took place
                // is equal to the city gave as an argument.   
                if(strcmp(city_ride,line)==0){
                    // Getting the respective driver fields 
                    getDriverFields(&driver_ride, &name_driver, &birth_day_driver, &gender_driver, 
                                    &car_class_driver, &city_driver, &account_creation_driver, 
                                    &account_status_driver);
                    // Checking if the driver is not NULL. 
                    if(name_driver!=NULL){
                        // Updating the average price in the city by adding the current ride data
                        if (strcmp(car_class_driver,"basic")==0) price_average += 3.25 + 0.62*distance_ride;
                        else if (strcmp(car_class_driver,"green")==0) price_average += 4.00 + 0.79*distance_ride;
                        else if (strcmp(car_class_driver,"premium")==0) price_average += 5.20 + 0.94*distance_ride;
                        // Updating the trip counter
                        trip_counter++;
                    }
                }
            }
    }
            
    if(trip_counter!=0) fprintf(NewFile,"%.3f\n",price_average/trip_counter);


    fclose(NewFile);            // Closing the output file
 
}



// Function responsible for executing query 5.
void query5(char *line,char *file){
    
    // Creating the arguments that change when called in the get function.
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, 
         *car_class_driver = NULL, *city_driver = NULL, *account_creation_driver = NULL, 
         *account_status_driver = NULL; 
    
    char *date_ride = NULL, *driver_ride = NULL, *user_ride = NULL, *city_ride = NULL; 
    int distance_ride = 0; 
    double score_user_ride = 0.000, score_driver_ride = 0.000, tip_ride = 0.000;

    double price_average = 0.000;
    int i, trip_counter = 0;
    
    // Calculating the dates passed in the argument
    char data1[11],data2[11];
    strncpy(data1,line,10);
    data1[10] = '\0';
    strncpy(data2,line+11,10);
    data2[10] = '\0';

    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Opening the output file, so the query is able to write the output
    
    //  For loop that iterates throught the rides hash table to
    // search for all the rides that took place between the dates 
    // passed as arguments.
    for(i=0; i < n_lines; i++){
        // Getting the the information of the current rides        
        getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, &distance_ride, 
                      &score_user_ride, &score_driver_ride, &tip_ride);
        // Checking if the ride in not NULL.
        if(date_ride!=NULL){
            // Calculating if the date from the ride is in between the two dates passed as an argument        
            if(calculateData(date_ride,data1)<=0 && calculateData(data2,date_ride)<=0){
                // Getting the respective driver fields         
                getDriverFields(&driver_ride, &name_driver, &birth_day_driver, &gender_driver, 
                                &car_class_driver, &city_driver, &account_creation_driver, 
                                &account_status_driver);
                // Checking if the driver is not NULL. 
                if(name_driver!=NULL){
                    // Updating the average price by adding the current ride data
                    if (strcmp(car_class_driver,"basic")==0) price_average += 3.25 + 0.62*distance_ride;
                    else if (strcmp(car_class_driver,"green")==0) price_average += 4.00 + 0.79*distance_ride;
                    else if (strcmp(car_class_driver,"premium")==0) price_average += 5.20 + 0.94*distance_ride;
                    // Updating the trip counter 
                    trip_counter++;
                }
            }
        }
    }
               
    if(trip_counter!=0) fprintf(NewFile,"%.3f\n",price_average/trip_counter);
    

    fclose(NewFile);            // Closing the output file
    
 
     
}



// Function responsible for executing query 6.
void query6(char *line,char *file){
    
    // Creating the arguments that change when called in the get function.
    char *date_ride = NULL, *driver_ride = NULL, *user_ride = NULL, *city_ride = NULL; 
    int distance_ride = 0; 
    double score_user_ride = 0.000, score_driver_ride = 0.000, tip_ride = 0.000;

    double dist = 0;
    int i, trip_counter = 0;
    
    // Calculating the city passed as an argument
    char city[20];
    for(i=0; line[i] != ' '; i++){
        
        city[i]=line[i];
    }
    city[i]='\0';

    // Calculating the dates passed in the argument
    char date1[11],date2[11];
    strncpy(date1,line+i+1,10);
    date1[10] = '\0';
    strncpy(date2,line+i+12,10);
    date2[10] = '\0';

 
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Opening the output file, so the query is able to write the output
    
    //  For loop that iterates throught the rides hash table to
    // search for all the rides that took place between the dates 
    // passed as arguments and in the city passed as an argument.
    for(i=0; i < n_lines; i++){
        // Getting the the information of the current ride          
        getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, 
                      &distance_ride, &score_user_ride, &score_driver_ride, 
                      &tip_ride);
        // Checking if the ride in not NULL.
        if (date_ride!=NULL){
             //  Checking if the ride took place in the city passed as an argument and if the date 
             // from the ride is in between the two dates passed as an argument.       
            if((strcmp(city_ride,city)==0) && (calculateData(date_ride,date1)<=0) && (calculateData(date2,date_ride)<=0)){
                // Updating the total distance and trip counter.
                dist += distance_ride;
                trip_counter++;
            }
        }
    }

    if(dist!=0) fprintf(NewFile,"%.3f\n",dist/trip_counter);
        
    fclose(NewFile);            // Closing the output file
  
     
}



// Function responsible for executing query 7.
void query7(char *line,char *file){

   
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write

    int i, j, n_drivers = 0;
    
    // Calculating the number of element the program needs to print.
    char*aux=malloc(sizeof(line));
    for (i=0; line[i]!=' '; i++){
        
        aux[i]=line[i];
    }
    aux[i]='\0';
    n_drivers = atoi(aux);

    // Calculating which city was passed as an argument.
    char *city = malloc(sizeof(strlen(line)-i));
    for (i=i+1,j=0; line[i]!='\0'; i++,j++){
        city[j]=line[i];
    }
    city[j]='\0';
    
    // Creating the arguments that change when called in the get function.
    char *id = NULL, *name = NULL;
    double score_average = 0.000, total_score = 0.000;
    int trip_counter = 0;
    
    // Creating the rides_drivers_city hash table
    insert_hash_rides_drivers_city(city);
    // Sorting the hash table
    sortQ7();
    
    // Calculating the first element to be printed
    int ind = n_lines_drivers-1;
    
    //  For loop that iterates throught the hash table and prints
    // in the output file all of them.
    while(n_drivers!=0){
        // Getting the the information of the current rides_driver_city
        getRideDriverCityFields(&ind, &score_average, &id, &trip_counter, 
                                &name, &total_score);

        if(id==NULL) break;

        fprintf(NewFile,"%s;%s;%.3f\n", id, name, score_average);
        
        // Updating the counters
        n_drivers--;
        ind--;
    }
    // Freeing the hash table
    free_hash_rides_driver_city();
    // Freeing pointer no longer needed.
    free(aux);
    free(city);

    fclose(NewFile);            // Closing the output file
  
     
}



// Function responsible for executing query 8.
void query8(char *line,char *file){

  
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Opening the output file, so the query is able to write the output
    
    char*aux = malloc(sizeof(line));
    char gender = line[0];

    int i, j = 0, age;

    // Calculating the age passed as an argument
    for(i=2;line[i]!='\0';i++,j++){
        aux[j]=line[i];
    }
    aux[j]='\0';
    age = atoi(aux);
    
    // Creating the arguments that change when called in the get function.
    char *id_driver = NULL, *name_driver = NULL, *username = NULL, 
         *name_user = NULL, *date_driver = NULL, *date_user = NULL, 
         *id_trip = NULL; 
    int isValid = 0;
    
    // Creating the rides gender hash table 
    insert_hash_rides_gender(gender,age);
    
    //  For loop that iterates throught the hash table and prints
    // in the output file all of them.
    for(i=0; i < n_lines_gender; i++){
        // Getting the the information of the current rides_gender
        getRideGenderFields(&id_driver, &name_driver, &username, &name_user, 
                            &date_driver, &date_user, &id_trip, &isValid);
        
        if(id_driver==NULL) break;
        
        fprintf(NewFile,"%s;%s;%s;%s\n", id_driver, name_driver, username, name_user);
    }
    
    // Freeing pointer no longer needed.
    free_hash_rides_gender();
    free(aux);

    fclose(NewFile);            // Closing the output file
 
}



// Function responsible for executing query 9.
void query9(char *line,char *file){
    int i;

    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Opening the output file, so the query is able to write the output

    // Calculating the dates passed in the argument
    char date1[11],date2[11];
    strncpy(date1,line,10);
    date1[10] = '\0';
    strncpy(date2,line+11,10);
    date2[10] = '\0';
    
    // Creating the arguments that change when called in the get function.
    char *date = NULL, *id = NULL, *city = NULL, *id_trip = NULL;
    int distance = 0, isValid = 0;
    double tip = 0.000;
    
    // Creating the rides date hash table 
    insert_hash_rides_date(date1,date2);
    
    //  For loop that iterates throught the hash table and prints
    // in the output file all of them.
    for(i=0;i<n_lines_drivers;i++){
        // Getting the the information of the current rides_date
        getRideDateFields(&distance, &date, &id, &city, 
                          &tip, &id_trip, &isValid);
        
        if(date==NULL) break;
        
        fprintf(NewFile,"%s;%s;%d;%s;%.3f\n", id, date, distance, city, tip);
    }

    fclose(NewFile);            // Closing the output file
    
}



//  Function responsible for opening and reading the .txt file relative to the inputs of the
// queries. This function, for each line it reads, sends the input to one of the relative functions
// to queries for future data processing.
//
//  This function also calculate the time each query took and if the output was correct,
// if the flag 'checkTime' is equal to zero.
void read_exe_queries(char *file, int checkTime, char *outputs){

    // Opens the input's file
    FILE* File1;
    File1 = fopen(file,"r");
    
    if (chdir("Resultados/") != 0);     // Changes to the main directory


    char line[150],line2[150];
    char query;
    
    int i,input = 0;
    
    // Reads every line in the input's file
    while(fgets(line, 150, File1)!=NULL){

        double aux;
        input++;
        char buffer [50];

        //  This function is responsible for creating an output text file
        // with the number corresponding to the input number.
        snprintf(buffer, sizeof (buffer), "command%d_output.txt",input);

        // Calculating which query to execute.
        query = line[0];       
    
        for(i=2;line[i]!='\0';i++){         //  This for loop distinguishes, from the query number, 
            line2[i-2] = line[i];           // the rest of the input to later provide the functions that
        }                                   // execute the queries with the correct arguments.
        line2[i-3] = '\0';

        //  This switch case chooses according to the variable query
        // which block to execute.
        switch (query){
         
          case '1':
             if(checkTime==0){
                  aux = time_query(query1,line2,buffer);
                  if(aux >=10){
                    printf("\033[0;33m");
                    printf("Input %d [Query 1]: %fs ", input, aux);
                    printf("\033[0m");
                  } 
                  else printf("Input %d [Query 1]: %fs ", input, aux);
                  check_output(input, outputs);
             }
             else query1(line2, buffer);
             break;

          case '2':
             if(checkTime==0){
                  aux = time_query(query2,line2,buffer);
                  if(aux>=10){
                    printf("\033[0;33m");
                    printf("Input %d [Query 2]: %fs ", input, aux);
                    printf("\033[0m");
                  }
                  else printf("Input %d [Query 2]: %fs ", input, aux);
                  check_output(input, outputs);
             }
             else query2(line2,buffer);
             break;

          case '3':
             if(checkTime==0){
                  aux = time_query(query3,line2,buffer);
                  if(aux>=10){
                    printf("\033[0;33m");
                    printf("Input %d [Query 3]: %fs ", input, aux);
                    printf("\033[0m");
                  }
                  else printf("Input %d [Query 3]: %fs ", input, aux);
                  check_output(input, outputs);
             }
             else query3(line2,buffer);
             break;

          case '4':
             if(checkTime==0){
                  aux = time_query(query4,line2,buffer);
                  if(aux>=10){
                    printf("\033[0;33m");
                    printf("Input %d [Query 4]: %fs ", input, aux);
                    printf("\033[0m");
                  }
                  else printf("Input %d [Query 4]: %fs ", input, aux);
                  check_output(input, outputs);
             }
             else query4(line2,buffer);
             break;

          case '5':
             if(checkTime==0){
                  aux = time_query(query5,line2,buffer);
                  if(aux>=10){
                    printf("\033[0;33m");
                    printf("Input %d [Query 5]: %fs ", input, aux);
                    printf("\033[0m");
                  }
                  else printf("Input %d [Query 5]: %fs ", input, aux);
                  check_output(input, outputs);
             }
             else query5(line2,buffer);
             break;

          case '6':
             if(checkTime==0){
                  aux = time_query(query6,line2,buffer);
                  if(aux>=10){
                    printf("\033[0;33m");
                    printf("Input %d [Query 6]: %fs ", input, aux);
                    printf("\033[0m");
                  }
                  else printf("Input %d [Query 6]: %fs ", input, aux);
                  check_output(input, outputs);
             }
             else query6(line2,buffer);
             break;

          case '7':
             if(checkTime==0){
                  aux = time_query(query7,line2,buffer);
                  if(aux>=10){
                    printf("\033[0;33m");
                    printf("Input %d [Query 7]: %fs ", input, aux);
                    printf("\033[0m");
                  }
                  else printf("Input %d [Query 7]: %fs ", input, aux);
                  check_output(input, outputs);
             }
             else query7(line2,buffer);
             break;

          case '8':
             if(checkTime==0){
                  aux = time_query(query8,line2,buffer);
                  if(aux>=10){
                    printf("\033[0;33m");
                    printf("Input %d [Query 8]: %fs ", input, aux);
                    printf("\033[0m");
                  }
                  else printf("Input %d [Query 8]: %fs ", input, aux);
                  check_output(input, outputs);
             }
             else query8(line2,buffer);
             break;

          case '9':
             if(checkTime==0){
                  aux = time_query(query9,line2,buffer);
                  if(aux>=10){
                    printf("\033[0;33m");
                    printf("Input %d [Query 9]: %fs ", input, aux);
                    printf("\033[0m");
                  }
                  else printf("Input %d [Query 9]: %fs ", input, aux);
                  check_output(input, outputs);
             }
             else query9(line2,buffer);
             break;
              
          default:
             break;
        }
  
    }
    // Closing the input file
    fclose(File1);
    
    if (chdir("trabalho-pratico") != 0);    // Changes to the main directory


}



int read_exe_queries_interactive(char *file){

    char line[150];
    char query;
    int i;

    //  Calculating which query to execute based 
    // on the line given by the user
    query = file[0];       
        
    if(file[1]!=' ') return 1;

    for(i=2;file[i]!='\0';i++){          //  This for loop distinguishes, from the query number, 
         line[i-2] = file[i];            // the rest of the input to later provide the functions that
    }                                    // execute the queries with the correct arguments.
    line[i-2] = '\0';
    
    if (chdir("Resultados/") != 0);

    //  This switch case chooses according to the variable query
    // which block to execute.
    switch (query)
        {
        case '1':
           query1(line,"command_output_interativo.txt");
           break;

        case '2':
           query2(line,"command_output_interativo.txt");
           break;

        case '3':
           query3(line,"command_output_interativo.txt");
           break;

        case '4':
           query4(line,"command_output_interativo.txt");
           break;
           
        case '5':
           query5(line,"command_output_interativo.txt");
           break;

        case '6':
           query6(line,"command_output_interativo.txt");
           break;   

        case '7':
           query7(line,"command_output_interativo.txt");
           break; 

        case '8':
           query8(line,"command_output_interativo.txt");
           break; 

        case '9':
           query9(line,"command_output_interativo.txt");
           break; 
             
        default:
           return 1;
           break;
        }

    if (chdir("trabalho-pratico") != 0);     // Changes to the main directory


    return 0;
  
}
