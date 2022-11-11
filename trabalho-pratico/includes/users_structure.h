#define TABLE_SIZE 100000

typedef struct hash_table{
    char *username;
    Users user;
    struct table *next;
}hash_table;

typedef struct users{
    char *username;
    char *name;
    char *birth_day;
    char *account_creation; 
    char *pay_method;
    char *account_status;
}Users;

hash_table *create_hash(void);
hash_table new_user();
hash_table insert_user(hash_table t, char *username, char *name, char *birth_day, char *account_creation, char *pay_method, char *account_status);
void write_user(Users u);