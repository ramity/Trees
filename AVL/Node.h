#ifndef NODE_H
#define NODE_H

class Node
{
public:
    Node(int data);
    Node(int data, Node * left, Node * right);

    Node * left;
    int data;
    Node * right;
    int height;
};

#endif
