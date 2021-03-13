#ifndef _btree_h
#define _btree_h

#include "node.h"

typedef struct btree {
    node* root;
    int order;
} btree;

btree* create_tree(int order);
node* create_node(btree* tree);
void run(node* node, void(visit)(int key));
int search_key(btree* tree, int key);
int binary_search(node* node, int key);
node* search_node(btree* tree, int key);
void insert_key_node(node* insert_node, node* new_node, int key);
int overflow(btree* tree, node* node);
node* split_node(btree* tree, node* node);
void insert_key(btree* tree, int key);
void insert_recursive_key(btree* tree, node* insert_node, node* new_node, int key);

#endif
