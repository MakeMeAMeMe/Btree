#ifndef _btree_h
#define _btree_h

#include "node.h"

typedef struct btree btree;
struct btree {
    btree_node* root;
    int order;
};

btree* create_b_tree(int order);
btree_node* create_b_node(btree* tree);
void run_btree(btree_node* node, void(visit)(int key));
int search_b_key(btree* tree, int key);
int binary_search(btree_node* node, int key);
btree_node* search_node(btree* tree, int key);
void insert_key_node(btree_node* insert_node, btree_node* new_node, int key);
int overflow(btree* tree, btree_node* node);
btree_node* split_node(btree* tree, btree_node* node);
void insert_b_key(btree* tree, int key);
void insert_recursive_key(btree* tree, btree_node* insert_node, btree_node* new_node, int key);
void delete_tree(btree *tree);
void delete_node(btree_node *node);

#endif
