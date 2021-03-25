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

    cout << "balance: " << mytree.isBalanced() << endl;

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

    cout << "balance: " << mytree.isBalanced() << endl;

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

    cerr << "mytree.clear()" << endl;
    mytree.clear();

    cout << "balance: " << mytree.isBalanced() << endl;

    mytree.print();

    cerr << "empty(): " << mytree.empty() << endl;

    cout << "balance: " << mytree.isBalanced() << endl;

    mytree.remove(28);
    mytree.print();
    mytree.remove(17);
    mytree.print();
    mytree.remove(2);
    mytree.print();

    
    AVLTree<int, int> tenet;
    cerr << "tenet " << endl;

    pair<int, int> T1(1, 1);
    pair<int, int> T2(2, 2);
    pair<int, int> T3(3, 3);
    pair<int, int> T4(4, 4);
    pair<int, int> T5(5, 5);
    pair<int, int> T6(6, 6);
    pair<int, int> T7(7, 7);
    pair<int, int> T8(8, 8);

    cout << "balance: " << mytree.isBalanced() << endl;

    pair<int, int> T9(9, 9);
    pair<int, int> T10(10, 10);
    pair<int, int> T11(11, 11);
    pair<int, int> T12(12, 12);
    pair<int, int> T13(13, 13);
    pair<int, int> T14(14, 14);
    pair<int, int> T15(15, 15);

    tenet.insert(T1);
    tenet.insert(T15);
    tenet.insert(T2);
    tenet.insert(T14);
    tenet.insert(T3);
    tenet.insert(T13);
    tenet.insert(T4);
    tenet.insert(T12);

    cout << "balance: " << mytree.isBalanced() << endl;
    tenet.clear();
    cerr << "empty(): " << mytree.empty() << endl;

    tenet.insert(T5);
    tenet.insert(T11);
    tenet.insert(T6);
    tenet.insert(T10);
    tenet.insert(T7);
    tenet.insert(T9);
    tenet.insert(T8);
    tenet.print();
    pair<int, int> T77(7, 77);
    tenet.insert(T77);
    tenet.print();

    cout << "balance: " << mytree.isBalanced() << endl;

    tenet.clear();
    cerr << "empty(): " << mytree.empty() << endl;
    tenet.print();

    return 0;
}