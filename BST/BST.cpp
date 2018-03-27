#include "./BST.h"

#include <algorithm>
#include <stdlib.h>
#include <iostream>

using namespace std;

//Created by:
//Lewis Brown

//This is a class based approach for a basic binary search tree.
//This class will later serve as a starting point for more advanced trees.

BST::BST()
{
    this->root = NULL;
}

BST::BST(int data)
{
    this->root = new Node(data);
}

BST::BST(int data, Node * left, Node * right)
{
    this->root = new Node(data, left, right);
}

Node * BST::search(int key)
{
    return this->search(this->root, key);
}

Node * BST::search(Node * node, int key)
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

bool BST::insert(int key)
{
    if(this->root == NULL)
    {
        this->root = new Node(key);

        return true;
    }
    else
    {
        return this->insert(this->root, key);
    }
}

bool BST::insert(Node *& node, int key)
{
    if(key == node->data)
    {
        return false;
    }
    else if(key > node->data && node->right == NULL)
    {
        node->right = new Node(key);

        return true;
    }
    else if(key < node->data && node->left == NULL)
    {
        node->left = new Node(key);

        return true;
    }
    else if(key > node->data && node->right != NULL)
    {
        this->insert(node->right, key);
    }
    else if(key < node->data && node->left != NULL)
    {
        this->insert(node->left, key);
    }
}

int BST::countChildren(Node * node)
{
    int count = 0;

    if(node->left != NULL)
        count++;

    if(node->right != NULL)
        count++;

    return count;
}

bool BST::remove(int key)
{
    return this->remove(this->root, key);
}

bool BST::remove(Node *& node, int key)
{
    cout << "removing: " << key << endl;

    if(this->root == NULL)
    {
        return false;
    }
    else if(key == node->data)
    {
        int count = this->countChildren(node);

        cout << "children count: " << count << endl;

        if(count == 0)
        {
            delete node;
            node = NULL;
        }
        else if(count == 1)
        {
            Node * save;

            if(node->left != NULL)
            {
                save = node->left;

                delete node->left;
                node->left = NULL;

                node = save;
            }
            else
            {
                save = node->right;

                delete node->right;
                node->right = NULL;

                node = node->right;
            }

            delete save;
            save = NULL;
        }
        else
        {
            Node * leftSideNode = node->left;
            Node * rightSideNode = node->right;

            while(leftSideNode->right != NULL)
            {
                leftSideNode = leftSideNode->right;
            }

            while(rightSideNode->left != NULL)
            {
                rightSideNode = rightSideNode->left;
            }

            //see which value is closer to the one we are trying to replace

            int leftSideNodeDiff = abs(node->data - leftSideNode->data);
            int rightSideNodeDiff = abs(node->data - rightSideNode->data);

            if(leftSideNodeDiff < rightSideNodeDiff)
            {
                //use left side replacement
                Node * save = node->left;

                delete node->left;
                node->left = NULL;

                node = leftSideNode;
                node->left = save;
            }
            else
            {
                //use right side replacement
                Node * save = node->right;

                delete node->right;
                node->right = NULL;

                node = rightSideNode;
                node->right = save;
            }

            delete leftSideNode;
            delete rightSideNode;
            leftSideNode = NULL;
            rightSideNode = NULL;
        }

        return true;
    }
    else if(key < node->data)
    {
        if(node->left == NULL)
        {
            return false;
        }
        else
        {
            return this->remove(node->left, key);
        }
    }
    else if(key > node->data)
    {
        if(node->right == NULL)
        {
            return false;
        }
        else
        {
            return this->remove(node->right, key);
        }
    }
}

void BST::show()
{
    this->show(this->root);
}

void BST::show(Node * node)
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

int BST::getHeight(int height)
{
    if(this->root == NULL)
    {
        return 0;
    }
    else
    {
        return this->getHeight(this->root, height);
    }
}

int BST::getHeight(Node * node, int height)
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

int BST::getSize(int size)
{
    return this->getSize(this->root, size);
}

int BST::getSize(Node * node, int size)
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

bool BST::check()
{
    return this->check(this->root);
}

bool BST::check(Node * node)
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
