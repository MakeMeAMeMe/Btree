#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./btree/btree.h"
#include "./avl_tree/avl_tree.h"

#define PIOR_CASO_FILE_PATH "./data/pior_caso.txt"
#define MEDIO_CASO_FILE_PATH "./data/medio_caso.txt"

int main() {
    // A estratégia é criar um arquivo com dois campos por linha: qtd de keys inseridas, tempo gasto inserindo todas.
    // Precisa de dois arquivos, um para o pior caso, pode ser ordem crescente, e um para o caso médio, aleatório.

    btree* btree;
    FILE *pior_caso/*, *medio_caso*/;
    clock_t time_delta;

    srand(time(NULL));

    // Pior caso
    pior_caso = fopen(PIOR_CASO_FILE_PATH, "w");
    
    time_delta = clock();
    
    for (size_t test = 1; test <= 100; test++) {    // Testes variando de 1 á 100 chaves
        //for (size_t i = 0; i < 10; i++) {           // 10 testes por qtd de chaves
            btree = create_b_tree(1);
            for (int key = 0; key < test; key++) {  // geração das chaves
                    insert_b_key(btree, key);
                    printf("key inserted: %d\n", key);
            }
            time_delta = clock() - time_delta;
            double time_taken = ((double)time_delta) / CLOCKS_PER_SEC;
            fprintf(pior_caso, "%zu %lf\n", test, time_taken);
            delete_tree(btree);
            printf("-----------------------------------\ntree end\n");
        //}
    }
    fclose(pior_caso);

    /*
    // caso médio
    medio_caso = fopen(MEDIO_CASO_FILE_PATH, "w");
    time_delta -= time_delta; // Espero que resete

    for (size_t test = 1; test <= 100; test++) {
        for (int i = 0; i < test; i++) {
            // insert_key(btree, rand());
            printf("%u\n", rand());
        }
        time_delta = clock() - time_delta;
        double time_taken = ((double)time_delta) / CLOCKS_PER_SEC;
        fprintf(medio_caso, "%zu %lf\n", test, time_taken);
    }
    fclose(medio_caso);
    */
    return 0;
}
