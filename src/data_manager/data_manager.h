#ifndef data_manager_hpp
#define data_manager_hpp

#include <stddef.h>

#define PIOR_CASO_FILENAME "pior_caso.txt"
#define MEDIO_CASO_FILENAME "medio_caso.txt"
#define DATA_PATH "./data/"
#define AVL_DATA_PATH DATA_PATH "avl/"
#define BTREE_DATA_PATH DATA_PATH "btree/"

#define PIOR_CASO_BTREE_PATH BTREE_DATA_PATH PIOR_CASO_FILENAME
#define PIOR_CASO_AVL_PATH AVL_DATA_PATH PIOR_CASO_FILENAME
#define MEDIO_CASO_BTREE_PATH BTREE_DATA_PATH MEDIO_CASO_FILENAME
#define MEDIO_CASO_AVL_PATH AVL_DATA_PATH MEDIO_CASO_FILENAME


typedef struct data_manager data_manager;
typedef struct data_pair data_pair;

struct data_pair {
    size_t qtd_keys;
    double time_taken;
};

struct data_manager {
    data_pair *data;
    size_t qtd_data;
};

void init_manager(data_manager** manager, size_t qtd_data);
void add_data_manager(data_manager* manager, data_pair data);
void print_data_manager(data_manager* manager);
void write_to_file(data_manager* manager, const char* filepath);
void destroy_manager(data_manager* manager);

#endif