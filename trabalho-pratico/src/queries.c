#include <stdio.h>
#include <string.h>
#include "queries.h"
#include "drivers_structure.h"
#include "rides_structure.h"
#include "users_structure.h"

void querie1(char line[100]){
    drivers *d;
    users *u;   
    
    if(line[0]=='0') {        
        d = procura_hash_drivers(line);
        if(d!=NULL && d->account_status=="active") {

        }
    }
    else {                      
        u = procura_hash_users(line);
        if(u!=NULL && u->account_status=="active") {

        }
    }                      
}
void querie2(char line[100])
{
   
}

void querie3(char line[100])
{
  
}

void read_exe_queries(char const *argv){

    char line[100],line2[100];
    int querie,i;
    
    while(fgets(line, 100, stdin)!=NULL){
    
    querie = line[0];
    
    for(i=2;line[i]!='/0';i++){
        line2[i-2] = line[i];
    }
    line2[i] = '\0';

    switch (querie)
    {
    case '1':
        querie1(line2);
        break;

    case '2':
        querie2(line2);
        break;

    case '3':
        querie3(line2);
        break;

    default:
        break;
    }
  
  }

}