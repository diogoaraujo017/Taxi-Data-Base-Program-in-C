#include <stdio.h>
#include <string.h>
#include "queries.h"
#include "drivers_structure.h"
#include "rides_structure.h"
#include "users_structure.h"
#include <dirent.h>

void querie1(char line[],char *file){

    drivers *d;
    users *u;   

    FILE * NewFile;
    NewFile = fopen(file, "w");
    //DIR* dir = opendir("Resultados/.");

    if(line[0]=='0') {        
        d = procura_hash_drivers(line);
        if(d!=NULL && strcmp(converte(d->account_status),"active")){
            drivers_q1 d1 = calcula_hash_rides_drivers(d->id);
            fprintf("%s;%c;%d;%.3f;%d;%.3f\n",d1.name,d1.gender,d1.age,d1.avaliacao_media,d1.numero_viagens,d1.total_auferido);
        }
    }
    else {                      
        u = procura_hash_users(line);
        if(u!=NULL && strcmp(converte(u->account_status),"active")){
            users_q1 u1 = calcula_hash_rides_users(u->name);
            fprintf("%s;%c;%d;%.3f;%d;%.3f\n",u1.name,u1.gender,u1.age,u1.avaliacao_media,u1.numero_viagens,u1.total_gasto);
        }
    }     
    fclose(NewFile);
    //closedir(dir);
}

void querie2(char line[],char *file){}

void querie3(char line[],char *file){}

void read_exe_queries(char *file){

    FILE* File1;
    File1 = fopen("tests.txt","r");
    char line[100],line2[100];
    char querie;
    int i;
    
    while(fgets(line, 150, File1)!=NULL){

        int x=0;
        x++;
        char buffer [50];
        snprintf(buffer, sizeof (buffer), "command%d_output.txt",x);


        querie = line[0];
    
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