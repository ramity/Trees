#include "./Node.h"

Node::Node(int data)
{
    this->left = NULL;
    this->data = data;
    this->right = NULL;
}

Node::Node(int data, Node * left, Node * right)
{
    this->left = left;
    this->data = data;
    this->right = right;
}
