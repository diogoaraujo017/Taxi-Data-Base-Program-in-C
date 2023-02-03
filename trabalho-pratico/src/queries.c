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

// Função responsável pela execução da querie 1.
void query1(char *line,char *file){ 

    int i,numero_viagens=0;
    double carType[2];
    double average_score=0.000, total_payed=0.000, total_spent=0.000;

    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, 
         *car_class_driver = NULL, *city_driver = NULL, *account_creation_driver = NULL, 
         *account_status_driver = NULL;
    
    char *name_user = NULL, *gender_user = NULL, *birth_day_user = NULL, 
         *account_creation_user = NULL, *account_status_user = NULL;
    
    char *date_ride = NULL, *driver_ride = NULL, *user_ride = NULL, *city_ride = NULL; 
    int distance_ride = 0; 
    double score_user_ride = 0.000, score_driver_ride = 0.000, tip_ride = 0.000;

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write
    
    if(line[0]=='0') {                                        // O input da querie é um id (corresponde a um driver)
                            
        getDriverFields(&line, &name_driver, &birth_day_driver, &gender_driver, 
                        &car_class_driver, &city_driver, &account_creation_driver, 
                        &account_status_driver); 

        if(name_driver!=NULL && (strcmp((account_status_driver),"active")==0)){  // Verifica se o driver existe e tem a conta ativa
            
            if (strcmp(car_class_driver,"basic")==0) {carType[0]=3.25;carType[1]=0.62;}
            else if (strcmp(car_class_driver,"green")==0) {carType[0]=4.00;carType[1]=0.79;}
            else if (strcmp(car_class_driver,"premium")==0) {carType[0]=5.20;carType[1]=0.94;}
            
            for(i=0; i < n_lines; i++){

                 getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, 
                               &distance_ride, &score_user_ride, &score_driver_ride, &tip_ride);

                 if(date_ride!=NULL){

                    if(strcmp(driver_ride,line)==0){
                        average_score += score_driver_ride;
                        numero_viagens++;
                        total_payed += carType[0] + carType[1]*distance_ride + tip_ride;
                    }
                 }
               }
            if(numero_viagens!=0){ 
             
                fprintf(NewFile,"%s;%c;%d;%.3f;%d;%.3f\n",name_driver,gender_driver[0]
                                                         ,calculateAge(birth_day_driver)
                                                         ,average_score/numero_viagens
                                                         ,numero_viagens,total_payed);

            }
        }
    }

    else {                                                  // O input da querie é um username (corresponde a um user)                                            
        
        getUserFields(&line, &name_user, &gender_user, &birth_day_user, 
                      &account_creation_user, &account_status_user);
        
        if(name_user!=NULL && (strcmp((account_status_user),"active")==0)){  // Verifica se o user existe e tem a conta ativa
            
            for(i=0; i < n_lines; i++){
                 
                 getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, 
                               &distance_ride, &score_user_ride, &score_driver_ride, 
                               &tip_ride);

                 if(date_ride!=NULL){

                    if(strcmp(user_ride,line)==0){
                   
                        getDriverFields(&driver_ride, &name_driver, &birth_day_driver, 
                                        &gender_driver, &car_class_driver, &city_driver, 
                                        &account_creation_driver, &account_status_driver); 

                        if(name_driver==NULL) return;

                        if (strcmp(car_class_driver,"basic")==0) total_spent += 3.25 + 0.62*distance_ride + tip_ride;
                        else if (strcmp(car_class_driver,"green")==0) total_spent += 4.00 + 0.79*distance_ride + tip_ride;
                        else if (strcmp(car_class_driver,"premium")==0) total_spent += 5.20 + 0.94*distance_ride + tip_ride;

                        average_score += score_user_ride;
                        numero_viagens++;
                    
                    }
                 }
               }
         
         if(numero_viagens!=0){ 
             
             fprintf(NewFile,"%s;%c;%d;%.3f;%d;%.3f\n",name_user,gender_user[0]
                                                      ,calculateAge(birth_day_user)
                                                      ,average_score/numero_viagens
                                                      ,numero_viagens,total_spent);
         }
      }
    }     

    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 2.
void query2(char *line,char *file){
    
    char *date = NULL, *driver = NULL, *name = NULL; 
    double score_driver = 0.000, score_total = 0.000;
    int trip_counter = 0;

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write

    int ind = n_lines_drivers-1;

    int n_drivers = atoi(line);

    while(n_drivers!=0){

        getRideDriverFields(&ind , &date, &driver, &score_driver, 
                            &name, &trip_counter, &score_total);

        fprintf(NewFile,"%s;%s;%.3f\n", driver, name, score_driver);

        n_drivers--;
        ind--;
    }

    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 3.
void query3(char *line,char *file){
    
    char *date = NULL, *username = NULL, *nome = NULL;
    int distance = 0;
    
    int ind = n_lines_users-1;
    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write

    int n_users = atoi(line);

    while(n_users!=0){
        
        getRideUserFields(&ind, &distance, &date, &username, &nome);   
        
        fprintf(NewFile,"%s;%s;%d\n",username, nome, distance);
        
        n_users--;
        ind--;
    }

    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 4.
void query4(char *line,char *file){
    
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, 
         *car_class_driver = NULL, *city_driver = NULL, *account_creation_driver = NULL, 
         *account_status_driver = NULL;
    
    char *date_ride = NULL, *driver_ride = NULL, *user_ride = NULL, 
         *city_ride = NULL; 
    int distance_ride = 0; 
    double score_user_ride = 0.000, score_driver_ride = 0.000, tip_ride = 0.000;
    
    double price_average = 0.000;
    int i, trip_counter = 0;

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries.
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write.
    
    for(i=0; i < n_lines; i++){
            
            getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, &distance_ride, 
                               &score_user_ride, &score_driver_ride, &tip_ride); 
            
            if(date_ride!=NULL){
                    
                if(strcmp(city_ride,line)==0){

                    getDriverFields(&driver_ride, &name_driver, &birth_day_driver, &gender_driver, 
                                    &car_class_driver, &city_driver, &account_creation_driver, 
                                    &account_status_driver);

                    if(name_driver!=NULL){
                        
                        if (strcmp(car_class_driver,"basic")==0) price_average += 3.25 + 0.62*distance_ride;
                        else if (strcmp(car_class_driver,"green")==0) price_average += 4.00 + 0.79*distance_ride;
                        else if (strcmp(car_class_driver,"premium")==0) price_average += 5.20 + 0.94*distance_ride;
                     
                        trip_counter++;
                    }
                }
            }
    }
            
    if(trip_counter!=0) fprintf(NewFile,"%.3f\n",price_average/trip_counter);


    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 5.
void query5(char *line,char *file){
    
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, 
         *car_class_driver = NULL, *city_driver = NULL, *account_creation_driver = NULL, 
         *account_status_driver = NULL; 
    
    char *date_ride = NULL, *driver_ride = NULL, *user_ride = NULL, *city_ride = NULL; 
    int distance_ride = 0; 
    double score_user_ride = 0.000, score_driver_ride = 0.000, tip_ride = 0.000;

    double price_average = 0.000;
    int i, trip_counter = 0;
    
    char data1[10],data2[10];

    strncpy(data1,line,10);
    strncpy(data2,line+11,10);

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries.
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write.
    
    for(i=0; i < n_lines; i++){
                 
        getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, &distance_ride, 
                      &score_user_ride, &score_driver_ride, &tip_ride);

        if(date_ride!=NULL){
                    
            if(calculateData(date_ride,data1)<=0 && calculateData(data2,date_ride)<=0){
                        
                getDriverFields(&driver_ride, &name_driver, &birth_day_driver, &gender_driver, 
                                &car_class_driver, &city_driver, &account_creation_driver, 
                                &account_status_driver);

                if(name_driver!=NULL){
                    
                    if (strcmp(car_class_driver,"basic")==0) price_average += 3.25 + 0.62*distance_ride;
                    else if (strcmp(car_class_driver,"green")==0) price_average += 4.00 + 0.79*distance_ride;
                    else if (strcmp(car_class_driver,"premium")==0) price_average += 5.20 + 0.94*distance_ride;
                     
                    trip_counter++;
                }
            }
        }
    }
               
    if(trip_counter!=0) fprintf(NewFile,"%.3f\n",price_average/trip_counter);
    

    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 6.
void query6(char *line,char *file){
    
    char *date_ride = NULL, *driver_ride = NULL, *user_ride = NULL, *city_ride = NULL; 
    int distance_ride = 0; 
    double score_user_ride = 0.000, score_driver_ride = 0.000, tip_ride = 0.000;

    double dist = 0;
    int i, trip_counter = 0;

    char city[20],date1[10],date2[10];

    for(i=0; line[i] != ' '; i++){
        
        city[i]=line[i];
    }
    city[i]='\0';
    
    strncpy(date1,line+i+1,10);
    strncpy(date2,line+i+12,10);

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries.
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write.
    
    for(i=0; i < n_lines; i++){
                 
        getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, 
                      &distance_ride, &score_user_ride, &score_driver_ride, 
                      &tip_ride);

        if (date_ride!=NULL){
                    
            if((strcmp(city_ride,city)==0) && (calculateData(date_ride,date1)<=0) && (calculateData(date2,date_ride)<=0)){
                dist += distance_ride;
                trip_counter++;
            }
        }
    }

    if(dist!=0) fprintf(NewFile,"%.3f\n",dist/trip_counter);
        
    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 7.
void query7(char *line,char *file){

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write

    int i, j, n_drivers = 0;
    
    char*aux=malloc(sizeof(line));

    for (i=0; line[i]!=' '; i++){
        
        aux[i]=line[i];
    }
    aux[i]='\0';

    n_drivers = atoi(aux);

    char *city = malloc(sizeof(strlen(line)-i));

    for (i=i+1,j=0; line[i]!='\0'; i++,j++){
        city[j]=line[i];
    }
    city[j]='\0';

    char *id = NULL, *name = NULL;
    double score_average = 0.000, total_score = 0.000;
    int trip_counter = 0;
    
    insert_hash_rides_drivers_city(city);
    sortQ7();

    int ind = n_lines_drivers-1;

    while(n_drivers!=0){

        getRideDriverCityFields(&ind, &score_average, &id, &trip_counter, 
                                &name, &total_score);

        if(strcmp(name,"null")==0) break;

        fprintf(NewFile,"%s;%s;%.3f\n", id, name, score_average);
        
        n_drivers--;
        ind--;
    }

    free_hash_rides_driver_city();

    free(aux);
    free(city);

    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal

    
}
// Função responsável pela execução da querie 8.
void query8(char *line,char *file){

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write

    char*aux=malloc(sizeof(line));
    char gender=line[0];

    int i, j = 0, age;

    for(i=2;line[i]!='\0';i++,j++){
        aux[j]=line[i];
    }
    aux[j]='\0';

    age = atoi(aux);

    char *id_driver = NULL, *name_driver = NULL, *username = NULL, 
         *name_user = NULL, *date_driver = NULL, *date_user = NULL, 
         *id_trip = NULL; 
    int isValid = 0;

    insert_hash_rides_gender(gender,age);

    for(i=0; i < n_lines_gender; i++){
        
        getRideGenderFields(&id_driver, &name_driver, &username, &name_user, 
                            &date_driver, &date_user, &id_trip, &isValid);
        
        if(name_driver==NULL) break;
        
        fprintf(NewFile,"%s;%s;%s;%s\n", id_driver, name_driver, username, name_user);
    }
    
    free_hash_rides_gender();
    free(aux);

    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal

}

// Função responsável pela execução da querie 9.
void query9(char *line,char *file){

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write

    char date1[10],date2[10];
    
    int i;
    
    strncpy(date1,line,10);
    strncpy(date2,line+11,10);

    char *date = NULL, *id = NULL, *city = NULL, *id_trip = NULL;
    int distance = 0, isValid = 0;
    double tip = 0.000;
    
    insert_hash_rides_date(date1,date2);

    for(i=0;i<n_lines_drivers;i++){
        
        getRideDateFields(&distance, &date, &id, &city, 
                          &tip, &id_trip, &isValid);
        
        if(date==NULL) break;
        
        fprintf(NewFile,"%s;%s;%d;%s;%.3f\n", id, date, distance, city, tip);
    }

    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal

}

// Função responsável pela abertura e leitura do ficheiro .txt relativo aos inputs das
// queries. Esta função a cada linha que lê, envia o input para uma das funções relativas
// às queries para futuro tratamento dos dados.
void read_exe_queries(char *file, int checkTime, char *outputs){

    // Leitura do ficheiro .txt de modo a recebemos os seus inputs para as queries
    FILE* File1;
    File1 = fopen(file,"r");
    
    char line[150],line2[150];
    char querie;
    
    int i,input = 0;
    
    // Leitura das várias linhas do ficheiro .txt e redirecionamento para a sua querie correspondente
    while(fgets(line, 150, File1)!=NULL){

        input++;
        char buffer [50];

        // Esta função é responsável pela criação de N ficheiros de texto .txt com o intuito de 
        // serem escritos com o output correspondente à querie em questão. Os ficheiros terão o nome
        // commandX_output.txt
        snprintf(buffer, sizeof (buffer), "command%d_output.txt",input);


        querie = line[0];       // O primeiro dígito da linha é o número da querie correspondente
    
        for(i=2;line[i]!='\0';i++){         // Este for loop faz a distinção do resto do input
            line2[i-2] = line[i];           // para mais tarde ser fornecido as funções que 
        }                                   // executam as queries.

        line2[i-3] = '\0';

        switch (querie){
       
          case '1':
             if(checkTime==0){
                  printf("Input %d [Query 1]: %fs ", input, time_query(query1,line2,buffer));
                  check_output(input, outputs);
             }
             else query1(line2, buffer);
             break;

          case '2':
             if(checkTime==0){
                  printf("Input %d [Query 2]: %fs ", input, time_query(query2,line2,buffer));
                  check_output(input, outputs);
             }
             else query2(line2,buffer);
             break;

          case '3':
             if(checkTime==0){
                  printf("Input %d [Query 3]: %fs ", input, time_query(query3,line2,buffer));
                  check_output(input, outputs);
             }
             else query3(line2,buffer);
             break;

          case '4':
             if(checkTime==0){
                  printf("Input %d [Query 4]: %fs ", input, time_query(query4,line2,buffer));
                  check_output(input, outputs);
             }
             else query4(line2,buffer);
             break;

          case '5':
             if(checkTime==0){
                  printf("Input %d [Query 5]: %fs ", input, time_query(query5,line2,buffer));
                  check_output(input, outputs);
             }
             else query5(line2,buffer);
             break;

          case '6':
             if(checkTime==0){
                  printf("Input %d [Query 6]: %fs ", input, time_query(query6,line2,buffer));
                  check_output(input, outputs);
             }
             else query6(line2,buffer);
             break;

          case '7':
             if(checkTime==0){
                  printf("Input %d [Query 7]: %fs ", input, time_query(query7,line2,buffer));
                  check_output(input, outputs);
             }
             else query7(line2,buffer);
             break;

          case '8':
             if(checkTime==0){
                  printf("Input %d [Query 8]: %fs ", input, time_query(query8,line2,buffer));
                  check_output(input, outputs);
             }
             else query8(line2,buffer);
             break;

          case '9':
             if(checkTime==0){
                  printf("Input %d [Query 9]: %fs ", input, time_query(query9,line2,buffer));
                  check_output(input, outputs);
             }
             else query9(line2,buffer);
             break;
              
          default:
             break;
        }
  
    }

    fclose(File1);

}





int read_exe_queries_interactive(char *file){

    char line[150];
    char querie;
    int i;

    querie = file[0];       // O primeiro dígito da linha é o número da querie correspondente
        
    if(file[1]!=' ') return 1;

    for(i=2;file[i]!='\0';i++){         // Este for loop faz a distinção do resto do input
    
        line[i-2] = file[i];           // para mais tarde ser fornecido as funções que 
    }                                   // executam as queries.
    line[i-2] = '\0';

    switch (querie)
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
        
    return 0;
  
}