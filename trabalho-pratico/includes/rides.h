#ifndef RIDES
#define RIDES


typedef struct rides{
    char *id;
    char *date;
    char *driver;
    char *user;
    char *city;
    int distance;
    int score_user;
    int score_driver;
    double tip;
    char *comment;  
}*Rides;

Rides init_ride(const char *str);
char* get_date(Rides r);
char* get_ride_info(Rides r);

#endif