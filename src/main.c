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

void shuffle(int* array, size_t n) {
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int main() {
    btree* btree = NULL;
    avl_tree* avl_tree = NULL;
    clock_t clock_delta;
    double time_delta;
    int keys[100], random_keys[100];

    for (int i = 0; i < 100; i++) {
        keys[i] = i;
        random_keys[i] = i;
    }

    data_manager* manager = NULL;

    srand(time(NULL));

    clock_delta = clock();

#if TEST
#else
    init_manager(&manager, QTD_KEYS * QTD_TESTS);
    for (size_t qtd_keys = 1; qtd_keys <= QTD_KEYS; qtd_keys++) {
        for (size_t test = 0; test < QTD_TESTS; test++) {
            btree = create_b_tree();
            reset_clock(&clock_delta);
            for (int key = 0; key < qtd_keys; key++) {
                insert_b_key(btree, keys[key]);
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
            shuffle(random_keys, 100);
            for (int key = 0; key < qtd_keys; key++) {
                insert_b_key(btree, random_keys[key]);
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
                avl_tree->root = _avl_insert_key(avl_tree, &avl_tree->root, keys[key]);
            }
            reset_clock(&clock_delta);
            time_taken(clock_delta, &time_delta);
            add_data_manager(manager, (data_pair){.qtd_keys = qtd_keys, .time_taken = time_delta});
            avl_run(avl_tree);
            for (int i = 0; i < 100; i++)
                avl_tree->root = Delete(avl_tree->root, i);
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
            shuffle(random_keys, 100);
            for (int key = 0; key < qtd_keys; key++) {
                avl_tree->root = _avl_insert_key(avl_tree, &avl_tree->root, random_keys[key]);
            }
            reset_clock(&clock_delta);
            time_taken(clock_delta, &time_delta);
            add_data_manager(manager, (data_pair){.qtd_keys = qtd_keys, .time_taken = time_delta});
            for (int i = 0; i < 100; i++)
                avl_tree->root = Delete(avl_tree->root, i);
        }
    }
    write_to_file(manager, MEDIO_CASO_AVL_PATH);
    destroy_manager(manager);

#endif

    return 0;
}
