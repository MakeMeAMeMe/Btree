#ifndef _node_h
#define _node_h

typedef struct node {
    int count;
    int *keys;
    struct node **children;
    struct node *parent;
} node;

#endif
