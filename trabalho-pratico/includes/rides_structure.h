#include <stdbool.h>
#define MAX_INFO 50
#define N_LINHAS 1000000


unsigned int hash(char *user);
void init_hash_table();
bool insert_hash_table(rides *r);
rides *procura_hash_table (char *user);
