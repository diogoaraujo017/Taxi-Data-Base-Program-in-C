#ifndef RIDES_STRUCTURE_H
#define RIDES_STRUCTURE_H

#include <stdbool.h>
#include "parsing.h"

#define MAX_INFO 100
#define N_LINHAS 1000000


int calculaData (char *line,char *line2);
int calculaData2 (int dia, int mes, int ano,char *line2,int key);
int calculaIdade (char *line);
const char* converte(char *str);
unsigned int hash_ride(int id);
void init_hash_rides();
bool insert_hash_rides(char *id,char *dt,char *dr,char *user,char *c,int dist,int su,int sd,double tip);
rides *procura_rides(int id);

#endif
