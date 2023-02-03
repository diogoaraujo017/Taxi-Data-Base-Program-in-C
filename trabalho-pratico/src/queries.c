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
void querie1(char *line,char *file){ 

    int i,numero_viagens=0;
    double carType[2];
    double avaliacao_media=0.000,total_auferido=0.000,total_gasto=0.000;

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
                            
        getDriverFields(&line, &name_driver, &birth_day_driver, &gender_driver, &car_class_driver, &city_driver, &account_creation_driver, &account_status_driver); 

        if(name_driver!=NULL && (strcmp((account_status_driver),"active")==0)){  // Verifica se o driver existe e tem a conta ativa
            
            if (strcmp(car_class_driver,"basic")==0) {carType[0]=3.25;carType[1]=0.62;}
            else if (strcmp(car_class_driver,"green")==0) {carType[0]=4.00;carType[1]=0.79;}
            else if (strcmp(car_class_driver,"premium")==0) {carType[0]=5.20;carType[1]=0.94;}
            
            for(i=0;i<n_linhas;i++){

                 getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, &distance_ride, &score_user_ride, &score_driver_ride, &tip_ride);

                 if(date_ride!=NULL){

                    if(strcmp(driver_ride,line)==0){
                        avaliacao_media += score_driver_ride;
                        numero_viagens++;
                        total_auferido += carType[0] + carType[1]*distance_ride + tip_ride;
                    }
                 }
               }
            if(numero_viagens!=0) fprintf(NewFile,"%s;%c;%d;%.3f;%d;%.3f\n",name_driver,gender_driver[0],calculaIdade(birth_day_driver),avaliacao_media/numero_viagens,numero_viagens,total_auferido);
        }
    }

    else {                                                  // O input da querie é um username (corresponde a um user)                                            
        getUserFields(&line, &name_user, &gender_user, &birth_day_user, &account_creation_user, &account_status_user);
        if(name_user!=NULL && (strcmp((account_status_user),"active")==0)){  // Verifica se o user existe e tem a conta ativa
            
            for(i=0;i<n_linhas;i++){
                 
                 getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, &distance_ride, &score_user_ride, &score_driver_ride, &tip_ride);

                 if(date_ride!=NULL){

                    if(strcmp(user_ride,line)==0){
                   
                        getDriverFields(&driver_ride, &name_driver, &birth_day_driver, &gender_driver, &car_class_driver, &city_driver, &account_creation_driver, &account_status_driver); 

                        if(name_driver==NULL) return;
                        if (strcmp(car_class_driver,"basic")==0) total_gasto += 3.25 + 0.62*distance_ride + tip_ride;
                        else if (strcmp(car_class_driver,"green")==0) total_gasto += 4.00 + 0.79*distance_ride + tip_ride;
                        else if (strcmp(car_class_driver,"premium")==0) total_gasto += 5.20 + 0.94*distance_ride + tip_ride;

                        avaliacao_media += score_user_ride;
                        numero_viagens++;
                     
                    
                    }
                 }
               }
         
         if(numero_viagens!=0) fprintf(NewFile,"%s;%c;%d;%.3f;%d;%.3f\n",name_user,gender_user[0],calculaIdade(birth_day_user),avaliacao_media/numero_viagens,numero_viagens,total_gasto);
        }
    }     

    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 2.
void querie2(char *line,char *file){
    
    char *date = NULL, *driver = NULL, *nome = NULL; 
    double score_driver = 0.000, score_total = 0.000;
    int numero_viagens = 0;

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write

    int ind=n_linhas_drivers-1;
    int n_condutores=atoi(line);

    while(n_condutores!=0){

        getRideDriverFields(&ind , &date, &driver, &score_driver, &nome, &numero_viagens, &score_total);

        fprintf(NewFile,"%s;%s;%.3f\n", driver, nome, score_driver);

        n_condutores--;
        ind--;
    }

    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 3.
void querie3(char *line,char *file){
    
    char *date = NULL, *username = NULL, *nome = NULL;
    int distancia = 0;
    
    int ind = n_linhas_users-1;
    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write


    int n_utilizadores=atoi(line);

    while(n_utilizadores!=0){
        
        getRideUserFields(&ind, &distancia, &date, &username, &nome);   
        
        fprintf(NewFile,"%s;%s;%d\n",username, nome, distancia);
        
        n_utilizadores--;
        ind--;
    }

    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 4.
void querie4(char *line,char *file){
    
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, 
         *car_class_driver = NULL, *city_driver = NULL, *account_creation_driver = NULL, 
         *account_status_driver = NULL;
    
    char *date_ride = NULL, *driver_ride = NULL, *user_ride = NULL, 
         *city_ride = NULL; 
    int distance_ride = 0; 
    double score_user_ride = 0.000, score_driver_ride = 0.000, tip_ride = 0.000;
    
    double preco_medio=0.000;
    int i, numero_viagens=0;

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries.
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write.
    
     for(i=0;i<n_linhas;i++){
                 getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, &distance_ride, &score_user_ride, &score_driver_ride, &tip_ride); 
                 if(date_ride!=NULL){
                    if(strcmp(city_ride,line)==0){

                        getDriverFields(&driver_ride, &name_driver, &birth_day_driver, &gender_driver, &car_class_driver, &city_driver, &account_creation_driver, &account_status_driver);

                        if(name_driver!=NULL){
                            if (strcmp(car_class_driver,"basic")==0) preco_medio += 3.25 + 0.62*distance_ride;
                            else if (strcmp(car_class_driver,"green")==0) preco_medio += 4.00 + 0.79*distance_ride;
                            else if (strcmp(car_class_driver,"premium")==0) preco_medio += 5.20 + 0.94*distance_ride;
                     
                        numero_viagens++;
                        }
                    }
                 }
               }
            
        if(numero_viagens!=0) fprintf(NewFile,"%.3f\n",preco_medio/numero_viagens);


        fclose(NewFile);            //Fecha o ficheiro criado
        chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 5.
void querie5(char *line,char *file){
    
    char *name_driver = NULL, *birth_day_driver = NULL, *gender_driver = NULL, 
         *car_class_driver = NULL, *city_driver = NULL, *account_creation_driver = NULL, 
         *account_status_driver = NULL; 
    
    char *date_ride = NULL, *driver_ride = NULL, *user_ride = NULL, *city_ride = NULL; 
    int distance_ride = 0; 
    double score_user_ride = 0.000, score_driver_ride = 0.000, tip_ride = 0.000;

    double preco_medio=0.000;
    int i,numero_viagens=0;
    char data1[10],data2[10];

    strncpy(data1,line,10);
    strncpy(data2,line+11,10);

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries.
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write.
    
     for(i=0;i<n_linhas;i++){
                 
                 getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, &distance_ride, &score_user_ride, &score_driver_ride, &tip_ride);

                 if(date_ride!=NULL){
                    if(calculaData(date_ride,data1)<=0 && calculaData(data2,date_ride)<=0){
                        
                        getDriverFields(&driver_ride, &name_driver, &birth_day_driver, &gender_driver, &car_class_driver, &city_driver, &account_creation_driver, &account_status_driver);

                        if(name_driver!=NULL){
                            if (strcmp(car_class_driver,"basic")==0) preco_medio += 3.25 + 0.62*distance_ride;
                            else if (strcmp(car_class_driver,"green")==0) preco_medio += 4.00 + 0.79*distance_ride;
                            else if (strcmp(car_class_driver,"premium")==0) preco_medio += 5.20 + 0.94*distance_ride;
                     
                        numero_viagens++;
                        }
                    }
                 }
               }
               
        if(numero_viagens!=0) fprintf(NewFile,"%.3f\n",preco_medio/numero_viagens);
    

        fclose(NewFile);            //Fecha o ficheiro criado
        chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 6.
void querie6(char *line,char *file){
    
    char *date_ride = NULL, *driver_ride = NULL, *user_ride = NULL, *city_ride = NULL; 
    int distance_ride = 0; 
    double score_user_ride = 0.000, score_driver_ride = 0.000, tip_ride = 0.000;

    double dist=0;
    int i,numero_viagens=0;
    char cidade[20],data1[10],data2[10];

    for(i=0;line[i] != ' ';i++){
        cidade[i]=line[i];
    }
    cidade[i]='\0';
    strncpy(data1,line+i+1,10);
    strncpy(data2,line+i+12,10);

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries.
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write.
    
     for(i=0;i<n_linhas;i++){
                 
                 getRideFields(&i, &date_ride, &driver_ride, &user_ride, &city_ride, &distance_ride, &score_user_ride, &score_driver_ride, &tip_ride);

                 if (date_ride!=NULL){
                    if((strcmp(city_ride,cidade)==0) && (calculaData(date_ride,data1)<=0) && (calculaData(data2,date_ride)<=0)){
                        dist += distance_ride;
                        numero_viagens++;
                    }
                 }
               }

        if(dist!=0) fprintf(NewFile,"%.3f\n",dist/numero_viagens);
        
        fclose(NewFile);            //Fecha o ficheiro criado
        chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 7.
void querie7(char *line,char *file){

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write

    int i,j,n_condutores=0;
    char*aux=malloc(sizeof(line));
    for (i=0;line[i]!=' ';i++){
        aux[i]=line[i];
    }
    aux[i]='\0';
    n_condutores= atoi(aux);

    char *city = malloc(sizeof(strlen(line)-i));
    for (i=i+1,j=0;line[i]!='\0';i++,j++){
        city[j]=line[i];
    }
    city[j]='\0';

    char *id = NULL, *nome = NULL;
    double avaliacao_media = 0.000, avaliacao_total = 0.000;
    int numero_viagens = 0;
    
    
    insert_hash_rides_drivers_city(city);
    sortQ7();

    int ind = n_linhas_drivers-1;

    while(n_condutores!=0){

        getRideDriverCityFields(&ind, &avaliacao_media, &id, &numero_viagens, &nome, &avaliacao_total);

        if(strcmp(nome,"null")==0) break;

        fprintf(NewFile,"%s;%s;%.3f\n", id, nome, avaliacao_media);
        
        n_condutores--;
        ind--;
    }

    free_hash_rides_driver_city();

    free(aux);
    free(city);

    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal

    
}
// Função responsável pela execução da querie 8.
void querie8(char *line,char *file){

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write

    char*aux=malloc(sizeof(line));
    char genero=line[0];
    int i,j=0,idade;

    for(i=2;line[i]!='\0';i++,j++){
        aux[j]=line[i];
    }
    aux[j]='\0';
    idade = atoi(aux);

    char *id_condutor = NULL, *nome_condutor = NULL, *username_utilizador = NULL, 
         *nome_utilizador = NULL, *data_driver = NULL, *data_user = NULL, *id_viagem = NULL; 
    int isValid = 0;

    insert_hash_rides_gender(genero,idade);

    for(i=0;i<n_linhas_gender;i++){
        
        getRideGenderFields(&id_condutor, &nome_condutor, &username_utilizador, &nome_utilizador, &data_driver, &data_user, &id_viagem, &isValid);
        
        if(nome_condutor==NULL)break;
        
        fprintf(NewFile,"%s;%s;%s;%s\n", id_condutor, nome_condutor, username_utilizador, nome_utilizador);
    }
    
    free_hash_rides_gender();
    free(aux);

    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal

}

// Função responsável pela execução da querie 9.
void querie9(char *line,char *file){

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write

    char date1[10],date2[10];
    register int i;
    
    strncpy(date1,line,10);
    strncpy(date2,line+11,10);

    char *date = NULL, *id = NULL, *city = NULL, *id_viagem = NULL;
    int distance = 0, isValid = 0;
    double tip = 0.000;
    
    insert_hash_rides_date(date1,date2);

    for(i=0;i<n_linhas_drivers;i++){
        
        getRideDateFields(&distance, &date, &id, &city, &tip, &id_viagem, &isValid);
        
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
    int i,input=0;
    
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

        switch (querie)
        {
        case '1':
           if(checkTime==0){
                printf("Input %d [Query 1]: %fs ", input, time_query(querie1,line2,buffer));
                check_output(input, outputs);
           }
           else querie1(line2, buffer);
           break;

        case '2':
           if(checkTime==0){
                printf("Input %d [Query 2]: %fs ", input, time_query(querie2,line2,buffer));
                check_output(input, outputs);
           }
           else querie2(line2,buffer);
           break;

        case '3':
           if(checkTime==0){
                printf("Input %d [Query 3]: %fs ", input, time_query(querie3,line2,buffer));
                check_output(input, outputs);
           }
           else querie3(line2,buffer);
           break;

        case '4':
           if(checkTime==0){
                printf("Input %d [Query 4]: %fs ", input, time_query(querie4,line2,buffer));
                check_output(input, outputs);
           }
           else querie4(line2,buffer);
           break;

        case '5':
           if(checkTime==0){
                printf("Input %d [Query 5]: %fs ", input, time_query(querie5,line2,buffer));
                check_output(input, outputs);
           }
           else querie5(line2,buffer);
           break;

        case '6':
           if(checkTime==0){
                printf("Input %d [Query 6]: %fs ", input, time_query(querie6,line2,buffer));
                check_output(input, outputs);
           }
           else querie6(line2,buffer);
           break;

        case '7':
           if(checkTime==0){
                printf("Input %d [Query 7]: %fs ", input, time_query(querie7,line2,buffer));
                check_output(input, outputs);
           }
           else querie7(line2,buffer);
           break;

        case '8':
           if(checkTime==0){
                printf("Input %d [Query 8]: %fs ", input, time_query(querie8,line2,buffer));
                check_output(input, outputs);
           }
           else querie8(line2,buffer);
           break;

        case '9':
           if(checkTime==0){
                printf("Input %d [Query 9]: %fs ", input, time_query(querie9,line2,buffer));
                check_output(input, outputs);
           }
           else querie9(line2,buffer);
           break;
             
        default:
           break;
        }
  
    }

    fclose(File1);

}





int read_exe_queries_interativo(char *file){

    
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
           querie1(line,"command_output_interativo.txt");
           break;

        case '2':
           querie2(line,"command_output_interativo.txt");
           break;

        case '3':
           querie3(line,"command_output_interativo.txt");
           break;

        case '4':
           querie4(line,"command_output_interativo.txt");
           break;
           
        case '5':
           querie5(line,"command_output_interativo.txt");
           break;

        case '6':
           querie6(line,"command_output_interativo.txt");
           break;   

        case '7':
           querie7(line,"command_output_interativo.txt");
           break; 

        case '8':
           querie8(line,"command_output_interativo.txt");
           break; 

        case '9':
           querie9(line,"command_output_interativo.txt");
           break; 
             
        default:
           return 1;
           break;
        }
        
    return 0;
  
}