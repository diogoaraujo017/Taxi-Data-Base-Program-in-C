#ifndef PARSE
#define PARSE

typedef struct parse
{
    Users parse[10000];
    int numero_linhas;
}*Parse;  

Parse init_user();
Parse insert_user(Parse w, Users u);
char** get_all_users(Parse x);

#endif