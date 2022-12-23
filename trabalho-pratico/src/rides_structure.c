#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rides_structure.h"
#include "users_structure.h"
#include "drivers_structure.h"
#include "parsing.h"
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#define IDADE_DIA 9
#define IDADE_MES 10
#define IDADE_ANO 2022


// Hash Table das rides com a key das rides.
rides *hash_rides[N_LINHAS];

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

int calculaData2 (int dia,int mes,int ano,char *line2, int key){

    int dia2,mes2,ano2;

    dia2 = (line2[0]-'0')*10+(line2[1]-'0');
    mes2 = (line2[3]-'0')*10+(line2[4]-'0');
    ano2 = (line2[6]-'0')*1000+(line2[7]-'0')*100+(line2[8]-'0')*10+(line2[9]-'0');
    
    //Da return a True se Data1 mais recente.
    if(key == 1){
    if (ano>ano2) return 0;
    else if (mes>mes2) return 0;
    else if (dia>dia2) return 0;
    }
    else {
        if (ano<ano2) return 0;
        else if (mes<mes2) return 0;
        else if (dia<dia2) return 0;
    }
    
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

// Esta função inicia a hash table das rides com os tamanho respetivos, colocando todas as
// suas linhas a NULL. Fazemos isto, para quando existirem colisões, estas não serem um problema.
void init_hash_rides(){
    for (int i = 0; i < N_LINHAS; i++)
    {
        hash_rides[i] = NULL; 
    }   
}

bool insert_hash_rides(char *id,char *dt,char *dr,char *user,char *c,int dist,int su,int sd,double tip){
    rides *r = malloc(sizeof(rides));
    r->id=id;
    r->date=dt;
    r->driver=dr;
    r->user=user;
    r->city=c;
    r->distance=dist;
    r->score_user=su;
    r->score_driver=sd;
    r->tip=tip;   
    
    if ((hash_rides[atoi(id)-1] == NULL)){
            hash_rides[atoi(id)-1] = r;
            return true;
        }
    return false;
}

// Procura um determinado username na hash table city. Esta função é bastante rápida a executar, mesmo
// existindo muitas linhas de hash, devido à existência de keys que estão associadas, uma a cada
// input colocado na hash table. Se encontrar a função dará return à linha da hash correspondente
// em forma de struct, caso contrário dará return a NULL.
rides *procura_rides(int id){
    if(id>=0 && id<1000001){ 
        return hash_rides[id];
        }
    // Return a NULL se não encontrar o user na hash table.
    return NULL;                                                                        
}




