#include <algorithm>
#include <stdlib.h>
#include <iostream>

using namespace std;

//Created by:
//Lewis Brown

//This is a class based approach for a basic binary search tree.
//This class will later serve as a starting point for more advanced trees.

class BST
{
public:
    BST(int data);
    BST(int data, BST * left, BST * right);
    BST * search(BST * head, int key);
    bool insert(BST * head, int key);
    bool remove(BST * head, int key);

    void show(BST * head);

    int countChildren(BST * head);
    int getHeight(BST * head, int height);
    int getSize(BST * head, int size);

    bool check(BST * head);

    int data;
    BST * left;
    BST * right;
};

BST::BST(int data)
{
    this->data = data;
    this->left = NULL;
    this->right = NULL;
}

BST::BST(int data, BST * left, BST * right)
{
    this->data = data;
    this->left = left;
    this->right = right;
}

BST * BST::search(BST * head, int key)
{
    if(key == head->data || head == NULL)
    {
        return head;
    }
    else if(key > head->data)
    {
        return this->search(head->right, key);
    }
    else if(key < head->data)
    {
        return this->search(head->left, key);
    }
}

bool BST::insert(BST * head, int key)
{
    if(key == head->data)
    {
        return false;
    }
    else if(key > head->data && head->right == NULL)
    {
        head->right = new BST(key);

        return true;
    }
    else if(key < head->data && head->left == NULL)
    {
        head->left = new BST(key);

        return true;
    }
    else if(key > head->data && head->right != NULL)
    {
        this->insert(head->right, key);
    }
    else if(key < head->data && head->left != NULL)
    {
        this->insert(head->left, key);
    }
}

int BST::countChildren(BST * head)
{
    int count = 0;

    if(head->left != NULL)
        count++;

    if(head->right != NULL)
        count++;

    return count;
}

bool BST::remove(BST * head, int key)
{
    if(key == head->data)
    {
        int count = this->countChildren(head);

        if(count == 0)
        {
            delete head;
        }
        else if(count == 1)
        {
            if(head->left != NULL)
            {
                head = head->left;
            }
            else
            {
                head = head->right;
            }
        }
        else
        {
            BST * leftSideBST = head->left;
            BST * rightSideBST = head->right;

            while(leftSideBST->right != NULL)
            {
                leftSideBST = leftSideBST->right;
            }

            while(rightSideBST->left != NULL)
            {
                rightSideBST = rightSideBST->left;
            }

            //see which value is closer to the one we are trying to replace

            int leftSideBSTDiff = abs(head->data - leftSideBST->data);
            int rightSideBSTDiff = abs(head->data - rightSideBST->data);

            if(leftSideBSTDiff < rightSideBSTDiff)
            {
                //use left side replacement
                BST * save = head->left;

                head = leftSideBST;
                head->left = save;
            }
            else
            {
                //use right side replacement
                BST * save = head->right;

                head = rightSideBST;
                head->right = save;
            }
        }

        return true;
    }
    else if(key < head->data)
    {
        if(head->left == NULL)
        {
            return false;
        }
        else
        {
            return this->remove(head->left, key);
        }
    }
    else if(key > head->data)
    {
        if(head->right == NULL)
        {
            return false;
        }
        else
        {
            return this->remove(head->right, key);
        }
    }
}

//opted for in order solution for show method
void BST::show(BST * head)
{
    if(head->left != NULL)
    {
        this->show(head->left);
    }

    cout << head->data << endl;

    if(head->right != NULL)
    {
        this->show(head->right);
    }
}

int BST::getHeight(BST * head, int height)
{
    if(head->left != NULL && head->right != NULL)
    {
        return max(
            this->getHeight(head->left, height + 1),
            this->getHeight(head->right, height + 1)
        );
    }
    else if(head->left != NULL && head->right == NULL)
    {
        return this->getHeight(head->left, height + 1);
    }
    else if(head->left == NULL && head->right != NULL)
    {
        return this->getHeight(head->right, height + 1);
    }
    else if(head->left == NULL && head->right == NULL)
    {
        return height;
    }
}

int BST::getSize(BST * head, int size)
{
    if(head->left != NULL && head->right != NULL)
    {
        return this->getSize(head->left, size + 1) + this->getSize(head->right, size + 1);
    }
    else if(head->left != NULL && head->right == NULL)
    {
        return this->getSize(head->left, size + 1);
    }
    else if(head->left == NULL && head->right != NULL)
    {
        return this->getSize(head->right, size + 1);
    }
    else if(head->left == NULL && head->right == NULL)
    {
        return size;
    }
}

bool BST::check(BST * head)
{
    if(head == NULL)
    {
        return true;
    }

    if(head->left != NULL && head->left->data > head->data)
    {
        return false;
    }

    if(head->right != NULL && head->right->data < head->data)
    {
        return false;
    }

    if(!this->check(head->left) || !this->check(head->right))
    {
        return false;
    }

    return true;

}

int main()
{
    BST * test = new BST(9);

    test->insert(test, 2);
    test->insert(test, 4);
    test->insert(test, 6);
    test->insert(test, 8);
    test->insert(test, 1);
    test->insert(test, 3);
    test->insert(test, 5);
    test->insert(test, 7);

    test->show(test);
}
