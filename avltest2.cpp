#include <iostream>
#include "avlbst.h"

using namespace std;

int main(){

    AVLTree<int, int> mytree;

    pair<int, int> N1(1, 1);
    pair<int, int> N2(2, 2);
    pair<int, int> N3(3, 3);
    pair<int, int> N4(4, 4);
    pair<int, int> N5(5, 5);
    pair<int, int> N6(6, 6);
    pair<int, int> N7(7, 7);
    pair<int, int> N8(8, 8);
    pair<int, int> N9(9, 9);
    pair<int, int> N10(10, 10);
    pair<int, int> N11(11, 11);
    pair<int, int> N12(12, 12);
    pair<int, int> N13(13, 13);
    pair<int, int> N14(14, 14);
    pair<int, int> N15(15, 15);

    mytree.insert(N1);
    
    mytree.insert(N2);

    mytree.insert(N3);

    mytree.insert(N4);

    mytree.insert(N5);

    mytree.insert(N6);

    mytree.insert(N7);

    mytree.insert(N8);

    mytree.insert(N9);

    mytree.insert(N10);

    mytree.insert(N11);

    mytree.insert(N12);

    mytree.insert(N13);

    mytree.insert(N14);
    mytree.insert(N15);
    mytree.print();

    if(mytree.isBalanced()){
        cout << "------------------------------------------------------------Balanced tree" << endl;
    }
    else{
        cout << "------------------------------------------------------------   NOT Balanced tree" << endl;
    }


    mytree.remove(1);
    mytree.print();
    mytree.remove(2);
    mytree.print();
    mytree.remove(3);
    mytree.print();
    mytree.remove(4);
    mytree.print();
    mytree.remove(5);
    mytree.print();
    mytree.remove(6);
    if(mytree.isBalanced()){
        cout << "------------------------------------------------------------Balanced tree" << endl;
    }
    else{
        cout << "------------------------------------------------------------   NOT Balanced tree" << endl;
    }
    mytree.print();
    mytree.remove(7);
    mytree.print();
    mytree.remove(8);
    mytree.print();
    mytree.remove(9);
    if(mytree.isBalanced()){
        cout << "------------------------------------------------------------Balanced tree" << endl;
    }
    else{
        cout << "------------------------------------------------------------   NOT Balanced tree" << endl;
    }
    mytree.print();
    mytree.remove(10);
    cout << endl;
    cout << "gap btw remove and print" << endl;
    cout << endl;
    mytree.print();
    mytree.remove(11);
    mytree.print();
    mytree.remove(12);
    mytree.print();
    mytree.remove(13);
    mytree.print();
    mytree.remove(14);
    mytree.print();
    mytree.remove(15);
    mytree.print();
    if(mytree.isBalanced()){
        cout << "------------------------------------------------------------Balanced tree" << endl;
    }
    else{
        cout << "------------------------------------------------------------NOT Balanced tree" << endl;
    }
    mytree.remove(1);
    mytree.print();

    return 0;
}