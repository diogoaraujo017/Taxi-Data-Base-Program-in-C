#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rides.h"


Rides init_ride(const char *str) {
    Rides r = (Rides*) malloc(sizeof(Rides));
    r->id= strdup(str);
    return r;
}

char* get_date(Rides r){
    return strdup(r->date);
}

char* get_ride_info(Rides r){
    return get_place(r);
}