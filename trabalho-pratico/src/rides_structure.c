#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rides_structure.h"
#include "users_structure.h"
#include "drivers_structure.h"
#include "parsing_rides.h"
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#define IDADE_DIA 9
#define IDADE_MES 10
#define IDADE_ANO 2022

// Hash Table das rides com a key dos drivers.
drivers_q1 *hash_rides_drivers[N_LINHASD];

// Hash Table das rides com a key dos users.
users_q1 *hash_rides_users[N_LINHASU];

// Hash Table das rides com a key das cities.
city_c1 *hash_rides_city[N_LINHASC];


// A função calculaData verifica se a data do primeiro input e mais recente que a  
// do segundo input.
int calculaData (char *line,char *line2){

    int dia1,mes1,ano1;
    int dia2,mes2,ano2;
    
    //Divide a datas em dia, mês e ano.
    dia1 = (line[0]-'0')*10+(line[1]-'0');
    mes1 = (line[3]-'0')*10+(line[4]-'0');
    ano1 = (line[6]-'0')*1000+(line[7]-'0')*100+(line[8]-'0')*10+(line[9]-'0');

    dia2 = (line2[0]-'0')*10+(line2[1]-'0');
    mes2 = (line2[3]-'0')*10+(line2[4]-'0');
    ano2 = (line2[6]-'0')*1000+(line2[7]-'0')*100+(line2[8]-'0')*10+(line2[9]-'0');
    
    //Da return a True se Data1 mais recente.
    if (ano1>ano2) return 0;
    else if (mes1>mes2) return 0;
    else if (dia1>dia2) return 0;
    
    //Da return a False se Data2 mais recente.
    return 1;
}


// A função calculaIdade calcula quantos anos passaram desde uma certa data.
int calculaIdade (char *line){

    int dia,mes,ano;
    int idade;
    
    //Divide a data em dia, mês e ano.
    dia = (line[0]-'0')*10+(line[1]-'0');
    mes = (line[3]-'0')*10+(line[4]-'0');
    ano = (line[6]-'0')*1000+(line[7]-'0')*100+(line[8]-'0')*10+(line[9]-'0');
    
    // Calcula a idade sem verificar se ele ja fez anos em 2022.
    idade = IDADE_ANO-ano-1;
    
    // Condição que verifica se a pessoa ja fez anos no ano 2022.
    if (mes<IDADE_MES || (mes==IDADE_MES && dia<=IDADE_DIA)){
        idade++;                                              
    }
    return idade;
}

// A função converte trasforma uma string que possa ter letras maiúsculas
// numa string com apenas letras minúsculas.
const char* converte(char *str){
    int i;
    
    for (i = 0; str[i] != '\0'; i++) {
        // Tranforma o carácter na posição i em minúsculo, caso ele seja maiúsculo.
        str[i] = tolower(str[i]);
    }
    return str;
}

// Associa um número da hash a cada linha criando uma key que mais tarde pode ser utilizada para
// procurar esse driver na hash table rides_drivers.
unsigned int hash_drivers_rides(char *id){
    int comp = strnlen(id,MAX_INFO);
    unsigned int num_hash = 0;
    for (int i = 0; i < comp; i++)
    {
        num_hash += id[i];
        num_hash = (num_hash * id[i]) % N_LINHASD;
    }
    return num_hash;
}

// Associa um número da hash a cada linha criando uma key que mais tarde pode ser utilizada para
// procurar esse user na hash table rides_users.
unsigned int hash_user_rides(char *user){
    int comp = strnlen(user,MAX_INFO);
    unsigned int num_hash = 0;
    for (int i = 0; i < comp; i++)
    {
        num_hash += user[i];
        num_hash = (num_hash * user[i]) % N_LINHASU;
    }
    return num_hash;
}

// Associa um número da hash a cada linha criando uma key que mais tarde pode ser utilizada para
// procurar esse user na hash table rides_city.
unsigned int hash_city_rides(char *city){
    int comp = strnlen(city,MAX_INFO);
    unsigned int num_hash = 0;
    for (int i = 0; i < comp; i++)
    {
        num_hash += city[i];
        num_hash = (num_hash * city[i]) % N_LINHASC;
    }
    return num_hash;
}

// Esta função inicia a hash table rides_drivers com os tamanho respetivos, colocando todas as
// suas linhas a NULL. Fazemos isto, para quando existirem colisões, estas não serem um problema.
void init_hash_rides_drivers(){
    for (int i = 0; i < N_LINHASD; i++)
    {
        hash_rides_drivers[i] = NULL;
    }   
}

// Esta função inicia a hash table rides_users com os tamanho respetivos, colocando todas as
// suas linhas a NULL. Fazemos isto, para quando existirem colisões, estas não serem um problema.
void init_hash_rides_users(){
    for (int i = 0; i < N_LINHASU; i++)
    {
        hash_rides_users[i] = NULL; 
    }   
}

// Esta função inicia a hash table city com os tamanho respetivos, colocando todas as
// suas linhas a NULL. Fazemos isto, para quando existirem colisões, estas não serem um problema.
void init_hash_rides_city(){
    for (int i = 0; i < N_LINHASC; i++)
    {
        hash_rides_city[i] = NULL; 
    }   
}


// A função insert_rides_drivers insere uma struct drivers_q1 na hash table rides_drivers.
bool insert_rides_drivers(char *id,char *dt,char *dr,char *u,char *ac,int dist,int su,int sd,double tip,char *cm){
    // Procura o driver na hash tables dos drivers para obtermos o modelo do carro.
    drivers d = *procura_hash_drivers(dr);
    // Cria uma struct drivers_q1 e atualiza os valores para inserirmos na hash tables rides_drivers.
    drivers_q1 *d1 = malloc(sizeof(drivers_q1));
    d1->id = dr;
    d1->date = dt;
    d1->avaliacao_media = (double) sd;
    d1->numero_viagens = 1;
    // Verifica o tipo de carro do driver e calcula quanto ganhou com base na distancia e a tip que o user deu.
    if ((strcmp(converte(d.car_class),"basic"))==0) d1->total_auferido = 3.25 + 0.62*dist + tip;
    else if ((strcmp(converte(d.car_class),"green"))==0) d1->total_auferido = 4.00 + 0.79*dist + tip;
    else if ((strcmp(converte(d.car_class),"premium"))==0) d1->total_auferido = 5.20 + 0.94*dist + tip;
    // Calcula a key atraves do id do driver.
    int aux = hash_drivers_rides(dr);
    for (int i=0;i < N_LINHASD;i++){
        // Calcula uma das keys possíveis.
        int next_position = (i + aux) % N_LINHASD;
        // Verifica se nessa posição tem algum driver.
        if (hash_rides_drivers[next_position] == NULL){
            // Se nao tiver insere o nosso drivers_q1 nessa posição
            // e da return a true para terminar a função. 
            hash_rides_drivers[next_position] = d1;
            return true;
        }
        // Verifica se o driver que esta nessa posição na hash table e o que estamos a tentar inserir são iguais.
        // Se for o driver que estamos a procura a função vai actualizar os parâmetros da struct drivers_q1 que
        // se encontra na hash table.
        if(strcmp(hash_rides_drivers[next_position]->id,dr)==0) {
            // Se a data da ride atual for mais recente que a que esta na hash table vamos atualizar a hash table.
            if((calculaData(d1->date,hash_rides_drivers[next_position]->date)==0)) hash_rides_drivers[next_position]->date = d1->date;
            // Atualiza os restantes parâmetros.
            hash_rides_drivers[next_position]->avaliacao_media += sd;
            hash_rides_drivers[next_position]->numero_viagens += 1;
            hash_rides_drivers[next_position]->total_auferido += d1->total_auferido;
            // Da return a true para terminar a execução da função.
            return true;
        }
    }
    return false;
}

// A função insert_rides_users insere uma struct users_q1 na hash table rides_users.
bool insert_rides_users(char *id,char *dt,char *dr,char *user,char *ac,int dist,int su,int sd,double tip,char *cm){
    // Procura o driver na hash tables dos drivers para obtermos o modelo do carro.
    drivers d = *procura_hash_drivers(dr);
    // Cria uma struct users_q1 e atualiza os valores para inserirmos na hash tables rides_users.
    users_q1 *u1 = malloc(sizeof(users_q1));
    u1->username = user;
    u1->date = dt;
    u1->avaliacao_media = (double) su;
    u1->numero_viagens = 1;
    // Verifica o tipo de carro do driver e calcula quanto gastou o user com base na distancia e a tip que deu.
    if ((strcmp(converte(d.car_class),"basic"))==0) u1->total_gasto = 3.25 + 0.62*dist + tip;
    else if ((strcmp(converte(d.car_class),"green"))==0) u1->total_gasto = 4.00 + 0.79*dist + tip;
    else if ((strcmp(converte(d.car_class),"premium"))==0) u1->total_gasto = 5.20 + 0.94*dist + tip;
    // Calcula a key atraves do username do user.
    int aux = hash_user_rides(user);
    for (int i=0;i < N_LINHASU;i++){
        // Calcula uma das keys possíveis.
        int next_position = (i + aux) % N_LINHASU;
        // Verifica se nessa posição tem algum user.
        if (hash_rides_users[next_position] == NULL){
            // Se nao tiver insere o nosso users_q1 nessa posição
            // e da return a true para terminar a função. 
            hash_rides_users[next_position] = u1;
            return true;
        }
        // Verifica se o user que esta nessa posição na hash table e o que estamos a tentar inserir são iguais.
        // Se for o user que estamos a procura a função vai actualizar os parâmetros da struct users_q1 que
        // se encontra na hash table.
        if(strcmp(hash_rides_users[next_position]->username,user)==0) {
            // Se a data da ride atual for mais recente que a que esta na hash table vamos atualizar a hash table.
            if((calculaData(u1->date,hash_rides_users[next_position]->date)==0)) hash_rides_users[next_position]->date = u1->date;
            // Atualiza os restantes parâmetros.
            hash_rides_users[next_position]->avaliacao_media += su;
            hash_rides_users[next_position]->numero_viagens += 1;
            hash_rides_users[next_position]->total_gasto += u1->total_gasto;
            // Da return a true para terminar a execução da função.
            return true;
        }
    }
    return false;
}

// A função insert_rides_city insere uma struct city_c1 na hash table rides_users.
bool insert_rides_city(char *id,char *dt,char *dr,char *user,char *c,int dist,int su,int sd,double tip,char *cm){
    // Procura o driver na hash tables dos drivers para obtermos o modelo do carro.
    drivers d = *procura_hash_drivers(dr);
    // Cria uma struct users_q1 e atualiza os valores para inserirmos na hash tables rides_users.
    city_c1 *c1 = malloc(sizeof(city_c1));
    c1->city = c;
    c1->numero_viagens = 1;
    // Verifica o tipo de carro do driver e calcula quanto gastou o user com base na distancia e a tip que deu.
    if ((strcmp(converte(d.car_class),"basic"))==0) c1->custo = 3.25 + 0.62*dist;
    else if ((strcmp(converte(d.car_class),"green"))==0) c1->custo = 4.00 + 0.79*dist;
    else if ((strcmp(converte(d.car_class),"premium"))==0) c1->custo = 5.20 + 0.94*dist;
    // Calcula a key atraves do username do user.
    int aux = hash_city_rides(c);
    for (int i=0;i < N_LINHASC;i++){
        // Calcula uma das keys possíveis.
        int next_position = (i + aux) % N_LINHASC;
        // Verifica se nessa posição tem algum user.
        if (hash_rides_city[next_position] == NULL){
            // Se nao tiver insere o nosso users_q1 nessa posição
            // e da return a true para terminar a função. 
            hash_rides_city[next_position] = c1;
            return true;
        }
        // Verifica se o user que esta nessa posição na hash table e o que estamos a tentar inserir são iguais.
        // Se for o user que estamos a procura a função vai actualizar os parâmetros da struct users_q1 que
        // se encontra na hash table.
        if(strcmp(hash_rides_city[next_position]->city,c)==0)  {
            // Atualiza os restantes parâmetros.
            hash_rides_city[next_position]->numero_viagens ++;
            hash_rides_city[next_position]->custo += c1->custo;
            // Da return a true para terminar a execução da função.
            return true;
        }
    }
    return false;
}



// Procura um determinado id na hash table rides_drivers. Esta função é bastante rápida a executar, mesmo
// existindo muitas linhas de hash, devido à existência de keys que estão associadas, uma a cada
// input colocado na hash table. Se encontrar a função dará return à linha da hash correspondente
// em forma de struct, caso contrário dará return a NULL.
drivers_q1 *procura_rides_drivers(char *id){
    int aux = hash_drivers_rides(id);
    for (int i = 0; i < N_LINHASD; i++){                                         
        // Calcula uma das keys possíveis.
        int next_position = (i + aux) % N_LINHASD;                              
        // Verifica se o driver que esta nessa posição na hash table e o que estamos a procura são iguas.
        if (strncmp(hash_rides_drivers[next_position]->id, id, MAX_INFO)==0){    
            return hash_rides_drivers[next_position];
        }
    }
    // Return a NULL se não encontrar o user na hash table.
    return NULL;
}

// Procura um determinado username na hash table rides_users. Esta função é bastante rápida a executar, mesmo
// existindo muitas linhas de hash, devido à existência de keys que estão associadas, uma a cada
// input colocado na hash table. Se encontrar a função dará return à linha da hash correspondente
// em forma de struct, caso contrário dará return a NULL.
users_q1 *procura_rides_users(char *username){
    int aux = hash_user_rides(username);
    for (int i = 0; i < N_LINHASU; i++){
        // Calcula uma das keys possíveis.
        int next_position = (i + aux) % N_LINHASU;
        // Verifica se o user que esta nessa posição da hash table e o que estamos a procura são iguais.
        if (strncmp(hash_rides_users[next_position]->username, username, MAX_INFO)==0){ 
            return hash_rides_users[next_position];
        }
    }
    // Return a NULL se não encontrar o user na hash table.
    return NULL;                                                                        
}

// Procura um determinado username na hash table city. Esta função é bastante rápida a executar, mesmo
// existindo muitas linhas de hash, devido à existência de keys que estão associadas, uma a cada
// input colocado na hash table. Se encontrar a função dará return à linha da hash correspondente
// em forma de struct, caso contrário dará return a NULL.
city_c1 *procura_rides_city(char *city){
    int aux = hash_city_rides(city);
    for (int i = 0; i < N_LINHASC; i++){
        // Calcula uma das keys possíveis.
        int next_position = (i + aux) % N_LINHASC;
        // Verifica se a info que esta nessa posição da hash table e o que estamos a procura são iguais.
        if (strncmp(hash_rides_city[next_position]->city, city, MAX_INFO)==0){ 
            return hash_rides_city[next_position];
        }
    }
    // Return a NULL se não encontrar o user na hash table.
    return NULL;                                                                        
}




