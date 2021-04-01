#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./avl_tree/avl_tree.h"
#include "./btree/btree.h"
#include "./data_manager/data_manager.h"
#include "./polyfill/clock.h"

#define QTD_KEYS 100
#define QTD_TESTS 10

// #define TEST

int main() {
    // A estratégia é criar um arquivo com dois campos por linha: qtd de keys inseridas, tempo gasto inserindo todas.
    // Precisa de dois arquivos, um para o pior caso, pode ser ordem crescente, e um para o caso médio, aleatório.

    btree* btree = NULL;
    avl_tree* avl_tree = NULL;
    clock_t clock_delta;
    double time_delta;
    int random_key;

    data_manager* manager = NULL;

    srand(time(NULL));

    clock_delta = clock();

#ifdef TEST
    long qtd_keys;
    int user_key;
    scanf("%ld", &qtd_keys);
    init_manager(&manager, QTD_KEYS * QTD_TESTS);
    avl_create_tree(&avl_tree);
    reset_clock(&clock_delta);
    for (int key = 0; key < qtd_keys; key++) {
        scanf("%d", &user_key);
        avl_insert_key(avl_tree, user_key);
    }
    reset_clock(&clock_delta);
    time_taken(clock_delta, &time_delta);
    add_data_manager(manager, (data_pair){.qtd_keys = qtd_keys, .time_taken = time_delta});
    avl_destroy_tree(avl_tree);
    destroy_manager(manager);
#endif

#ifndef TEST
    init_manager(&manager, QTD_KEYS * QTD_TESTS);
    for (size_t qtd_keys = 1; qtd_keys <= QTD_KEYS; qtd_keys++) {
        for (size_t test = 0; test < QTD_TESTS; test++) {
            btree = create_b_tree();
            reset_clock(&clock_delta);
            for (int key = 0; key < qtd_keys; key++) {
                insert_b_key(btree, key);
            }
            reset_clock(&clock_delta);
            time_taken(clock_delta, &time_delta);
            add_data_manager(manager, (data_pair){.qtd_keys = qtd_keys, .time_taken = time_delta});
            free(btree);
        }
    }
    write_to_file(manager, PIOR_CASO_BTREE_PATH);
    destroy_manager(manager);

    init_manager(&manager, QTD_KEYS * QTD_TESTS);
    for (size_t qtd_keys = 1; qtd_keys <= QTD_KEYS; qtd_keys++) {
        for (size_t test = 0; test < QTD_TESTS; test++) {
            btree = create_b_tree();
            reset_clock(&clock_delta);
            for (int key = 0; key < qtd_keys; key++) {
                random_key = rand() % 100;  // Normalizar para range [0, 99], ficando parecido com o sequencial
                insert_b_key(btree, random_key);
            }
            reset_clock(&clock_delta);
            time_taken(clock_delta, &time_delta);
            add_data_manager(manager, (data_pair){.qtd_keys = qtd_keys, .time_taken = time_delta});
            free(btree);
        }
    }
    write_to_file(manager, MEDIO_CASO_BTREE_PATH);
    destroy_manager(manager);

    init_manager(&manager, QTD_KEYS * QTD_TESTS);
    for (size_t qtd_keys = 1; qtd_keys <= QTD_KEYS; qtd_keys++) {
        for (size_t test = 0; test < QTD_TESTS; test++) {
            avl_create_tree(&avl_tree);
            reset_clock(&clock_delta);
            for (int key = 0; key < qtd_keys; key++) {
                avl_insert_key(avl_tree, key);
            }
            reset_clock(&clock_delta);
            time_taken(clock_delta, &time_delta);
            add_data_manager(manager, (data_pair){.qtd_keys = qtd_keys, .time_taken = time_delta});
            avl_run(avl_tree);
            avl_destroy_tree(avl_tree);
        }
    }
    write_to_file(manager, PIOR_CASO_AVL_PATH);
    destroy_manager(manager);

    init_manager(&manager, QTD_KEYS * QTD_TESTS);
    for (size_t qtd_keys = 1; qtd_keys <= QTD_KEYS; qtd_keys++) {
        for (size_t test = 0; test < QTD_TESTS; test++) {
            avl_create_tree(&avl_tree);
            printf("nova\n");
            reset_clock(&clock_delta);
            for (int key = 0; key < qtd_keys; key++) {
                do {
                    random_key = rand() % 100;  // Normalizar para range [0, 99], ficando parecido com o sequencial
                } while (avl_search_key(avl_tree, random_key));
                printf("key: %d\n", random_key);
                avl_insert_key(avl_tree, random_key);
            }
            reset_clock(&clock_delta);
            time_taken(clock_delta, &time_delta);
            add_data_manager(manager, (data_pair){.qtd_keys = qtd_keys, .time_taken = time_delta});
            avl_destroy_tree(avl_tree);
        }
    }
    write_to_file(manager, MEDIO_CASO_AVL_PATH);
    destroy_manager(manager);
#endif
    return 0;
}
