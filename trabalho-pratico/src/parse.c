#include "parse.h"
#include "users.h"
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

char** get_all_users(Parse x){
    char**aux = (char**) alloc(((x->numero_linhas)+1)*sizeof(char**));
    for (int i=0;i< x->numero_linhas;i++){
        aux[i] = strdup(x->parse[i]);
    }
}


