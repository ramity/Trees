#include "./Node.h"

Node::Node(int data)
{
    this->left = NULL;
    this->data = data;
    this->right = NULL;
    this->height = 1;
}

Node::Node(int data, Node * left, Node * right)
{
    this->left = left;
    this->data = data;
    this->right = right;

    int leftHeight = this->getHeight(node->left, height + 1);
    int rightHeight = = this->getHeight(node->left, height + 1);

    this->height = leftHeight - rightHeight;
}

int Node::getHeight(Node * node, int height)
{
    if(node->left != NULL && node->right != NULL)
    {
        return max(
            this->getHeight(node->left, height + 1),
            this->getHeight(node->right, height + 1)
        );
    }
    else if(node->left != NULL && node->right == NULL)
    {
        return this->getHeight(node->left, height + 1);
    }
    else if(node->left == NULL && node->right != NULL)
    {
        return this->getHeight(node->right, height + 1);
    }
    else if(node->left == NULL && node->right == NULL)
    {
        return height;
    }
}
