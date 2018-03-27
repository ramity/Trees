#ifndef NODE_H
#define NODE_H

class Node
{
public:
    Node(int data);
    Node(int data, Node * left, Node * right);

    void getHeight(Node * node, int height = 0);

    Node * left;
    int data;
    Node * right;
};

#endif
