#include <iostream>
#include "avlbst.h"
#include <string>

using namespace std;

int main() {

    AVLTree<int, string> mytree;

    pair<int, string> N1(10, "ten");
    pair<int, string> N2(20, "twenty");
    pair<int, string> N3(30, "thirty");
    pair<int, string> N4(15, "fifteen");
    pair<int, string> N5(25, "twenty-five");
    pair<int, string> N6(12, "twelve");
    pair<int, string> N7(5, "five");
    pair<int, string> N8(3, "three");
    pair<int, string> N9(8, "eight"); 
    pair<int, string> N10(28, "twenty-eight");
    pair<int, string> N11(17, "seventeen");
    pair<int, string> N12(2, "two");

    mytree.insert(N1);
    mytree.print();
    mytree.insert(N2);
    mytree.print();
    mytree.insert(N3);
    mytree.print();
    mytree.insert(N4);
    mytree.print();
    mytree.insert(N5);
    mytree.print();
    mytree.insert(N6);
    mytree.print();
    mytree.insert(N7);
    mytree.print();
    mytree.insert(N8);
    mytree.print();
    mytree.insert(N9);
    mytree.print();
    mytree.insert(N10);
    mytree.print();
    mytree.insert(N11);
    mytree.print();
    mytree.insert(N12);
    mytree.print();

    mytree.remove(25);
    mytree.print();
    mytree.remove(30);
    mytree.print();
    mytree.remove(20);
    mytree.print();
    mytree.remove(8);
    mytree.print();
    mytree.remove(10);
    mytree.print();
    mytree.remove(15);
    mytree.print();
    mytree.remove(25);
    mytree.print();
    mytree.remove(12);
    mytree.print();
    mytree.remove(5);
    mytree.print();
    mytree.remove(3);
    mytree.print();
    mytree.remove(28);
    mytree.print();
    mytree.remove(17);
    mytree.print();
    mytree.remove(2);
    mytree.print();

    return 0;
}