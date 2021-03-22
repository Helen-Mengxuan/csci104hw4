#include <iostream>
#include "avlbst.h"

using namespace std;

int main() {

    AVLTree<int, int> mytree;

    pair<int, int> N1(1, 1);
    pair<int, int> N2(2, 2);
    pair<int, int> N3(3, 3);

    cout << "start" << endl;
    mytree.insert(N1);
    cout << "after n1" << endl;
    mytree.insert(N2);
    cout << "after n2" << endl;
    mytree.insert(N3);
    cout << "after n3" << endl;
   

    mytree.print();
    return 0;
}