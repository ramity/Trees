#ifndef AVL_H
#define AVL_H

#include "./Node.h"

class AVL
{
public:
    AVL();
    AVL(int data);

    Node * search(int key);
    Node * search(Node * node, int key);

    bool insert(int key);
    Node * insert(Node * node, int key);

    bool remove(int key);
    Node * remove(Node * node, int key);

    void show();
    void show(Node * node);

    int getHeight();
    int getHeight(Node * node, int height);

    int getSize();
    int getSize(Node * node, int size);

    bool check();
    bool check(Node * node);

    //insert helper
    int countChildren(Node * node);

    Node * leftRotation(Node * node);
    Node * rightRotation(Node * node);
    Node * getMinNode(Node * node);
    int getBalance(Node * node);
    int getNodeHeight(Node * node);

    Node * root;
};

#endif
