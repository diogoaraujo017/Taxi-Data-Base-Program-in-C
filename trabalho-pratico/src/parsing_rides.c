#include "rides_structure.h"
#include "parsing_rides.h"
#include "parsing_users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


// Esta função é responsável pelo parsing do ficheiro rides.csv. Funciona da seguinte forma:
// É aberto o fichero rides.csv e em seguida é lida linha a linha do ficheiro e colocada na função
// analisa_linha_rides para um melhor tratamento dos dados.
void read_store_rides(){
    FILE *ridesF;
    char line[250];
    ridesF = fopen("rides.csv", "r");

    fgets(line, 250, ridesF);

    while (fgets(line, 250, ridesF)!=NULL){
        analisa_linha_rides(line);
    }
    fclose(ridesF);
}


// Esta função é responsável pelo tratamento da linha, ou seja, é ela que tem o papel de
// ler cada parâmetro dos rides definido na struct. Essa leitura é facilmente efetuada devido
// à existência dos ';' que separam todos os parâmetros. Em seguida, é necessário inserir
// todos os parâmetros relativos à ride (apenas do ficheiro rides.csv) nas hash tables através 
// das funções insert_rides_drivers e insert_rides_users.
void analisa_linha_rides(char *line){
    char *a,*a1,*a2,*a3,*a4,*a5;
    int a6,a7,a8;
    double a9;
    a=malloc(sizeof(line));
    a1=malloc(sizeof(line));
    a2=malloc(sizeof(line));
    a3=malloc(sizeof(line));
    a4=malloc(sizeof(line));
    a5=malloc(sizeof(line));
    int i,j;
    int aux=1;
    char *ptr;
    for(i=0,j=0;line[i]!='\0';i++,j++){
        if (line[i]==';'){

            a[j]='\0';

            switch (aux)
            {
            case 1:
                filtra(a,a1);
                break;
            case 2:    
                filtra(a,a2);
                break;
            case 3:
                filtra(a,a3);
                break;
            case 4:    
                filtra(a,a4);
                break;
            case 5:
                filtra(a,a5);
                break;
            case 6:    
                a6 =(a[0]-'0');
                break;
            case 7:    
                a7 =(a[0]-'0');
                break;
            case 8:    
                a8 =(a[0]-'0');
                break;
            case 9:    
                a9 = strtod(a,&ptr);
                break;
            default:
                break;
            }

            aux++;
            j=-1;
        }
        else a[j]=line[i];

    }
    a[j-1]='\0';

//Funções que inserem todos os parâmetros da ride (apenas do ficheiro rides.csv) nas hash tables 
    insert_rides_drivers(a1,a2,a3,a4,a5,a6,a7,a8,a9,a);
    insert_rides_users(a1,a2,a3,a4,a5,a6,a7,a8,a9,a);

}



