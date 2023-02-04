#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "func_auxiliares.h"
#include <ctype.h>
#include <time.h>
#include <unistd.h>

// Function responsible for comparing two dates
int calculateData (char *line,char *line2){

    int day1,month1,year1;
    int day2,month2,year2;
    
    // Divides the date into day, month and year
    day1 = (line[0]-'0')*10+(line[1]-'0');
    month1 = (line[3]-'0')*10+(line[4]-'0');
    year1 = (line[6]-'0')*1000+(line[7]-'0')*100+(line[8]-'0')*10+(line[9]-'0');

    day2 = (line2[0]-'0')*10+(line2[1]-'0');
    month2 = (line2[3]-'0')*10+(line2[4]-'0');
    year2 = (line2[6]-'0')*1000+(line2[7]-'0')*100+(line2[8]-'0')*10+(line2[9]-'0');
    
    // It returns 0 if the first date is more recent than the other
    if (year1>year2) return 0;
    if (year1==year2 && month1>month2) return 0;
    if (year1==year2 && month1==month2 && day1>day2) return 0;

    // It returns -1 if the first date is the same as the second date
    if (year1==year2 && month1==month2 && day1==day2) return (-1);

    // It returns 1 if the second date is more recent than the other
    return 1;
}

// Function calculates how many years have passes since the date in the define
int calculateAge (char *line){

    int day,month,year;
    int age;
    
    // Divides the date into day, month and year
    day = (line[0]-'0')*10+(line[1]-'0');
    month = (line[3]-'0')*10+(line[4]-'0');
    year = (line[6]-'0')*1000+(line[7]-'0')*100+(line[8]-'0')*10+(line[9]-'0');
    
    age = IDADE_ANO-year-1;
    
    // Conditon that verifies if the person has already has their birthday on the year 2022 (defined date)
    if (month<IDADE_MES || (month==IDADE_MES && day<=IDADE_DIA)){
        age++;                                              
    }
    return age;
}


// This function converts a string that may have capital letters to a string with only lower case letters
char* convert(char *str){
    
    int i;
    
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

// This function verifies if the data received as input is valid acording to the necessary parameters.
// It is only valid if it has a size of 10, 2 separators (/) and if there are 2 integer number for the day and month
// and 4 for the year
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

// This function verifies if the distance received as input is valid acording to the necessary parameters.
// It is only valid if the number is an integer and bigger than zero
int check_distance(char *distance){
    
    int i;
    int n_digits = strlen(distance);

    for(i=0; i < n_digits; i++){
        if (!isdigit(distance[i])) return 1; 
    }
   
    if(n_digits==1 && distance[0]=='0') return 1;

    return 0;
}

// This function verifies if the score received as input is valid acording to the necessary parameters.
// It is only valid if the score is an integer and bigger than zero
int check_score(char *score){
    
    int i;
    int n_digits = strlen(score);
    
    if(n_digits==1 && score[0]=='0') return 1;
    
    for(i=0; i < n_digits; i++){
        if(!isdigit(score[i])) return 1;
    }

    return 0;
}

// This function verifies if the tip received as input is valid acording to the necessary parameters.
// It is only valid if the number is an integer or a decimal and bigger or equal to zero
int check_tip(char *tip){
    
    int i;
    int n_digits = strlen(tip);
    
    for(i=0; i < n_digits; i++){
        if((!isdigit(tip[i])) && tip[i]!='.') return 1;
    }

    return 0;
}


// This function verifies if the status received as input is valid acording to the necessary parameters.
// It is only valid if the string is equal to active or inactive
int check_account(char* status){
    
    if(strcmp(convert(status),"active")!=0 && strcmp(convert(status),"inactive")!=0) return 1;

    return 0;
}

// This function verifies if the class received as input is valid acording to the necessary parameters.
// It is only valid if the string is equal to basic, green or premium
int check_class(char *car){
    
    if(strcmp(convert(car),"basic")!=0 && strcmp(convert(car),"green")!=0 && strcmp(convert(car),"premium")!=0) return 1;
    
    return 0;
}

// This function is responsible for determining the time that the hash tables take to be executed
double time_hash(void (*func)(char*, char),char *dir, char file_aux){
  
  clock_t start = clock();
  func(dir,file_aux);
  clock_t end = clock();
  
  return (double)(end - start) / CLOCKS_PER_SEC;

}

// This function is responsible for determining the time that the queries take to be executed
double time_query(void (*func)(char*, char*),char *line,char *file){
  
  clock_t start = clock();
  func(line,file);
  clock_t end = clock();
  
  return (double)(end - start) / CLOCKS_PER_SEC;

}

int correct=0; // Indicates the number of queries that have the correct output
int incorrect=0; // Indicates the number of queries that have the incorrect output

// This function is responsibe to determine if two files are equal to one another or not
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
             printf("[INCORRECT]\n"); // Prints with color red
             printf("\033[0m");
             
             incorrect++;
             
             return;
          }

  } while (n1 == buffsize && n2 == buffsize);

    printf("\033[0;32m");
    printf("[CORRECT]\n"); // Prints with color red
    printf("\033[0m");
    
    correct++;

    chdir("trabalho-pratico");
}