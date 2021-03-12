#include "btree.h"

int main(int argc, char const *argv[])
{
    btree** btree = create_tree(1);
    
    for(int i = 0; i < 100; i++) {
        insert_key(btree, i);
    }

    return 0;
}
