
#ifndef avl_tree_h
#define avl_tree_h

#include "./node.h"

typedef struct avl_tree avl_tree;
struct avl_tree {
    avl_node* root;
};

void avl_create_tree(avl_tree** tree);
void avl_create_node(avl_node** node, int key);
void _avl_run(avl_node* node);
void avl_run(avl_tree* tree);
int _avl_search_key(avl_node* node, int key);
int avl_search_key(avl_tree* tree, int key);
avl_node* _avl_insert_key(avl_tree* tree, avl_node** node, int key);
avl_node *Delete(avl_node *node, int key);
int height(avl_node* node);
int bf(avl_node* node);
avl_node* rotate_right(avl_node *node);
avl_node* rotate_left(avl_node *node);
avl_node* RR(avl_node* node);
avl_node* LL(avl_node* node);
avl_node* LR(avl_node* node);
avl_node* RL(avl_node* node);

#endif
