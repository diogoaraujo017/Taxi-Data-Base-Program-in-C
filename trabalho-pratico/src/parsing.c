#include "drivers_structure.h"
#include "users_structure.h"
#include "rides_structure.h"
#include <stdio.h>
#include "parsing.h"
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


// Esta função copia uma string (init) para outra (dest) com um tamanho menor que a primeira.
// Isto acontece, porque a string dest é finalizada quando encontra o primeiro '\0', cortando 
// o tamanho substancialmente.
char* filtra(char *init,char *dest){
    int i;
    for(i=0;init[i]!='\0';i++){
        dest[i]=init[i];
    }
    dest[i]='\0';
    return dest;
}




// Esta função é responsável pelo parsing do ficheiro drivers.csv. Funciona da seguinte forma:
// É aberto o fichero drivers.csv e em seguida é lida linha a linha do ficheiro e colocada na função
// analisa_linha_drivers para um melhor tratamento dos dados.
void read_store(char *dir, char file_aux){
    FILE *file;
    char line[250];
    file = fopen(dir, "r");

    fgets(line, 250, file);

    if (file_aux == 'd'){
        while (fgets(line, 250, file)!=NULL){
            analisa_linha_drivers(line);
        }
    }
    else if (file_aux == 'u'){
        while (fgets(line, 250, file)!=NULL){
            analisa_linha_users(line);
        }
    }
    else if (file_aux == 'r'){
        while (fgets(line, 250, file)!=NULL){
            analisa_linha_rides(line);
        }
    }

    fclose(file);
}



// DRIVERS //////////////////////////////////////////////////


// Esta função é responsável pelo tratamento da linha, ou seja, é ela que tem o papel de
// ler cada parâmetro dos drivers definido na struct. Essa leitura é facilmente efetuada devido
// à existência dos ';' que separam todos os parâmetros. Em seguida, é necessário inserir
// todos os parâmetros relativos ao driver (apenas do ficheiro drivers.csv) na hash table através 
// da função insert_hash_drivers.
void analisa_linha_drivers(char *line){
    char *id,*name,*birth_date,*gender,*car_class,*license_plate,*city,*acc_creation,*acc_status;

    id=malloc(sizeof(line));
    name=malloc(sizeof(line));
    birth_date=malloc(sizeof(line));
    gender=malloc(sizeof(line));
    car_class=malloc(sizeof(line));
    license_plate=malloc(sizeof(line));
    city=malloc(sizeof(line));
    acc_creation=malloc(sizeof(line));
    acc_status=malloc(sizeof(line));

    

    sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", id,name,birth_date,gender,car_class,license_plate,city,acc_creation,acc_status);


    //Função que insere todos os parâmetros do driver(apenas do ficheiro drivers.csv) na hash table 
    insert_hash_drivers(id,name,birth_date,gender[0],car_class,license_plate,city,acc_creation,acc_status);

}




// USERS /////////////////////////////////////


// Esta função é responsável pelo tratamento da linha, ou seja, é ela que tem o papel de
// ler cada parâmetro dos users definido na struct. Essa leitura é facilmente efetuada devido
// à existência dos ';' que separam todos os parâmetros. Em seguida, é necessário inserir
// todos os parâmetros relativos ao user (apenas do ficheiro users.csv) na hash table através 
// da função insert_hash_users.
void analisa_linha_users(char *line){
    char *username,*name,*gender,*birth_date,*acc_creation,*pay_method,*acc_status;

    username=malloc(sizeof(line));
    name=malloc(sizeof(line));
    gender=malloc(sizeof(line));
    birth_date=malloc(sizeof(line));
    acc_creation=malloc(sizeof(line));
    pay_method=malloc(sizeof(line));
    acc_status=malloc(sizeof(line));

    sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", username,name,gender,birth_date,acc_creation,pay_method,acc_status);

    //Função que insere todos os parâmetros do user (apenas do ficheiro users.csv) na hash table 
    insert_hash_users(username,name,gender[0],birth_date,acc_creation,pay_method,acc_status);
}
















//RIDES //////////////////////////////////




// Esta função é responsável pelo tratamento da linha, ou seja, é ela que tem o papel de
// ler cada parâmetro dos rides definido na struct. Essa leitura é facilmente efetuada devido
// à existência dos ';' que separam todos os parâmetros. Em seguida, é necessário inserir
// todos os parâmetros relativos à ride (apenas do ficheiro rides.csv) nas hash tables através 
// das funções insert_rides_drivers e insert_rides_users.
void analisa_linha_rides(char *line){
    char *id,*date,*driver,*user,*city,*distance,*score_user,*score_driver,*tip;

    id=malloc(sizeof(line));
    date=malloc(sizeof(line));
    driver=malloc(sizeof(line));
    user=malloc(sizeof(line));
    city=malloc(sizeof(line));
    distance=malloc(sizeof(line));
    score_user=malloc(sizeof(line));
    score_driver=malloc(sizeof(line));
    tip=malloc(sizeof(line));
    char *ptr;


    sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]", id,date,driver,user,city,distance,score_user,score_driver,tip);

    int distance_int = atoi(distance);
    int score_user_int = atoi(score_user);
    int score_driver_int = atoi(score_driver);
    double tip_double =strtod(tip,&ptr);

    //Funções que inserem todos os parâmetros da ride (apenas do ficheiro rides.csv) nas hash tables 
    insert_rides_drivers(id,date,driver,user,city,distance_int,score_user_int,score_driver_int,tip_double,"comment");
    insert_rides_users(id,date,driver,user,city,distance_int,score_user_int,score_driver_int,tip_double,"comment");
    insert_rides_city(id,date,driver,user,city,distance_int,score_user_int,score_driver_int,tip_double,"comment");
}

