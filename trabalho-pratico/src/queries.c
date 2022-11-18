#include <stdio.h>
#include <string.h>
#include "queries.h"
#include "drivers_structure.h"
#include "rides_structure.h"
#include "users_structure.h"
#include <dirent.h>

void querie1(char line[100],FILE* file){
    drivers *d;
    users *u;   

    DIR* dir = opendir("Resultados");

    if(line[0]=='0') {        
        d = procura_hash_drivers(line);
        if(d!=NULL && strcmp(converte(d->account_status),"active")){
            drivers_q1 d1 = calcula_hash_rides_drivers(d->id);
            printf("%s;%c;%d;%.3f;%d;%.3f\n",d1.name,d1.gender,d1.age,d1.avaliacao_media,d1.numero_viagens,d1.total_auferido);
        }
    }
    else {                      
        u = procura_hash_users(line);
        if(u!=NULL && strcmp(converte(u->account_status),"active")){
            users_q1 u1 = calcula_hash_rides_users(u->name);
            printf("%s;%c;%d;%.3f;%d;%.3f\n",u1.name,u1.gender,u1.age,u1.avaliacao_media,u1.numero_viagens,u1.total_gasto);
        }
    }     
    fclose(file);
    closedir(dir);                 
}

void querie2(char line[100],FILE* file){}

void querie3(char line[100],FILE* file){}

void read_exe_queries(char const *argv){

    char line[100],line2[100];
    int querie,i;
    
    while(fgets(line, 100, stdin)!=NULL){

        int x=0;
        x++;
        char buffer [50];
        snprintf(buffer, sizeof (buffer), "command%d_output.txt",x);

        FILE * NewFile;
        NewFile = fopen(buffer, "w");

        querie = line[0];
    
        for(i=2;line[i]!='\0';i++){
            line2[i-2] = line[i];
        }

        line2[i] = '\0';

        switch (querie)
        {
        case '1':
           querie1(line2,NewFile);
           break;

        case '2':
           querie2(line2,NewFile);
           break;

        case '3':
           querie3(line2,NewFile);
           break;

        default:
           break;
        }
  
    }

}