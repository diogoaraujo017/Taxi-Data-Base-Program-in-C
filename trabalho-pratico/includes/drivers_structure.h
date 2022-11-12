#include <stdbool.h>
#define MAX_INFO 50
#define N_LINHAS 10000


unsigned int hash(char *id);
void init_hash_table();
bool insert_hash_table(drivers *r);
drivers *procura_hash_table (char *id);
