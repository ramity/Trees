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
    bool insert(BST *& head, int key);
    bool remove(BST *& head, int key);

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

bool BST::insert(BST *& head, int key)
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

bool BST::remove(BST *& head, int key)
{
    cout << "removing: " << key << endl;

    if(key == head->data)
    {
        int count = this->countChildren(head);

        cout << "children count: " << count << endl;

        if(count == 0)
        {
            delete head;
            head = NULL;
        }
        else if(count == 1)
        {
            BST * save;

            if(head->left != NULL)
            {
                save = head->left;

                delete head->left;
                head->left = NULL;

                head = save;
            }
            else
            {
                save = head->right;

                delete head->right;
                head->right = NULL;

                head = head->right;
            }

            delete save;
            save = NULL;
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

                delete head->left;
                head->left = NULL;

                head = leftSideBST;
                head->left = save;
            }
            else
            {
                //use right side replacement
                BST * save = head->right;

                delete head->right;
                head->right = NULL;

                head = rightSideBST;
                head->right = save;
            }

            delete leftSideBST;
            delete rightSideBST;
            leftSideBST = NULL;
            rightSideBST = NULL;
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
    if(head == NULL)
    {
        return 0;
    }
    else
    {
        return this->getSize(head->left, size) + this->getSize(head->right, size) + 1;
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

    test->insert(test, 0);
    test->insert(test, 2);
    test->insert(test, 4);
    test->insert(test, 6);
    test->insert(test, 8);
    test->insert(test, 1);
    test->insert(test, 3);
    test->insert(test, 5);
    test->insert(test, 7);

    cout << "is this a binary tree?" << endl;
    cout << test->check(test) << endl;

    cout << "expecting numbers 0..9" << endl;
    test->show(test);

    cout << "expecting a size of 10" << endl;
    cout << test->getSize(test, 0) << endl;

    delete test;
    test = NULL;

    test = new BST(5);

    test->insert(test, 2);
    test->insert(test, 1);
    test->insert(test, 3);
    test->insert(test, 8);
    test->insert(test, 7);
    test->insert(test, 9);

    cout << "expecting a size of 7" << endl;
    cout << test->getSize(test, 0) << endl;

    cout << "expecting a height of 2" << endl;
    cout << test->getHeight(test, 0) << endl;

    test->remove(test, 1);

    cout << "outputing tree after deleting 1" << endl;
    test->show(test);

    test->remove(test, 3);

    cout << "outputing tree after deleting 3" << endl;
    test->show(test);

    test->remove(test, 7);
    test->remove(test, 9);

    cout << "expecting a height of 1" << endl;
    cout << test->getHeight(test, 0) << endl;

    cout << "expectinig 2, 5, 8" << endl;
    test->show(test);

    test->insert(test, 3);
    BST * result = test->search(test, 2);
    cout << "expecting right node of 3" << endl;
    cout << result->right->data << endl;

    delete test;
    delete result;
    test = NULL;
    result = NULL;

    //now for benchmarking

    BST * big = new BST(500000);

    int min = 0;
    int max = 1000000;
    int iterations = 500000;
    int collisions = 0;

    //does not guarantee 500k elements due to collisions
    for(int z = 0;z < iterations - 1;z++)
    {
        bool result = big->insert(big, (rand() % (max - min + 1) + min));

        if(!result)
        {
            collisions++;
        }
    }

    cout << "This size should be: " << iterations - collisions << endl;
    cout << test->getSize(big, 0) << endl;
}
