#ifndef _node_h
#define _node_h

namespace btree {

template <typename T>
struct Node {
    int count;
    T* keys;
    Node** children;
    Node* parent;
};

}  // namespace Btree

#endif
