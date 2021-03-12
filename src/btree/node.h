typedef struct node {
    int count;
    int *keys;
    struct node **children;
    struct node *father;
} node;