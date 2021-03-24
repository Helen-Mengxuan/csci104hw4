#include <iostream>
#include "avlbst.h"

using namespace std;

int main() {

    AVLTree<double, double> mytree;

    pair<double, double> N1(1, 1);
    pair<double, double> N2(2, 2);
    pair<double, double> N3(3, 3);

    mytree.insert(N2);
    mytree.insert(N3);
    mytree.insert(N1);

    mytree.print();

    mytree.remove(2);
    mytree.print();

    mytree.remove(3);
    mytree.print();

    mytree.remove(1);
    mytree.print();

    return 0;
}