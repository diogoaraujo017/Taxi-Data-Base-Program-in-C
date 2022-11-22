#include <stdio.h>
#include <string.h>
#include "queries.h"
#include "drivers_structure.h"
#include "rides_structure.h"
#include "users_structure.h"
#include <parsing_users.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

// Função responsável pela execução da querie 1.
void querie1(char *line,char *file){
    drivers *d;
    users *u;   

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries
    
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write
    

    if(line[0]=='0') {                                        // O input da querie é um id (corresponde a um driver)
        d = procura_hash_drivers(line);                       // Procura o driver na hash table dos users
        if(d!=NULL && (strcmp((converte(d->account_status)),"active")==0)){  // Verifica se o driver existe e tem a conta ativa
            drivers_q1 *d1 = procura_rides_drivers(line);                    // Procura o driver na hash table dos rides
            d1->avaliacao_media = d1->avaliacao_media/d1->numero_viagens;
            fprintf(NewFile,"%s;%c;%d;%.3f;%d;%.3f\n",d->name,d->gender,calculaIdade(d->birth_day),d1->avaliacao_media,d1->numero_viagens,d1->total_auferido);
        }
    }


    else {                                                    // O input da querie é um username (corresponde a um user)                    
        u = procura_hash_users(line);                         // Procura o driver na hash table dos users
        if(u!=NULL && (strcmp((converte(u->account_status)),"active")==0)){  // Verifica se o user existe e tem a conta ativa
            users_q1 *u1 = procura_rides_users(line);                        // Procura o user na hash table dos rides
            u1->avaliacao_media = u1->avaliacao_media/u1->numero_viagens;
            fprintf(NewFile,"%s;%c;%d;%.3f;%d;%.3f\n",u->name,u->gender,calculaIdade(u->birth_day),u1->avaliacao_media,u1->numero_viagens,u1->total_gasto);
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

    chdir("Resultados/");       // Esta função vai para a diretoria onde contêm a pasta resultados, 
                                // para que seja possível nela os ficheiros .txt de output das queries.
    FILE * NewFile;
    NewFile = fopen(file, "w");  // Abre o ficheiro .txt de modo a poder dar write.
    
    city_c1 *c1 = procura_rides_city(line);     // Procura o driver na hash table dos rides.
    if (c1->numero_viagens!=0){
        c1->custo = c1->custo/c1->numero_viagens;    // Calcula o custo medio da cidade, com base no numero de viagens feitas.
        fprintf(NewFile,"%.3f\n",c1->custo);
        }
    
    
    fclose(NewFile);            //Fecha o ficheiro criado
    chdir("trabalho-pratico");  // Volta à diretoria principal

}

// Função responsável pela execução da querie 5.
void querie5(char *line,char *file){}

// Função responsável pela execução da querie 6.
void querie6(char *line,char *file){

    char *a11= malloc(sizeof(line));   // City
    char *a22= malloc(sizeof(line));   // Data1 (mais antiga)
    char *a33= malloc(sizeof(line));   // Data2 (mais recente)

    int i=0;
    for (i=0;line[i]!=' ';i++){         // For loop que retira do input a cidade.
        a11[i]=line[i];
    }
    a11[i] = '\0';
    filtra(a11,a11);

    for (i=i+1;line[i]!=' ';i++){       // For loop que retira do input a primeira data.
        a22[i]=line[i];
    }
    a22[i] = '\0';
    filtra(a22,a22);

    for (i=i+1;line[i]!='\0';i++){      // For loop que retira do input a segunda data.
        a33[i]=line[i]; 
    }
    a33[i] = '\0';
    filtra(a33,a33);
    
    double dist=0;
    int cont;

    FILE *ridesF1;
    char line2[250];
    ridesF1 = fopen("rides.csv", "r");

    fgets(line2, 250, ridesF1);

    while (fgets(line2, 250, ridesF1)!=NULL){    // While loop que le as linhas do ficheiros de rides
       char *a,*a1,*a2,*a3,*a4,*a5;              // e que verifica se determinada ride foi feita na cidade
       int a6;                                   // fornecida e verifica se essa ride foi efetuada detro 
       a=malloc(sizeof(line2));                  // do intervalo fornecido.
       a1=malloc(sizeof(line2));
       a2=malloc(sizeof(line2));
       a3=malloc(sizeof(line2));
       a4=malloc(sizeof(line2));
       a5=malloc(sizeof(line2));
       int i,j;
       int aux=1;
       for(i=0,j=0;line2[i]!='\0';i++,j++){
           if (line2[i]==';'){

              a[j]='\0';

              switch (aux)
               {
                case 1:
                  filtra(a,a1);
                  break;
                case 2:    
                  filtra(a,a2);
                  break;
                case 3:
                  filtra(a,a3);
                  break;
                case 4:    
                  filtra(a,a4);
                  break;
                case 5:
                  filtra(a,a5);
                  break;
                case 6:    
                  a6 =atoi(a);
                  break;
                default:
                  break;
            }

              aux++;
              j=-1;
          }
          else a[j]=line2[i];
  
         }
         a[j-1]='\0';
         if((strncmp(a5, a11, MAX_INFO)==0) && calculaData(a22,a2)==0 && calculaData(a33,a2)==1){ // Se a ride foi feita na cidade e dentro das datas: 
                   dist += a6;                                                                    // Adiciona a distancia feita nessa ride;
                   cont++;                                                                        // Incrementa o contador do numero de viagens;
         }
       }

    fclose(ridesF1);
    
    chdir("Resultados/"); 

    FILE *NewFile;
    NewFile = fopen(file, "w");

    fprintf(NewFile,"%.3f\n",dist/cont);
                                                                   
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

        default:
           break;
        }
  
    }

    fclose(File1);

}