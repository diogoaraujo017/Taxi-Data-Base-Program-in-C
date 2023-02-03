#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "func_auxiliares.h"
#include <ctype.h>
#include <time.h>
#include <unistd.h>

// Função responsável por comparar duas datas
int calculateData (char *line,char *line2){

    int day1,month1,year1;
    int day2,month2,year2;
    
    //Divide a datas em dia, mês e ano.
    day1 = (line[0]-'0')*10+(line[1]-'0');
    month1 = (line[3]-'0')*10+(line[4]-'0');
    year1 = (line[6]-'0')*1000+(line[7]-'0')*100+(line[8]-'0')*10+(line[9]-'0');

    day2 = (line2[0]-'0')*10+(line2[1]-'0');
    month2 = (line2[3]-'0')*10+(line2[4]-'0');
    year2 = (line2[6]-'0')*1000+(line2[7]-'0')*100+(line2[8]-'0')*10+(line2[9]-'0');
    
    //Da return a True se Data1 mais recente.
    if (year1>year2) return 0;
    if (year1==year2 && month1>month2) return 0;
    if (year1==year2 && month1==month2 && day1>day2) return 0;

    if (year1==year2 && month1==month2 && day1==day2) return (-1);

    //Da return a False se Data2 mais recente.
    return 1;
}

// A função calculaIdade calcula quantos anos passaram desde uma certa data.
int calculateAge (char *line){

    int day,month,year;
    int age;
    
    //Divide a data em dia, mês e ano.
    day = (line[0]-'0')*10+(line[1]-'0');
    month = (line[3]-'0')*10+(line[4]-'0');
    year = (line[6]-'0')*1000+(line[7]-'0')*100+(line[8]-'0')*10+(line[9]-'0');
    
    // Calcula a idade sem verificar se ele ja fez anos em 2022.
    age = IDADE_ANO-year-1;
    
    // Condição que verifica se a pessoa ja fez anos no ano 2022.
    if (month<IDADE_MES || (month==IDADE_MES && day<=IDADE_DIA)){
        age++;                                              
    }
    return age;
}

// A função converte trasforma uma string que possa ter letras maiúsculas
// numa string com apenas letras minúsculas.
char* convert(char *str){
    
    int i;
    
    for (i = 0; str[i] != '\0'; i++) {
        // Tranforma o carácter na posição i em minúsculo, caso ele seja maiúsculo.
        str[i] = tolower(str[i]);
    }
    return str;
}

// Esta função é responsável por verificar se a data passada no ficheiro é válida através dos parâmetros necessários
// Só é valida se tiver um tamanho total de 10, 2 separadores e se tiver 2 inteiros para dia e mes e 4 para o ano
int check_data(char *date){
    
    if(strlen(date)!=10) return 1;

    if(!isdigit(date[0]) || !isdigit(date[1]) || date[2]!='/' || !isdigit(date[3]) || !isdigit(date[4]) || date[5]!='/' ||
       !isdigit(date[6]) || !isdigit(date[7]) || !isdigit(date[8]) || !isdigit(date[9])){
        return 1;
    }

    char day[3]; day[0] = date[0]; day[1] = date[1] ; day[2] = '\0';
    char month[3]; month[0] = date[3]; month[1] = date[4] ; month[2] = '\0';

    if(atoi(day)<1 || atoi(day)>31 || atoi(month)<1 || atoi(month)>12) return 1;

    return 0;
}

// Esta função é responsável por verificar se a distãncia passada no ficheiro é válida através dos parâmetros necessários
// Só é valida se a distãncia for um número inteiro maior que 0
int check_distance(char *distance){
    
    int i;
    int n_digits = strlen(distance);

    for(i=0; i < n_digits; i++){
        if (!isdigit(distance[i])) return 1; 
    }
   
    if(n_digits==1 && distance[0]=='0') return 1;

    return 0;
}

// Esta função é responsável por verificar se o score passado no ficheiro é válida através dos parâmetros necessários
// Só é valida se o score for um número inteiro maior que 0
int check_score(char *score){
    
    int i;
    int n_digits = strlen(score);
    
    if(n_digits==1 && score[0]=='0') return 1;
    
    for(i=0; i < n_digits; i++){
        if(!isdigit(score[i])) return 1;
    }

    return 0;
}

// Esta função é responsável por verificar se a tip passada no ficheiro é válida através dos parâmetros necessários
// Só é valida se a tip for um número inteiro ou decimal maior ou igual a 0
int check_tip(char *tip){
    
    int i;
    int n_digits = strlen(tip);
    
    for(i=0; i < n_digits; i++){
        if((!isdigit(tip[i])) && tip[i]!='.') return 1;
    }

    return 0;
}

// Esta função é responsável por verificar se a conta passada no ficheiro é válida através dos parâmetros necessários
// Só é valida se a conta tiver o parâmetro active ou inactive
int check_account(char* status){
    
    if(strcmp(convert(status),"active")!=0 && strcmp(convert(status),"inactive")!=0) return 1;

    return 0;
}

// Esta função é responsável por verificar se a classe passada no ficheiro é válida através dos parâmetros necessários
// Só é valida se a classe tiver o parâmetro basic, green ou premium
int check_class(char *car){
    
    if(strcmp(convert(car),"basic")!=0 && strcmp(convert(car),"green")!=0 && strcmp(convert(car),"premium")!=0) return 1;
    
    return 0;
}

// Esta função é responsável por determinar o tempo que as hash tables demoram a ser efetuadas
double time_hash(void (*func)(char*, char),char *dir, char file_aux){
  
  clock_t start = clock();
  func(dir,file_aux);
  clock_t end = clock();
  
  return (double)(end - start) / CLOCKS_PER_SEC;

}

// Esta função é responsável por determinar o tempo que as queries demoram a ser efetuadas
double time_query(void (*func)(char*, char*),char *line,char *file){
  
  clock_t start = clock();
  func(line,file);
  clock_t end = clock();
  
  return (double)(end - start) / CLOCKS_PER_SEC;

}

int correct=0; // Determina o número de queries que estão com o output correto
int incorrect=0; // Determina o número de queries que estão com o output incorreto

// Esta função é responsável por determinar se dois ficheiros são iguais ou não
void check_output(int input, char *outputs){

    int buffsize =  1024;
    chdir("Resultados/"); 

    char buffer [250];
    snprintf(buffer, sizeof (buffer), "command%d_output.txt",input);

    char buffer2 [250];
    snprintf(buffer2, sizeof (buffer2), "%s/command%d_output.txt",outputs,input);
    
    FILE *fp1 = fopen(buffer, "rb");

    FILE *fp2 = fopen(buffer2, "rb");

    char buf1[buffsize], buf2[buffsize];
    size_t n1, n2;

    do {
          n1 = fread(buf1, 1, buffsize, fp1); 
          
          if (n1 == 0 && ferror(fp1)) {
             perror("Error reading file 1");
             return;
          }
    
          n2 = fread(buf2, 1, buffsize, fp2);
          
          if (n2 == 0 && ferror(fp2)) {
             perror("Error reading file 2");
             return;
          }
    
          if (n1 != n2 || memcmp(buf1, buf2, n1)) {
             
             printf("\033[0;31m");
             printf("[INCORRECT]\n"); // Print com cor vermelha
             printf("\033[0m");
             
             incorrect++;
             
             return;
          }

  } while (n1 == buffsize && n2 == buffsize);

    printf("\033[0;32m");
    printf("[CORRECT]\n"); // Print com cor verde
    printf("\033[0m");
    
    correct++;

    chdir("trabalho-pratico");

}