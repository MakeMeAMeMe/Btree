#include "./avl_tree.h"

#include <stdio.h>
#include <stdlib.h>

void avl_create_tree(avl_tree** tree) {
    (*tree) = (avl_tree*)malloc(sizeof(avl_tree));
    (*tree)->root = NULL;
}

void avl_create_node(avl_node** node, int key) {
    (*node) = (avl_node*)malloc(sizeof(avl_node));
    (*node)->left = NULL;
    (*node)->right = NULL;
    (*node)->key = key;
}

void _avl_run(avl_node* node) {
    if (node->left) {
        _avl_run(node->left);
    }
    if (node->right) {
        _avl_run(node->right);
    }
    printf("%d ", node->key);
}

void avl_run(avl_tree* tree) {
    if (tree->root) {
        _avl_run(tree->root);
        printf("\n");
    } else {
        printf("Tree is Empty");
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

void _avl_insert_key(avl_node* node, int key) {
    if (node == NULL) {
        avl_create_node(&node, key);
    } else if (node->key > key) {  // TODO: O que fazer quando node->key == key? Rejeitar a inserção ou adicionar assim mesmo? A direira ou a esquerda?
        _avl_insert_key(node->left, key);
    } else {
        _avl_insert_key(node->right, key);
    }
}
void avl_insert_key(avl_tree* tree, int key) {
    _avl_insert_key(tree->root, key);
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
        left = altura(node->left) + 1;
    }
    if (node->right != NULL) {
        right = altura(node->right) + 1;
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

    if (node->left != NULL) {
        left = altura(node->left) + 1;
    }
    if (node->right != NULL) {
        right = altura(node->right) + 1;
    }

    return left - right;
}

avl_node* rse(avl_node* node) {
    if (node == NULL) {
        return node;
    }
    avl_node* parent = node->parent;
    avl_node* right = node->right;

    node->right = right->left;
    node->parent = right;
    right->left = node;
    right->parent = parent;

    return right;
}

avl_node* rse(avl_node* node) {
    if (node == NULL) {
        return node;
    }
    avl_node* parent = node->parent;
    avl_node* left = node->left;

    node->left = left->right;
    node->parent = left;
    left->right = node;
    left->parent = parent;

    return left;
}

avl_node* rde(avl_node* node) {
    node->right = rsd(node->right);
    return rse(node);
}

avl_node* rdd(avl_node* node) {
    node->left = rse(node->left);
    return rsd(node);
}
