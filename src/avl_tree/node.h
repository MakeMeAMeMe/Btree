typedef struct avl_node avl_node;
struct avl_node {
    avl_node* right;
    avl_node* left;
    int value;
};
