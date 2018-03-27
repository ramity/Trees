#ifndef BST_H
#define BST_H

#include "./Node.h"

class BST
{
public:
    BST();
    BST(int data);
    BST(int data, Node * left, Node * right);

    Node * search(int key);
    Node * search(Node * node, int key);

    bool insert(int key);
    bool insert(Node *& node, int key);

    bool remove(int key);
    bool remove(Node *& node, int key);

    void show();
    void show(Node * node);

    int getHeight(int height = 0);
    int getHeight(Node * node, int height = 0);

    int getSize(int size = 0);
    int getSize(Node * node, int size = 0);

    bool check();
    bool check(Node * node);

    //insert helper
    int countChildren(Node * node);

    Node * root;
};

#endif
