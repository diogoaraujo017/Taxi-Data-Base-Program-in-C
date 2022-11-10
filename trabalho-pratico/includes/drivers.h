#ifndef WORKSHOP
#define WORKSHOP

typedef struct workshop *Workshop;

typedef struct drivers{
    char *id;
    char *name;
    char *birth_day;
    char  gender;
    char *car_class;
    char *license_plate;
    char *acount_creation;  
}Drivers; 

Drivers init_car(const char *str);
char* get_plate(Drivers d);
char* get_car_info(Drivers d);

#endif
