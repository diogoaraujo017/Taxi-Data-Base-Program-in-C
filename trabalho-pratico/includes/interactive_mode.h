#ifndef INTERACTIVE_MODE_H
#define INTERACTIVE_MODE_H

typedef struct _IO_FILE FILE;

typedef struct _win_st WINDOW;

void interactive();
int interact_program(int highlight, WINDOW *win, int querie_possible);
int programa_main (char *file);
void go_back (int linha_inicial, FILE* file);

#endif