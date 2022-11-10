#include "users.h"
#include "parse.h"
#include <string.h>
#include <stdlib.h>


Parse init_user() {
    Parse p = (Parse) malloc(sizeof(Parse));
    p->numero_linhas = 0;
    return p;
}

Parse insert_user(Parse w, Users u){
    w->parse[w->numero_linhas] = u;
    (w->numero_linhas)++;
    return w;
}


int get_nr_linhas(Workshop w) {
    return (w->numero_linhas);
}


