#ifndef _btree_h
#define _btree_h

#include "./node.hpp"
#include <cstdlib>

namespace btree {

template <typename T>
struct Btree {
    Node<T> *raiz;
    unsigned int modulo;
    static void create(Btree** btree){
        (*btree) = (Btree*) malloc(sizeof(Btree));
        (*btree)->raiz = NULL;
        (*btree)->modulo = 2;
    }
    static void destroy(Btree* btree);
    void add(T value);
    void remove(T value);
    void walk();
    void print();
    void find(T value, T* out);
    void balance();
};

}  // namespace Btree

#endif