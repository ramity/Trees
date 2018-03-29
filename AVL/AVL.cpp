#include "./AVL.h"

#include <algorithm>
#include <stdlib.h>
#include <iostream>

using namespace std;

//Created by:
//Lewis Brown

//This is a class based approach for an AVL tree.

AVL::AVL()
{
    this->root = NULL;
}

AVL::AVL(int data)
{
    this->root = new Node(data);
}

Node * AVL::search(int key)
{
    return this->search(this->root, key);
}

Node * AVL::search(Node * node, int key)
{
    if(key == node->data || node == NULL)
    {
        return node;
    }
    else if(key > node->data)
    {
        return this->search(node->right, key);
    }
    else if(key < node->data)
    {
        return this->search(node->left, key);
    }
}

bool AVL::insert(int key)
{
    if(this->root == NULL)
    {
        this->root = new Node(key);

        return true;
    }
    else
    {
        this->root = this->insert(this->root, key);
    }
}

Node * AVL::insert(Node * node, int key)
{
    if(node == NULL)
    {
        return new Node(key);
    }

    //BST insert
    if(key < node->data)
    {
        node->left = this->insert(node->left, key);
    }
    else if(key > node->data)
    {
        node->right = this->insert(node->right, key);
    }
    else
    {
        return node;
    }

    //get and set heights
    node->height = 1 + max(
        this->getNodeHeight(node->left),
        this->getNodeHeight(node->right)
    );

    //store balance value
    int balance = this->getBalance(node);

    //LL case
    if(balance > 1 && key < node->left->data)
    {
        return this->rightRotation(node);
    }

    //RR case
    if(balance < -1 && key > node->right->data)
    {
        return this->leftRotation(node);
    }

    //LR case
    if(balance > 1 && key > node->left->data)
    {
        node->left = this->leftRotation(node->left);

        return this->rightRotation(node);
    }

    //RL case
    if(balance < -1 && key < node->right->data)
    {
        node->right = this->rightRotation(node->right);

        return this->leftRotation(node);
    }

    //return if balanced
    return node;
}

int AVL::getNodeHeight(Node * node)
{
    if(node == NULL)
    {
        return 0;
    }
    else
    {
        return node->height;
    }
}

int AVL::getBalance(Node * node)
{
    if(node == NULL)
    {
        return 0;
    }
    else
    {
        return this->getNodeHeight(node->left) - this->getNodeHeight(node->right);
    }
}

Node * AVL::leftRotation(Node * node)
{
    Node * right = node->right;
    Node * rightLeft = right->left;

    //Rotate
    right->left = node;
    node->right = rightLeft;

    //Update heights
    node->height = 1 + max(
        this->getNodeHeight(node->left),
        this->getNodeHeight(node->right)
    );
    right->height = 1 + max(
        this->getNodeHeight(right->left),
        this->getNodeHeight(right->right)
    );

    return right;
}

Node * AVL::rightRotation(Node * node)
{
    Node * left = node->left;
    Node * leftRight = left->right;

    //Rotate
    left->right = node;
    node->left = leftRight;

    //Update heights
    node->height = 1 + max(
        this->getNodeHeight(node->left),
        this->getNodeHeight(node->right)
    );
    left->height = 1 + max(
        this->getNodeHeight(left->left),
        this->getNodeHeight(left->right)
    );

    return left;
}

int AVL::countChildren(Node * node)
{
    int count = 0;

    if(node->left != NULL)
        count++;

    if(node->right != NULL)
        count++;

    return count;
}

bool AVL::remove(int key)
{
    if(this->root == NULL)
    {
        return false;
    }
    else
    {
        return this->remove(this->root, key);
    }
}

Node * AVL::remove(Node * node, int key)
{
    if(node == NULL)
    {
        return node;
    }

    if(key < node->data)
    {
        node->left = this->remove(node->left, key);
    }
    else if(key > node->data)
    {
        node->right = this->remove(node->right, key);
    }
    else
    {
        int childrenCount = this->countChildren(node);

        if(childrenCount == 0)
        {
            delete node;
            node = NULL;
        }
        else if(childrenCount == 1)
        {
            node = node->left ? node->left : node->right;
        }
        else if(childrenCount == 2)
        {
            Node * temp = this->getMinNode(node->right);

            node->data = temp->data;

            node->right = this->remove(node->right, temp->data);
        }
    }

    //handle fringe case from single node removal
    if(node == NULL)
    {
        return node;
    }

    node->height = 1 + max(this->getNodeHeight(node->left), this->getNodeHeight(node->right));

    int balance = this->getBalance(node);

    //check cases as one would with insert:

    //LL case
    if(balance > 1 && key < node->left->data)
    {
        return this->rightRotation(node);
    }

    //RR case
    if(balance < -1 && key > node->right->data)
    {
        return this->leftRotation(node);
    }

    //LR case
    if(balance > 1 && key > node->left->data)
    {
        node->left = this->leftRotation(node->left);

        return this->rightRotation(node);
    }

    //RL case
    if(balance < -1 && key < node->right->data)
    {
        node->right = this->rightRotation(node->right);

        return this->leftRotation(node);
    }

    //return if balanced
    return node;
}

void AVL::show()
{
    this->show(this->root);
}

void AVL::show(Node * node)
{
    if(node->left != NULL)
    {
        this->show(node->left);
    }

    cout << node->data << endl;

    if(node->right != NULL)
    {
        this->show(node->right);
    }
}

int AVL::getHeight()
{
    if(this->root == NULL)
    {
        return 0;
    }
    else
    {
        return this->getHeight(this->root, 1);
    }
}

int AVL::getHeight(Node * node, int height)
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

int AVL::getSize()
{
    if(this->root == NULL)
    {
        return 0;
    }
    else
    {
        return this->getSize(this->root, 0);
    }
}

int AVL::getSize(Node * node, int size)
{
    if(node == NULL)
    {
        return 0;
    }
    else
    {
        return this->getSize(node->left, size) + this->getSize(node->right, size) + 1;
    }
}

bool AVL::check()
{
    return this->check(this->root);
}

bool AVL::check(Node * node)
{
    if(node == NULL)
    {
        return true;
    }

    if(node->left != NULL && node->left->data > node->data)
    {
        return false;
    }

    if(node->right != NULL && node->right->data < node->data)
    {
        return false;
    }

    if(!this->check(node->left) || !this->check(node->right))
    {
        return false;
    }

    return true;
}

Node * AVL::getMinNode(Node * node)
{
    if(node->left != NULL)
    {
        return this->getMinNode(node->left);
    }
    else
    {
        //this is the min node
        return node;
    }
}
