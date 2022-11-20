#include <stdio.h>
#include <string.h>
#include "queries.h"
#include "drivers_structure.h"
#include "rides_structure.h"
#include "users_structure.h"
#include <dirent.h>
#include <unistd.h>


// Função responsável pelo tratamento de dados relativo à querie 1
void querie1(char *line,char *file){

    drivers *d;
    users *u;   

    chdir("trabalho-pratico");  // Esta função retorna para a diretoria principal


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


// Função responsável pelo tratamento de dados relativo à querie 2
void querie2(char *n,char *file){}


// Função responsável pelo tratamento de dados relativo à querie 3
void querie3(char *line,char *file){}




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
    
        for(i=2;line[i]!='\0';i++){
            line2[i-2] = line[i];
        }

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

        default:
           break;
        }
  
    }
    fclose(File1);

}