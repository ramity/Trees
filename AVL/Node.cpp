#include "./Node.h"

Node::Node(int data)
{
    this->left = NULL;
    this->data = data;
    this->right = NULL;
    this->height = 1;
}
