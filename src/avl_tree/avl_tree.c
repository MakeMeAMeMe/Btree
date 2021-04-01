#include "./avl_tree.h"

#include <stdio.h>
#include <stdlib.h>

void avl_create_tree(avl_tree** tree) {
    (*tree) = (avl_tree*)malloc(sizeof(avl_tree));
    (*tree)->root = NULL;
}

void avl_create_node(avl_node** node, int key) {
    (*node) = (avl_node*)malloc(sizeof(avl_node));
    if(!(*node)){
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    (*node)->left = NULL;
    (*node)->right = NULL;
    (*node)->parent = NULL;
    (*node)->key = key;
    (*node)->count = 1;
}

void _avl_run(avl_node* node) {
    if (node->left) {
        _avl_run(node->left);
    }
    if (node->right) {
        _avl_run(node->right);
    }
    printf("%d(%u)\n", node->key, node->count);
}

void avl_run(avl_tree* tree) {
    if (tree->root) {
        _avl_run(tree->root);
        printf("--------\n");
    } else {
        printf("Tree is Empty\n");
    }
}

int _avl_search_key(avl_node* node, int key) {
    if (node == NULL) {
        return 0;
    } else if (node->key == key) {
        return 1;
    } else if (_avl_search_key(node->left, key)) {
        return 1;
    } else if (_avl_search_key(node->right, key)) {
        return 1;
    }
    return 0;
}

int avl_search_key(avl_tree* tree, int key) {
    return _avl_search_key(tree->root, key);
}

void _avl_insert_key(avl_tree* tree, avl_node** node, int key) {
    if (*node == NULL) {
        avl_create_node(node, key);
    } 
    // else if ((*node)->key == key) {
    //     node->count++;
    // } 
    else if ((*node)->key > key) {  // TODO: O que fazer quando node->key == key? Rejeitar a inserção ou adicionar assim mesmo? A direira ou a esquerda?
        if ((*node)->left == NULL) {
            avl_create_node(&((*node)->left), key);
            ((*node)->left)->parent = *node;
            avl_balance(tree, ((*node)->left));
        } else {
            _avl_insert_key(tree, &((*node)->left), key);
        }
    } else if ((*node)->key < key) { 
        if ((*node)->right == NULL) {
            avl_create_node(&((*node)->right), key);
            ((*node)->right)->parent = *node;
            avl_balance(tree, ((*node)->right));
        } else {
            _avl_insert_key(tree, &((*node)->right), key);
        }
    }
}
void avl_insert_key(avl_tree* tree, int key) {
    _avl_insert_key(tree, &(tree->root), key);
}

int avl_delete_key(avl_tree* tree, int key);  //TODO: :(

int _avl_delete_key_and_sub_branch(avl_node** node, int key) {
    if (*node == NULL) {
        return 0;
    } else {
        if ((*node)->key == key) {
            avl_destroy_node(*node);
            return 1;
        } else if ((*node)->key > key) {
            return _avl_delete_key_and_sub_branch(&((*node)->left), key);
        } else {
            return _avl_delete_key_and_sub_branch(&((*node)->right), key);
        }
    }
}
int avl_delete_key_and_sub_branch(avl_tree* tree, int key) {
    return _avl_delete_key_and_sub_branch(&(tree->root), key);
}

void avl_destroy_tree(avl_tree* tree) {
    if (tree->root) {
        avl_destroy_node(tree->root);
    }
    free(tree);
}

void avl_destroy_node(avl_node* node) {
    printf("node: %p\n", node);
    if (node->right) {
        avl_destroy_node(node->right);
    }
    if (node->left) {
        avl_destroy_node(node->left);
    }
    free(node);
}

int height(avl_node* node) {
    int left, right;
    left = 0;
    right = 0;
    if (node == NULL) {
        return 0;
    }
    if (node->left != NULL) {
        left = height(node->left) + 1;
    }
    if (node->right != NULL) {
        right = height(node->right) + 1;
    }

    return left > right ? left : right;
}

int bf(avl_node* node) {
    int left, right;
    left = 0;
    right = 0;

    if (node == NULL) {
        return 0;
    }

    // printf("node %p ", node);
    // printf("left %p ", node->left);
    // printf("right %p\n", node->right);

    if (node->left != NULL) {
        left = height(node->left) + 1;
    }
    if (node->right != NULL) {
        right = height(node->right) + 1;
    }

    return left - right;
}

avl_node* rse(avl_tree* tree, avl_node* node) {
    avl_node* parent = node->parent;
    avl_node* right = node->right;

    node->right = right->left;
    node->parent = right;

    right->left = node;
    right->parent = parent;

    if (parent == NULL) {
        tree->root = right;
    } else {
        if (parent->left == node) {
            parent->left = right;
        } else {
            parent->right = right;
        }
    }

    return right;
}

avl_node* rsd(avl_tree* tree, avl_node* node) {
    avl_node* parent = node->parent;
    avl_node* left = node->left;

    node->left = left->right;
    node->parent = left;

    left->right = node;
    left->parent = parent;

    if (parent == NULL) {
        tree->root = left;
    } else {
        if (parent->left == node) {
            parent->left = left;
        } else {
            parent->right = left;
        }
    }

    return left;
}

avl_node* rde(avl_tree* tree, avl_node* node) {
    node->right = rsd(tree, node->right);
    return rse(tree, node);
}

avl_node* rdd(avl_tree* tree, avl_node* node) {
    node->left = rse(tree, node->left);
    return rsd(tree, node);
}

void avl_balance(avl_tree* tree, avl_node* node) {
    int bf_node, bf_left, bf_right;
    while (node != NULL) {
        bf_node = bf(node);
        if (bf_node > 1) {
            bf_left = bf(node->left);
            if (bf_left > 0) {
                rsd(tree, node);
            } else {
                rdd(tree, node);
            }
        } else if (bf_node < -1) {
            bf_right = bf(node->right);
            if (bf_right < 0) {
                rse(tree, node);
            } else {
                rde(tree, node);
            }
        }
        node = node->parent;
    }
}
