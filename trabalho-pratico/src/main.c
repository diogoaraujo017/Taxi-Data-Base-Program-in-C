#include <stdio.h>
#include <string.h>
//#include "drivers.h"
//#include "define.h"

int querie1(char line[]){
    char line2[100];
    int i;

    for(i=2;line[i]!='>';i++){
        line2[i-2] = line[i];
    }
    line2[i] = '\0';

    verifica_input(line);
}
void querie2(char line[]){
    char line2[100];
    int i;

    for(i=2;line[i]!='>';i++){
        line2[i-2] = line[i];
    }
    line2[i] = '\0';
    
}

void querie3(char line[]){
    char line2[100];
    int i;

    for(i=2;line[i]!='>';i++){
        line2[i-2] = line[i];
    }
    line2[i] = '\0';
    
}

int main (int argc, char const *argv[]){
    char line[100];
    int querie = getchar();

    fgets(line, 100, stdin);
    
    switch (querie)
    {
    case '1':
        querie1(line);
        break;
        
    case '2':
        querie2(line);
        break;

    case '3':
        querie3(line);
        break;    
    
    default:
        break;
    }
    
    return 0;
}

// FILE* drivers = fopen("drivers.csv", "r");