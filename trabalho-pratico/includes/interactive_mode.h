#ifndef INTERACTIVE_MODE_H
#define INTERACTIVE_MODE_H

typedef struct _IO_FILE FILE;
typedef struct _win_st WINDOW;

void interactive();

int interact_program(int highlight, WINDOW *win, int querie_possible);

int programa_main (char *file);

void move_pages(FILE *File, WINDOW *win, int n_linhas, int sum);

void display_page (FILE * File, int start, int end, int n_linhas, int isLarge);

#endif