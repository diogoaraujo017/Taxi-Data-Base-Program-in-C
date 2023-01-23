#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "func_auxiliares.h"
#include <ctype.h>


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
    if (ano1==ano2 && mes1>mes2) return 0;
    if (ano1==ano2 && mes1==mes2 && dia1>dia2) return 0;

    if (ano1==ano2 && mes1==mes2 && dia1==dia2) return (-1);


    
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
char* converte(char *str){
    int i;
    
    for (i = 0; str[i] != '\0'; i++) {
        // Tranforma o carácter na posição i em minúsculo, caso ele seja maiúsculo.
        str[i] = tolower(str[i]);
    }
    return str;
}







int check_data(char *date){
    if(strlen(date)!=10) return 1;

    if(!isdigit(date[0]) || !isdigit(date[1]) || date[2]!='/' || !isdigit(date[3]) || !isdigit(date[4]) || date[5]!='/' ||
       !isdigit(date[6]) || !isdigit(date[7]) || !isdigit(date[8]) || !isdigit(date[9])){
        return 1;
    }

    char dia[3]; dia[0]=date[0]; dia[1]=date[1] ; dia[2]='\0';
    char mes[3]; mes[0]=date[3]; mes[1]=date[4] ; mes[2]='\0';

    if(atoi(dia)<1 || atoi(dia)>31 || atoi(mes)<1 || atoi(mes)>12) return 1;

    return 0;
}

int check_distance(char *distance){
    register int i;
    int n_digitos=strlen(distance);

    for(i=0;i<n_digitos;i++){
        if (!isdigit(distance[i])) return 1; 
    }
   
    if(n_digitos==1 && distance[0]=='0') return 1;

    return 0;
}

int check_score(char *score){
    register int i;
    int n_digitos=strlen(score);
    if(n_digitos==1 && score[0]=='0') return 1;
    for(i=0;i<n_digitos;i++){
        if(!isdigit(score[i])) return 1;
    }

    return 0;
}

int check_tip(char *tip){
    register int i;
    int n_digitos=strlen(tip);
    for(i=0;i<n_digitos;i++){
        if((!isdigit(tip[i])) && tip[i]!='.') return 1;
    }

    return 0;
}

int check_account(char* status){
    if(strcmp(converte(status),"active")!=0 && strcmp(converte(status),"inactive")!=0) return 1;
    return 0;
}

int check_class(char *car){
    if(strcmp(converte(car),"basic")!=0 && strcmp(converte(car),"green")!=0 && strcmp(converte(car),"premium")!=0) return 1;
    return 0;
}

