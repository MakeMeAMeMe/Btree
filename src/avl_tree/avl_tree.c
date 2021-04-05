#include "./avl_tree.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#if PROFESSOR

Arvore* criar() {
    Arvore* arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;

    return arvore;
}

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

No* adicionarNo(No* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == NULL) {
            printf("Adicionando %d\n", valor);
            No* novo = malloc(sizeof(No));
            novo->valor = valor;
            novo->pai = no;

            no->direita = novo;

            return novo;
        } else {
            return adicionarNo(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            printf("Adicionando %d\n", valor);
            No* novo = malloc(sizeof(No));
            novo->valor = valor;
            novo->pai = no;

            no->esquerda = novo;

            return novo;
        } else {
            return adicionarNo(no->esquerda, valor);
        }
    }
}

No* adicionar(Arvore* arvore, int valor) {
    if (arvore->raiz == NULL) {
        printf("Adicionando %d\n", valor);
        No* novo = malloc(sizeof(No));
        novo->valor = valor;

        arvore->raiz = novo;

        return novo;
    } else {
        No* no = adicionarNo(arvore->raiz, valor);
        balanceamento(arvore, no);

        return no;
    }
}

void remover(Arvore* arvore, No* no) {
    if (no->esquerda != NULL) {
        remover(arvore, no->esquerda);
    }

    if (no->direita != NULL) {
        remover(arvore, no->direita);
    }

    if (no->pai == NULL) {
        arvore->raiz = NULL;
    } else {
        if (no->pai->esquerda == no) {
            no->pai->esquerda = NULL;
        } else {
            no->pai->direita = NULL;
        }
    }

    free(no);
}

No* localizar(No* no, int valor) {
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != NULL) {
                return localizar(no->esquerda, valor);
            }
        } else {
            if (no->direita != NULL) {
                return localizar(no->direita, valor);
            }
        }
    }

    return NULL;
}

void percorrerProfundidadeInOrder(No* no, void (*callback)(int)) {
    if (no != NULL) {
        percorrerProfundidadeInOrder(no->esquerda, callback);
        callback(no->valor);
        percorrerProfundidadeInOrder(no->direita, callback);
    }
}

void percorrerProfundidadePreOrder(No* no, void (*callback)(int)) {
    if (no != NULL) {
        callback(no->valor);
        percorrerProfundidadePreOrder(no->esquerda, callback);
        percorrerProfundidadePreOrder(no->direita, callback);
    }
}

void percorrerProfundidadePosOrder(No* no, void(callback)(int)) {
    if (no != NULL) {
        percorrerProfundidadePosOrder(no->esquerda, callback);
        percorrerProfundidadePosOrder(no->direita, callback);
        callback(no->valor);
    }
}

void visitar(int valor) {
    printf("%d ", valor);
}

void balanceamento(Arvore* arvore, No* no) {
    while (no != NULL) {
        int fator = fb(no);

        if (fator > 1) {  //árvore mais pesada para esquerda
            //rotação para a direita
            if (fb(no->esquerda) > 0) {
                printf("RSD(%d)\n", no->valor);
                rsd(arvore, no);  //rotação simples a direita, pois o FB do filho tem sinal igual
            } else {
                printf("RDD(%d)\n", no->valor);
                rdd(arvore, no);  //rotação dupla a direita, pois o FB do filho tem sinal diferente
            }
        } else if (fator < -1) {  //árvore mais pesada para a direita
            //rotação para a esquerda
            if (fb(no->direita) < 0) {
                printf("RSE(%d)\n", no->valor);
                rse(arvore, no);  //rotação simples a esquerda, pois o FB do filho tem sinal igual
            } else {
                printf("RDE(%d)\n", no->valor);
                rde(arvore, no);  //rotação dupla a esquerda, pois o FB do filho tem sinal diferente
            }
        }

        no = no->pai;
    }
}

int altura(No* no) {
    int esquerda = 0, direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }

    return esquerda > direita ? esquerda : direita;  //max(esquerda,direita)
}

int fb(No* no) {
    int esquerda = 0, direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }

    return esquerda - direita;
}

No* rse(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* direita = no->direita;

    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}

No* rsd(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* esquerda = no->esquerda;

    no->esquerda = esquerda->direita;
    no->pai = esquerda;

    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

No* rde(Arvore* arvore, No* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

No* rdd(Arvore* arvore, No* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}

#else

avl_tree* avl_create_tree() {
    avl_tree* tree;
    tree = (avl_tree*)malloc(sizeof(avl_tree));
    tree->root = NULL;
    return tree;
}

avl_node* avl_create_node() {
    avl_node* node;
    node = (avl_node*)malloc(sizeof(avl_node));
    if (!node) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->count = 1;
    return node;
}

void _avl_run(avl_node* node, unsigned int level) {
    if (node->left) {
        _avl_run(node->left, level + 1);
    }
    printf("%u %d(%u)\n", level, node->key, node->count);
    if (node->right) {
        _avl_run(node->right, level + 1);
    }
}

void avl_run(avl_tree* tree) {
    if (tree->root) {
        _avl_run(tree->root, 1);
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

void _avl_insert_key(avl_tree* tree, avl_node* node, int key) {
    if (node->key == key) {
        node->count++;
    } else if (node->key > key) {
        if (node->left == NULL) {
            node->left = avl_create_node();
            node->left->key = key;
            node->left->parent = node;
            assert(node->left->key == key);
            assert(node->left->count == 1);
            assert(node->left->parent == node);
            assert(node->left->parent->key == node->key);
            avl_balance(tree, node->left);
        } else {
            _avl_insert_key(tree, node->left, key);
        }
    } else if (node->key < key) {
        if (node->right == NULL) {
            node->right = avl_create_node();
            node->right->key = key;
            node->right->parent = node;
            assert(node->right->key == key);
            assert(node->right->count == 1);
            assert(node->right->parent == node);
            assert(node->right->parent->key == node->key);
            avl_balance(tree, node->right);
        } else {
            _avl_insert_key(tree, node->right, key);
        }
    }
}
void avl_insert_key(avl_tree* tree, int key) {
    if (tree->root == NULL) {
        tree->root = avl_create_node();
        tree->root->key = key;
    } else {
        _avl_insert_key(tree, tree->root, key);
    }
}

// int avl_delete_key(avl_tree* tree, int key);  //TODO: :(

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
    // printf("node: %p\n", node);
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
        } else if (parent->right == node) {
            parent->right = right;
        } else {
            printf("e %p %p %p %p\n", parent, parent->right, parent->left, node);
            printf("nop\n");
        }
    }
    return right;
}

avl_node* rsd(avl_tree* tree, avl_node* node) {
    avl_node* parent = node->parent;
    avl_node* left = node->left;  // y

    node->left = left->right;
    node->parent = left;

    left->right = node;  // x
    left->parent = parent;

    if (parent == NULL) {
        tree->root = left;
    } else {
        if (parent->left == node) {
            parent->left = left;
        } else if (parent->right == node) {
            parent->right = left;
        } else {
            printf("r %p %p %p %p\n", parent, parent->right, parent->left, node);
            printf("nop\n");
        }
    }

    return left;
}

avl_node* rde(avl_tree* tree, avl_node* node) {
    node->right = rsd(tree, node->right);
    avl_node* resp = rse(tree, node);
    return resp;
}

avl_node* rdd(avl_tree* tree, avl_node* node) {
    node->left = rse(tree, node->left);
    avl_node* resp = rsd(tree, node);
    return resp;
}

void avl_balance(avl_tree* tree, avl_node* node) {
    int bf_node, bf_left, bf_right;
    while (node != NULL) {
        bf_node = bf(node);
        if (bf_node > 1) {
            bf_left = bf(node->left);
            if (bf_left > 0) {
                // avl_node* parent = node->parent;
                // avl_node* left = node->left;
                // avl_node* cright = left->right;
                // avl_node* cleft = left->left;
                rsd(tree, node);
                // assert(left->parent->key == parent->key);
                // assert(node->parent->key == left->key);
                // assert(node->left->key == cright->key);
                // assert(left->left->key == cleft->key);
                // assert(left->right->key == node->key);
            } else {
                // avl_node* parent = node->parent;
                // avl_node* left = node->left;
                // avl_node* cright = left->right;
                // avl_node* crcright = cright->right;
                // avl_node* crcleft = cright->left;
                rdd(tree, node);
                // assert(cright->parent->key == parent->key);
                // assert(node->parent->key == cright->key);
                // assert(node->left->key == crcright->key);
                // assert(cright->left->key == left->key);
                // assert(cright->right->key == node->key);
                // assert(left->right->key == crcleft->key);
            }
        } else if (bf_node < -1) {
            bf_right = bf(node->right);
            if (bf_right < 0) {
                // avl_node* right = node->right;
                // avl_node* cleft = right->left;
                // avl_node* cright = right->right;
                rse(tree, node);
                // assert(node->parent->key == right->key);
                // assert(node->right->key == cleft->key);
                // assert(right->right->key == cright->key);
                // assert(right->left->key == node->key);
            } else {
                // avl_node* parent = node->parent;
                // avl_node* right = node->right;      // 5
                // avl_node* cleft = right->left;      // 4
                // avl_node* crcright = cleft->right;  // c
                // avl_node* crcleft = cleft->left;    // d
                rde(tree, node);
                // assert(cleft->parent->key == parent->key);
                // assert(node->parent->key == cleft->key);
                // assert(node->right->key == crcleft->key);
                // assert(cleft->left->key == node->key);
                // assert(cleft->right->key == right->key);
                // assert(right->left->key == crcright->key);
            }
        }
        node = node->parent;
    }
}
#endif