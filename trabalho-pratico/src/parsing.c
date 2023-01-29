#include "drivers_structure.h"
#include "users_structure.h"
#include "rides_structure.h"
#include <stdio.h>
#include "parsing.h"
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "func_auxiliares.h"


int n_linhas;
int n_linhas_drivers; 
int n_linhas_users; 
int n_linhas_gender;

void count_lines(char *drivers,char *users,char *rides){
  int d=0, u=0, r=0; 
  char line[1];
 
  FILE *file;
  file = fopen(drivers, "r");
  while (fgets(line, 1, file)!=NULL){
            d++;
        }
  fclose(file);

  file = fopen(users, "r");
  while (fgets(line, 1, file)!=NULL){
            u++;
        }
  fclose(file);

  file = fopen(rides, "r");
  while (fgets(line, 1, file)!=NULL){
             r++;
        }
  fclose(file);

  n_linhas=r*5;
  n_linhas_drivers=d*5; 
  n_linhas_users=u*5;
  n_linhas_gender=r/1000;
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
    int tamanho_info = 35;

    id=malloc(14);
    name=malloc(tamanho_info);
    birth_date=malloc(12);
    gender=malloc(3);
    car_class=malloc(10);
    license_plate=malloc(10);
    city=malloc(12);
    acc_creation=malloc(12);
    acc_status=malloc(10);
    acc_status[0]='!';

    sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", id,name,birth_date,gender,car_class,license_plate,city,acc_creation,acc_status);

    if(acc_status[0]=='!' || check_data(birth_date) ==1 || check_data(acc_creation) ==1 || check_account(acc_status)==1 || check_class(car_class)==1){
        free(id);
        free(name);
        free(birth_date);
        free(gender);
        free(car_class);
        free(license_plate);
        free(city);
        free(acc_status);       
        return;
    }
    free(license_plate);

    //Função que insere todos os parâmetros do driver(apenas do ficheiro drivers.csv) na hash table 
    insert_hash_drivers(id,name,birth_date,gender,converte(car_class),city,acc_creation,converte(acc_status));
}


// USERS /////////////////////////////////////

// Esta função é responsável pelo tratamento da linha, ou seja, é ela que tem o papel de
// ler cada parâmetro dos users definido na struct. Essa leitura é facilmente efetuada devido
// à existência dos ';' que separam todos os parâmetros. Em seguida, é necessário inserir
// todos os parâmetros relativos ao user (apenas do ficheiro users.csv) na hash table através 
// da função insert_hash_users.
void analisa_linha_users(char *line){
    char *username,*name,*gender,*birth_date,*acc_creation,*pay_method,*acc_status;
    int tamanho_info = 35;

    username=malloc(tamanho_info);
    name=malloc(tamanho_info);
    gender=malloc(3);
    birth_date=malloc(12);
    acc_creation=malloc(12);
    pay_method=malloc(12);
    acc_status=malloc(10);
    acc_status[0]='!';

    sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", username,name,gender,birth_date,acc_creation,pay_method,acc_status);

    if(acc_status[0]=='!' || check_data(birth_date) ==1 || check_account(acc_status)==1){
        free(username);
        free(name);
        free(gender);
        free(birth_date);
        free(acc_creation);
        free(pay_method);
        free(acc_status);
        return;
    }
    free(pay_method);

    //Função que insere todos os parâmetros do user (apenas do ficheiro users.csv) na hash table 
    insert_hash_users(username,name,gender,birth_date,acc_creation,converte(acc_status));


}



// RIDES //////////////////////////////////

// Esta função é responsável pelo tratamento da linha, ou seja, é ela que tem o papel de
// ler cada parâmetro dos rides definido na struct. Essa leitura é facilmente efetuada devido
// à existência dos ';' que separam todos os parâmetros. Em seguida, é necessário inserir
// todos os parâmetros relativos à ride (apenas do ficheiro rides.csv) nas hash tables através 
// das funções insert_rides_drivers e insert_rides_users.
void analisa_linha_rides(char *line){
    char *id,*date,*driver,*user,*city,*distance,*score_user,*score_driver,*tip,*ptr;
    int tamanho_info = 35;

    id=malloc(14);
    date=malloc(12);
    driver=malloc(14); 
    user=malloc(tamanho_info);
    city=malloc(12);
    distance=malloc(6);
    score_user=malloc(6);
    score_driver=malloc(6);
    tip=malloc(6);
    tip[0]='!';

    sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]", id,date,driver,user,city,distance,score_user,score_driver,tip);

    if(tip[0]=='!' || check_data(date) ==1 || check_distance(distance)==1 || check_score(score_user)==1 || check_score(score_driver)==1|| check_tip(tip)==1){
        free(id);
        free(date);
        free(driver);
        free(user);
        free(city);
        free(distance);
        free(score_user);
        free(score_driver);
        free(tip);
        return;
    }



    int distance_int = atoi(distance); 
    double score_user_double = atoi(score_user);
    double score_driver_double = atoi(score_driver);
    double tip_double = strtod(tip,&ptr);

    //Funções que inserem todos os parâmetros da ride (apenas do ficheiro rides.csv) nas hash tables 
    insert_hash_rides(id,date,driver,user,city,distance_int,score_user_double,score_driver_double,tip_double);
    insert_hash_rides_drivers(date,driver,score_driver_double);
    insert_hash_rides_users(distance_int,date,user);

    free(distance);
    free(score_user);
    free(score_driver);
    free(tip);
}

