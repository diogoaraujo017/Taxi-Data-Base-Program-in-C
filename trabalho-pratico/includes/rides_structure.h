#include <stdbool.h>
#define MAX_INFO 50
#define N_LINHAS 1000000


unsigned int hash_user_rides(char *user);
void init_hash_table();
bool insert_hash_rides(rides *r);
rides *procura_hash_user_rides(char *user);
