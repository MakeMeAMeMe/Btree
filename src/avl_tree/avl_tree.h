#ifndef avl_tree_h
#define avl_tree_h

#include "./node.h"

typedef struct avl_tree avl_tree;
struct avl_tree {
    avl_node* root;
};

void avl_create_tree(avl_tree** tree);
void avl_create_node(avl_node** node, int key);
void avl_run(avl_tree* tree);
int avl_search_key(avl_tree* tree, int key);
void avl_insert_key(avl_tree* tree, int key);
int avl_delete_key(avl_tree* tree, int key);
int avl_delete_key_and_sub_branch(avl_tree* tree, int key);
void avl_destroy_tree(avl_tree* tree);
void avl_destroy_node(avl_node* node);
void avl_balance(avl_tree* tree,avl_node* node);

#endif
