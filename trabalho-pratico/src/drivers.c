#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drivers.h"


Drivers init_car(const char *str) {
    Drivers d = (Drivers*) malloc(sizeof(Drivers));
    d->license_plate= strdup(str);
    return d;
}

char* get_plate(Drivers d){
    return strdup(d->license_plate);
}

char* get_car_info(Drivers d){
    return get_place(d);
}