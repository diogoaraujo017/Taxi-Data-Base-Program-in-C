#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users.h"


Users init_user(const char *str) {
    Users u = (Users*) malloc(sizeof(Users));
    u.username= strdup(str);
    return u;
}

char* get_username(Users u){
    return strdup(u.username);
}

char* get_user_info(Users u){
    return get_username(u);
}