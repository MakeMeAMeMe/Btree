#ifndef _node_h
#define _node_h

typedef struct btree_node btree_node;
struct btree_node {
    int count;
    int *keys;
    btree_node **children;
    btree_node *parent;
};

#endif
