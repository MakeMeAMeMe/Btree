#ifndef _btree_h
#define _btree_h

#include "node.h"

typedef struct btree btree;
struct btree {
    btree_node* root;
    int order;
};

btree* create_tree(int order);
btree_node* create_node(btree* tree);
void run(btree_node* node, void(visit)(int key));
int search_key(btree* tree, int key);
int binary_search(btree_node* node, int key);
btree_node* search_node(btree* tree, int key);
void insert_key_node(btree_node* insert_node, btree_node* new_node, int key);
int overflow(btree* tree, btree_node* node);
btree_node* split_node(btree* tree, btree_node* node);
void insert_key(btree* tree, int key);
void insert_recursive_key(btree* tree, btree_node* insert_node, btree_node* new_node, int key);

#endif
