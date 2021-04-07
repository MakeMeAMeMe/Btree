#include "./avl_tree.h"

#include <stdio.h>
#include <stdlib.h>

void avl_create_tree(avl_tree** tree) {
    (*tree) = (avl_tree*)malloc(sizeof(avl_tree));
    (*tree)->root = NULL;
}

void avl_create_node(avl_node** node, int key) {
    (*node) = (avl_node*)malloc(sizeof(avl_node));
    if (!(*node)) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    (*node)->left = NULL;
    (*node)->right = NULL;
    (*node)->node_height = 0;
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

avl_node* _avl_insert_key(avl_tree* tree, avl_node** node, int key) {
    if (*node == NULL) {
        avl_create_node(node, key);
    } else if ((*node)->key == key) {
        (*node)->count++;
    } else if (key > (*node)->key) {
        (*node)->right = _avl_insert_key(tree, &(*node)->right, key);
        if (bf((*node)) == -2) {
            if (key > (*node)->right->key)
                (*node) = RR((*node));
            else
                (*node) = RL((*node));
        }
    } else if (key < (*node)->key) {
        (*node)->left = _avl_insert_key(tree, &(*node)->left, key);
        if (bf((*node)) == 2) {
            if (key < (*node)->left->key)
                (*node) = LL((*node));
            else
                (*node) = LR((*node));
        }
    }
    (*node)->node_height = height((*node));

    return (*node);
}

avl_node* avl_delete (avl_node* node, int key) {
    avl_node* aux_node;

    if (node == NULL)
        return NULL;
    else if (key > node->key) {
        node->right = avl_delete(node->right, key);
        if (bf(node) == 2) {
            if (bf(node->left) >= 0)
                node = LL(node);
            else
                node = LR(node);
        }
    } else if (key < node->key) {
        node->left = avl_delete(node->left, key);
        if (bf(node) == -2) {
            if (bf(node->right) <= 0)
                node = RR(node);
            else
                node = RL(node);
        }
    } else {
        if (node->right != NULL) {
            aux_node = node->right;
            while (aux_node->left != NULL)
                aux_node = aux_node->left;

            node->key = aux_node->key;
            node->right = avl_delete(node->right, aux_node->key);

            if (bf(node) == 2) {
                if (bf(node->left) >= 0)
                    node = LL(node);
                else
                    node = LR(node);
            }
        } else
            return node->left;
    }
    node->node_height = height(node);
    return node;
}

int height(avl_node* node) {
    int left, right;
    left = 0;
    right = 0;
    if (node == NULL) {
        return 0;
    }
    if (node->right == NULL) {
        right = 0;
    } else {
        right = 1 + node->right->node_height;
    }
    if (node->left == NULL) {
        left = 0;
    } else {
        left = 1 + node->left->node_height;
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
        left = 1 + node->left->node_height;
    }
    if (node->right != NULL) {
        right = 1 + node->right->node_height;
    }

    return left - right;
}

avl_node* rotate_right(avl_node* node) {
    avl_node* aux;
    aux = node->left;
    node->left = aux->right;
    aux->right = node;
    node->node_height = height(node);
    aux->node_height = height(aux);
    return aux;
}

avl_node* rotate_left(avl_node* node) {
    avl_node* aux;
    aux = node->right;
    node->right = aux->left;
    aux->left = node;
    node->node_height = height(node);
    aux->node_height = height(aux);
    return aux;
}

avl_node* RR(avl_node* node) {
    node = rotate_left(node);
    return node;
}

avl_node* LL(avl_node* node) {
    node = rotate_right(node);
    return node;
}

avl_node* LR(avl_node* node) {
    node->left = rotate_left(node->left);
    node = rotate_right(node);
    return node;
}

avl_node* RL(avl_node* node) {
    node->right = rotate_right(node->right);
    node = rotate_left(node);
    return node;
}
