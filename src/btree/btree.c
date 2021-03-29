#include "btree.h"

#include <stdio.h>
#include <stdlib.h>

#define ORDEM 1

btree* create_b_tree() {
    btree* new_tree = (btree*)malloc(sizeof(btree));
    new_tree->order = ORDEM;
    new_tree->root = create_b_node(new_tree);

    return new_tree;
}

btree_node* create_b_node(btree* tree) {
    int MAX = tree->order * 2;
    btree_node* new_node = (btree_node*)malloc(sizeof(btree_node));

    new_node->parent = NULL;

    new_node->keys = malloc(sizeof(int) * (MAX + 1));
    new_node->children = malloc(sizeof(btree_node) * (MAX + 2));
    new_node->count = 0;

    for (int i = 0; i < MAX + 2; i++)
        new_node->children[i] = NULL;

    return new_node;
}

void run_btree(btree_node* node, void(visit)(int key)) {
    if (node != NULL) {
        for (int i = 0; i < node->count; i++) {
            run_btree(node->children[i], visit);
            visit(node->keys[i]);
        }
        run_btree(node->children[node->count], visit);
    }
}

int search_b_key(btree* tree, int key) {
    btree_node* node = tree->root;

    while (node != NULL) {
        int i = binary_search(node, key);

        if (i < node->count && node->keys[i] == key)
            return 1;
        else
            node = node->children[i];
    }

    return 0;
}

int binary_search(btree_node* node, int key) {
    int start = 0, end = node->count - 1, mid;
    while (start <= end) {
        mid = (start + end) / 2;
        if (node->keys[mid] == key)
            return mid;
        else if (node->keys[mid] > key)
            end = mid - 1;
        else
            start = mid + 1;
    }

    return start;
}

btree_node* search_node(btree* tree, int key) {
    btree_node* node = tree->root;

    while (node != NULL) {
        int i = binary_search(node, key);

        if (node->children[i] == NULL)
            return node;
        else
            node = node->children[i];
    }

    return NULL;
}

void insert_b_key_node(btree_node* insert_node, btree_node* new_node, int key) {
    int i = binary_search(insert_node, key);

    for (int j = insert_node->count - 1; j >= i; j--) {
        insert_node->keys[j + 1] = insert_node->keys[j];
        insert_node->children[j + 2] = insert_node->children[j + 1];
    }

    insert_node->keys[i] = key;
    insert_node->children[i + 1] = new_node;

    insert_node->count++;
}

int overflow(btree* tree, btree_node* node) {
    return node->count > tree->order * 2;
}

btree_node* split_node(btree* tree, btree_node* split_node) {
    int mid = split_node->count / 2;
    btree_node* new_node = create_b_node(tree);
    new_node->parent = split_node->parent;

    for (int i = mid + 1; i < split_node->count; i++) {
        new_node->children[new_node->count] = split_node->children[i];
        new_node->keys[new_node->count] = split_node->keys[i];

        if (new_node->children[new_node->count] != NULL)
            new_node->children[new_node->count]->parent = new_node;
    }

    new_node->children[new_node->count] = split_node->children[split_node->count];
    if (new_node->children[new_node->count] != NULL)
        new_node->children[new_node->count]->parent = new_node;
    split_node->count = mid;

    return new_node;
}

void insert_b_key(btree* tree, int key) {
    btree_node* node = search_node(tree, key);

    insert_recursive_key(tree, node, NULL, key);
}

void insert_recursive_key(btree* tree, btree_node* insert_node, btree_node* new_node, int key) {
    insert_b_key_node(insert_node, new_node, key);
    if (overflow(tree, insert_node)) {
        int promoted = insert_node->keys[tree->order];
        btree_node* new = split_node(tree, insert_node);

        if (insert_node->parent == NULL) {
            btree_node* parent = create_b_node(tree);
            parent->children[0] = insert_node;
            insert_b_key_node(parent, new, promoted);

            insert_node->parent = parent;
            new->parent = parent;
            tree->root = parent;
        } else {
            insert_recursive_key(tree, insert_node->parent, new, promoted);
        }
    }
}

void delete_tree(btree* tree) {
    if (tree->root) {
        printf("deleting root\n");
        delete_node(tree->root);
    }
    printf("deleting tree\n");
    free(tree);
}

void delete_node(btree_node* node) {
    for (int i = 0; i < (ORDEM * 2 + 2); i++) {
        if (node->children[i]) {
            delete_node(node->children[i]);
            printf("deleted child\n");
        }
    }
    
    if(node) {
        printf("child with key %d being deleted\n", node->keys[0]);
        free(node->keys);
        free(node);
    }
}