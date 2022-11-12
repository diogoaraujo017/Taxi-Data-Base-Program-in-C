#include <stdbool.h>
#define MAX_INFO 50
#define N_LINHAS 10000


unsigned int hash_drivers(char *id);
void init_hash_table();
bool insert_hash_drivers(drivers *d);
drivers *procura_hash_drivers (char *id);
