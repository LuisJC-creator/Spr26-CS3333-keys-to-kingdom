#include "binarySearchTree.h"

int main(){
    binarySearchTree T;
    T.insert(5.5);
    T.insert(2.5);
    T.insert(4.765);
    T.insert(43.5);
    T.insert(10.2);
    T.insert(9.8);
    

    T.display();
    cout << "Num leaes: " << T.num_leaf() << endl;
    return 0;
}