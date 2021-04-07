#include "./data_manager.h"

#include <stdlib.h>
#include <stdio.h>

void init_manager(data_manager** manager, size_t qtd_data) {
    (*manager) = (data_manager*)malloc(sizeof(data_manager));
    (*manager)->qtd_data = 0;
    (*manager)->data = (data_pair*)malloc(qtd_data * sizeof(data_pair));
}

void add_data_manager(data_manager* manager, data_pair data) {
    ((manager->data) + (manager->qtd_data))->qtd_keys = data.qtd_keys;
    ((manager->data) + (manager->qtd_data))->time_taken = data.time_taken;
    manager->qtd_data++;
}

void _print_data_manager(data_pair* data) {
    printf("Time taken to insert %zu keys: %lf\n", data->qtd_keys, data->time_taken);
}

void print_data_manager(data_manager* manager) {
    size_t i;
    for (i = 0; i < manager->qtd_data; i++) {
        _print_data_manager(manager->data + i);
    }
}

void _write_to_file(FILE* file, data_pair* data){
    fprintf(file, "%zu %lf\n", data->qtd_keys, data->time_taken);
}

void write_to_file(data_manager* manager, const char* filepath) {
    size_t i;
    FILE* file;
    file = fopen(filepath, "w+");

    for (i = 0; i < manager->qtd_data; i++) {
        _write_to_file(file, manager->data + i);
    }

    fclose(file);

    printf("Data on path %s written successfully, with %zu lines of data\n", filepath, manager->qtd_data);

}

void destroy_manager(data_manager* manager) {
    free(manager->data);
    free(manager);
}
