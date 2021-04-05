#ifndef avl_tree_h
#define avl_tree_h
#define PROFESSOR 0

#if PROFESSOR

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
} No;

typedef struct arvore {
    struct no* raiz;
} Arvore;

Arvore* criar();
void balanceamento(Arvore*, No*);
No* adicionar(Arvore* arvore, int valor);
int altura(No*);
int fb(No*);
No* rsd(Arvore*, No*);
No* rse(Arvore*, No*);
No* rdd(Arvore*, No*);
No* rde(Arvore*, No*);

#else

#include "./node.h"

typedef struct avl_tree avl_tree;
struct avl_tree {
    avl_node* root;
};

avl_tree* avl_create_tree();
avl_node* avl_create_node();
void avl_run(avl_tree* tree);
int avl_search_key(avl_tree* tree, int key);
void avl_insert_key(avl_tree* tree, int key);
int avl_delete_key(avl_tree* tree, int key);
int avl_delete_key_and_sub_branch(avl_tree* tree, int key);
void avl_destroy_tree(avl_tree* tree);
void avl_destroy_node(avl_node* node);
void avl_balance(avl_tree* tree, avl_node* node);
int height(avl_node* node);
int bf(avl_node* node);
avl_node* rse(avl_tree* tree, avl_node* node);
avl_node* rsd(avl_tree* tree, avl_node* node);
avl_node* rde(avl_tree* tree, avl_node* node);
avl_node* rdd(avl_tree* tree, avl_node* node);

#endif

#endif
