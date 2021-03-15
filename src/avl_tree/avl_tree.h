#ifndef avl_tree_h
#define avl_tree_h

#include "./node.h"

typedef struct avl_tree avl_tree;
struct avl_tree {
    avl_node* root;
};

void create_tree(avl_tree** tree);
void create_node(avl_node** node, int key);
void run(avl_tree* tree);
int search_key(avl_tree* tree, int key);
void insert_key(avl_tree* tree, int key);
void delete_key(avl_tree* tree, int key);
void destroy_tree(avl_tree* tree);
void destroy_node(avl_node* node);

#endif
