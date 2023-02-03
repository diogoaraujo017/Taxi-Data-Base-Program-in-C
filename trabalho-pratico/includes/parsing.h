#ifndef PARSING_H
#define PARSING_H

int count_lines(char *drivers,char *users,char *rides);

void read_store(char *dir, char file_aux);

void analisa_linha_drivers(char *line);

void analisa_linha_users(char *line);

void analisa_linha_rides(char *line);

#endif