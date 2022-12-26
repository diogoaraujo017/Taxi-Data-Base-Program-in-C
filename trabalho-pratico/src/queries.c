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

// Função responsável pela execução da querie 1.
void querie1(char *line,char *file){
    drivers *d,*d1;
    users *u;  
    rides *r,*r1; 
    int i,numero_viagens=0;
    double carType[2];
    double avaliacao_media=0.000,total_auferido=0.000,total_gasto=0.000;

    
    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write
    

    if(line[0]=='0') {                                        // O input da querie é um id (corresponde a um driver)
        d = procura_hash_drivers(line);                       // Procura o driver na hash table dos users
        if(d!=NULL && (strcmp((converte(d->account_status)),"active")==0)){  // Verifica se o driver existe e tem a conta ativa
            
            if ((strcmp(converte(d->car_class),"basic"))==0) {carType[0]=3.25;carType[1]=0.62;}
            else if ((strcmp(converte(d->car_class),"green"))==0) {carType[0]=4.00;carType[1]=0.79;}
            else if ((strcmp(converte(d->car_class),"premium"))==0) {carType[0]=5.20;carType[1]=0.94;}
            
            for(i=0;i<N_LINHAS;i++){
                 r = procura_rides(i);
                 if(strcmp(r->driver,line)==0){
                     avaliacao_media += r->score_driver;
                     numero_viagens++;
                     total_auferido += carType[0] + carType[1]*r->distance + r->tip;
                 }
               }
            fprintf(NewFile,"%s;%c;%d;%.3f;%d;%.3f\n",d->name,d->gender,calculaIdade(d->birth_day),avaliacao_media/numero_viagens,numero_viagens,total_auferido);
        }
    }


    else {                                                  // O input da querie é um username (corresponde a um user)                    
        u = procura_hash_users(line);                         // Procura o driver na hash table dos users
        if(u!=NULL && (strcmp((converte(u->account_status)),"active")==0)){  // Verifica se o user existe e tem a conta ativa
            
            for(i=0;i<N_LINHAS;i++){
                 r1 = procura_rides(i);
                 
                 if(strcmp(r1->user,line)==0){
                     d1 = procura_hash_drivers(r1->driver);
                     if ((strcmp(converte(d1->car_class),"basic"))==0) total_gasto += 3.25 + 0.62*r1->distance + r1->tip;
                     else if ((strcmp(converte(d1->car_class),"green"))==0) total_gasto += 4.00 + 0.79*r1->distance + r1->tip;
                     else if ((strcmp(converte(d1->car_class),"premium"))==0) total_gasto += 5.20 + 0.94*r1->distance + r1->tip;

                     avaliacao_media += r1->score_user;
                     numero_viagens++;
                     
                 }
               }
         
         fprintf(NewFile,"%s;%c;%d;%.3f;%d;%.3f\n",u->name,u->gender,calculaIdade(u->birth_day),avaliacao_media/numero_viagens,numero_viagens,total_gasto);
        }
    }     

    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 2.
void querie2(char *n,char *file){}

// Função responsável pela execução da querie 3.
void querie3(char *line,char *file){}

// Função responsável pela execução da querie 4.
void querie4(char *line,char *file){
    rides *r;
    drivers *d;
    double preco_medio=0.000;
    int i, numero_viagens=0;

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries.
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write.
    
     for(i=0;i<N_LINHAS;i++){
                 r = procura_rides(i);
                 
                 if(strcmp(r->city,line)==0){
                     d = procura_hash_drivers(r->driver);
                     
                     if ((strcmp(converte(d->car_class),"basic"))==0) preco_medio += 3.25 + 0.62*r->distance;
                     else if ((strcmp(converte(d->car_class),"green"))==0) preco_medio += 4.00 + 0.79*r->distance;
                     else if ((strcmp(converte(d->car_class),"premium"))==0) preco_medio += 5.20 + 0.94*r->distance;
                     
                     numero_viagens++;
                     
                 }
               }
            
        fprintf(NewFile,"%.3f\n",preco_medio/numero_viagens);
        
        fclose(NewFile);            //Fecha o ficheiro criado
        chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 5.
void querie5(char *line,char *file){
    rides *r;
    drivers *d;
    double preco_medio=0.000;
    int i,numero_viagens=0;
    char data1[10],data2[10];

    strncpy(data1,line,10);
    strncpy(data2,line+11,10);

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries.
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write.
    
     for(i=0;i<N_LINHAS;i++){
                 r = procura_rides(i);
                 
                 if((calculaData(r->date,data1)==0) && (calculaData(r->date,data2)==1)){
                     d = procura_hash_drivers(r->driver);
                     
                     if ((strcmp(converte(d->car_class),"basic"))==0) preco_medio += 3.25 + 0.62*r->distance;
                     else if ((strcmp(converte(d->car_class),"green"))==0) preco_medio += 4.00 + 0.79*r->distance;
                     else if ((strcmp(converte(d->car_class),"premium"))==0) preco_medio += 5.20 + 0.94*r->distance;
                     
                     numero_viagens++;
                     
                 }
               }

        preco_medio = preco_medio/numero_viagens;    
        fprintf(NewFile,"%.3f\n",preco_medio);
        
        fclose(NewFile);            //Fecha o ficheiro criado
        chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 6.
void querie6(char *line,char *file){
    
    rides *r;
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
    
     for(i=0;i<N_LINHAS;i++){
                 r = procura_rides(i);
                 
                 if((strcmp(r->city,cidade)==0) && (calculaData(r->date,data1)==0) && (calculaData(data2,r->date)==0)){
                     dist += r->distance;
                     numero_viagens++;
                 }
               }

        if(dist==0) fprintf(NewFile,"0.000");
        else fprintf(NewFile,"%.3f\n",dist/numero_viagens);
        
        fclose(NewFile);            //Fecha o ficheiro criado
        chdir("trabalho-pratico");  // Volta à diretoria principal
}

// Função responsável pela execução da querie 7.
void querie7(char *line,char *file){}

// Função responsável pela execução da querie 8.
void querie8(char *line,char *file){}

// Função responsável pela execução da querie 9.
void querie9(char *line,char *file){}

// Função responsável pela abertura e leitura do ficheiro .txt relativo aos inputs das
// queries. Esta função a cada linha que lê, envia o input para uma das funções relativas
// às queries para futuro tratamento dos dados.
void read_exe_queries(char *file){

    // Leitura do ficheiro .txt de modo a recebemos os seus inputs para as queries
    FILE* File1;
    File1 = fopen(file,"r");
    
    char line[150],line2[150];
    char querie;
    int i,x=0;
    
    // Leitura das várias linhas do ficheiro .txt e redirecionamento para a sua querie correspondente
    while(fgets(line, 150, File1)!=NULL){

        x++;
        char buffer [50];

        // Esta função é responsável pela criação de N ficheiros de texto .txt com o intuito de 
        // serem escritos com o output correspondente à querie em questão. Os ficheiros terão o nome
        // commandX_output.txt
        snprintf(buffer, sizeof (buffer), "command%d_output.txt",x);


        querie = line[0];       // O primeiro dígito da linha é o número da querie correspondente
    
        for(i=2;line[i]!='\0';i++){         // Este for loop faz a distinção do resto do input
            line2[i-2] = line[i];           // para mais tarde ser fornecido as funções que 
        }                                   // executam as queries.

        line2[i-3] = '\0';

        switch (querie)
        {
        case '1':
           querie1(line2,buffer);
           break;

        case '2':
           querie2(line2,buffer);
           break;

        case '3':
           querie3(line2,buffer);
           break;

        case '4':
           querie4(line2,buffer);
           break;
           
        case '5':
           querie5(line2,buffer);
           break;

        case '6':
           querie6(line2,buffer);
           break;   

        default:
           break;
        }
  
    }

    fclose(File1);

}