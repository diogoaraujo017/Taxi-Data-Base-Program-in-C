#define TABLE_SIZE 10000

typedef struct hash_table{
    char *id;
    Drivers user;
    struct table *next;
}hash_table;

typedef struct drivers{
    char *id;
    char *name;
    char *birth_day;
    char  gender;
    char *car_class;
    char *license_plate;
    char *acount_creation;  
}Drivers; 

hash_table insert_driver(hash_table t, char *id, char *name, char *birth_day, char *gender, char *car_class, char *license_plate,char *acount_creation);
hash_table new_driver();


