#include "./avl_tree.h"

#include <stdlib.h>

void create_tree(avl_tree** tree) {
    (*tree) = (avl_tree*)malloc(sizeof(avl_tree));
    (*tree)->root = NULL;
}

void create_node(avl_node** node, int key) {
    (*node) = (avl_node*)malloc(sizeof(avl_node));
    (*node)->left = NULL;
    (*node)->right = NULL;
    (*node)->key = key;
}

void _run(avl_node* node) {
    if (node->left) {
        _run(node->left);
    }
    if (node->right) {
        _run(node->right);
    }
    printf("%d ", node->key);
}

void run(avl_tree* tree) {
    if (tree->root) {
        _run(tree->root);
        printf("\n");
    } else {
        printf("Tree is Empty");
    }
}

int _search_key(avl_node* node, int key) {
    if (node == NULL) {
        return 0;
    } else if (node->key == key) {
        return 1;
    } else if (_search_key(node->left, key)) {
        return 1;
    } else if (_search_key(node->right, key)) {
        return 1;
    }
    return 0;
}

int search_key(avl_tree* tree, int key) {
    _search_key(tree->root, key);
}

void _insert_key(avl_node* node, int key) {
    if (node == NULL) {
        create_node(&node, key);
    } else if (node->key > key) {  // TODO: O que fazer quando node->key == key? Rejeitar a inserção ou adicionar assim mesmo? A direira ou a esquerda?
        _insert_key(node->left, key);
    } else {
        _insert_key(node->right, key);
    }
}
void insert_key(avl_tree* tree, int key) {
    _insert_key(tree->root, key);
}

void delete_key(avl_tree* tree, int key); //TODO: :(

void destroy_tree(avl_tree* tree) {
    if (tree->root) {
        destroy_node(tree->root);
    }
    free(tree);
}

void destroy_node(avl_node* node) {
    if (node->right) {
        destroy_node(node->right);
    }
    if (node->left) {
        destroy_node(node->left);
    }
    free(node);
}
