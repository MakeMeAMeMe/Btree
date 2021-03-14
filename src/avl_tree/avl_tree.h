#ifndef avl_tree_h
#define avl_tree_h

#include "./node.h"

typedef struct avl_tree avl_tree;
struct avl_tree {
    avl_node* root;
    int order;
};

#endif
