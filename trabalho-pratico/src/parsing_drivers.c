#include "drivers_structure.h"
#include <stdio.h>
#include "parsing_users.h"
#include "parsing_drivers.h"
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


// Esta função é responsável pelo parsing do ficheiro drivers.csv. Funciona da seguinte forma:
// É aberto o fichero drivers.csv e em seguida é lida linha a linha do ficheiro e colocada na função
// analisa_linha_drivers para um melhor tratamento dos dados.
void read_store_drivers(){
    FILE *driversF;
    char line[250];
    driversF = fopen("drivers.csv", "r");

    fgets(line, 250, driversF);

    while (fgets(line, 250, driversF)!=NULL){
        analisa_linha_drivers(line);
    }
    fclose(driversF);
}


// Esta função é responsável pelo tratamento da linha, ou seja, é ela que tem o papel de
// ler cada parâmetro dos drivers definido na struct. Essa leitura é facilmente efetuada devido
// à existência dos ';' que separam todos os parâmetros. Em seguida, é necessário inserir
// todos os parâmetros relativos ao driver (apenas do ficheiro drivers.csv) na hash table através 
// da função insert_hash_drivers.
void analisa_linha_drivers(char *line){
    char *a,*a1,*a2,*a3,*a5,*a6,*a7,*a8;
    char a4;
    a=malloc(sizeof(line));
    a1=malloc(sizeof(line));
    a2=malloc(sizeof(line));
    a3=malloc(sizeof(line));
    a5=malloc(sizeof(line));
    a6=malloc(sizeof(line));
    a7=malloc(sizeof(line));
    a8=malloc(sizeof(line));
    int i,j;
    int aux=1;
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
                a4=a[0];
                break;
            case 5:
                filtra(a,a5);
                break;
            case 6:    
                filtra(a,a6);
                break;
            case 7:    
                filtra(a,a7);
                break;   
            case 8:    
                filtra(a,a8);
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

//Função que insere todos os parâmetros do driver(apenas do ficheiro drivers.csv) na hash table 
    insert_hash_drivers(a1,a2,a3,a4,a5,a6,a7,a8,a);

}
