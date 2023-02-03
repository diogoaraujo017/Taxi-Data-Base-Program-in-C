#ifndef FUNC_AUXILIARES_H
#define FUNC_AUXILIARES_H

#define IDADE_DIA 9
#define IDADE_MES 10
#define IDADE_ANO 2022

int calculateData (char *line,char *line2);

int calculateAge (char *line);

char* convert(char *str);

int check_data(char *date);

int check_distance(char *distance);

int check_score(char *score);

int check_tip(char *tip);

int check_account(char* status);

int check_class(char *car);

double time_hash(void (*func)(char*, char),char *dir, char file_aux);

double time_query(void (*func)(char*, char*),char *line,char *file);

void check_output(int input, char *outputs);

#endif