#ifndef PARSING_H
#define PARSING_H

int count_lines(char *drivers,char *users,char *rides);

void read_store(char *dir, char file_aux);

void analyze_line_drivers(char *line);

void analyze_line_users(char *line);

void analyze_line_rides(char *line);

#endif