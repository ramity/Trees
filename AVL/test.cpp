#include "./AVL.cpp"
#include "./Node.cpp"

using namespace std;

int main()
{
    AVL * test = new AVL();

    test->insert(0);
    test->insert(2);
    test->insert(4);
    test->insert(6);
    test->insert(8);
    test->insert(1);
    test->insert(3);
    test->insert(5);
    test->insert(7);
    test->insert(9);

    cout << "is this a binary tree?" << endl;
    cout << test->check() << endl;

    cout << "expecting numbers 0..9" << endl;
    test->show();

    cout << "expecting a size of 10" << endl;
    cout << test->getSize() << endl;

    delete test;
    test = NULL;

    test = new AVL(5);

    test->insert(2);
    test->insert(1);
    test->insert(3);
    test->insert(8);
    test->insert(7);
    test->insert(9);

    cout << "expecting a size of 7" << endl;
    cout << test->getSize() << endl;

    cout << "expecting a height of 2" << endl;
    cout << test->getHeight() << endl;

    test->remove(1);

    cout << "outputing tree after deleting 1" << endl;
    test->show();

    test->remove(3);

    cout << "outputing tree after deleting 3" << endl;
    test->show();

    test->remove(7);
    test->remove(9);

    cout << "expecting a height of 1" << endl;
    cout << test->getHeight() << endl;

    cout << "expectinig 2, 5, 8" << endl;
    test->show();

    test->insert(3);
    Node * result = test->search(2);
    cout << "expecting right node of 3" << endl;
    cout << result->right->data << endl;

    delete test;
    delete result;
    test = NULL;
    result = NULL;

    //now for benchmarking

    AVL * big = new AVL(500000);

    int min = 0;
    int max = 1000000;
    int iterations = 500000;
    int collisions = 0;

    //does not guarantee 500k elements due to collisions
    for(int z = 0;z < iterations - 1;z++)
    {
        bool result = big->insert((rand() % (max - min + 1) + min));

        if(!result)
        {
            collisions++;
        }
    }

    cout << "This size should be: " << iterations - collisions << endl;
    cout << big->getSize() << endl;

    delete big;
    big = NULL;
}
