#include "./AVL.cpp"
#include "./Node.cpp"

using namespace std;

int main()
{
    AVL * test = new AVL();

    cout << "created AVL" << endl;

    test->insert(11);

    cout << "set root to 11" << endl;

    test->insert(22);

    cout << "added 22 to AVL tree" << endl;

    test->insert(33);
    test->insert(44);
    test->insert(55);
    test->insert(27);

    cout << "inserted values" << endl;

    test->show();

    cout << "showed values" << endl;

    test->remove(22);

    cout << "removed 22" << endl;

    test->show();

    cout << "22 should be gone" << endl;

    test->remove(27);

    test->show();

    delete test;
    test = NULL;

    return 0;
}
