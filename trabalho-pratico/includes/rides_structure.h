#define TABLE_SIZE 1000000

typedef struct hash_table{
    char *id;
    Rides user;
    struct table *next;
}hash_table;

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
}Rides;

hash_table insert_ride(hash_table t, char *username, char *name, char *birth_day, char *account_creation, char *pay_method, char *account_status);
hash_table new_ride();
