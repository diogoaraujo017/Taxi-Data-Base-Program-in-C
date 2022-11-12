#include <stdbool.h>
#define MAX_INFO 50
#define N_LINHAS 100000


unsigned int hash_users(char *username);
void init_hash_table();
bool insert_hash_users(users *u);
users *procura_hash_users(char *username);
void write_user(users u);
void insert_user_hash(char *username, char *name, char *birth_day, char *account_creation, char *pay_method, char *account_status);