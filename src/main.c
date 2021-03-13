#include <stdio.h>
#include <time.h>

#include "./btree/btree.h"

int main(int argc, char const* argv[]) {
    btree* btree = create_tree(1);
    clock_t time;

    time = clock();
    for (int i = 0; i < 100; i++) {
        insert_key(btree, i);
    }
    time = clock() - time;
    double time_taken = ((double)time) / CLOCKS_PER_SEC;

    printf("%f\n", time_taken);
    return 0;
}
