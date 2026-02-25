#include "autocompleter.h"

// O(1) constructor
Autocompleter::Autocompleter(){
    root = nullptr;
}

void Autocompleter::insert(string x, int freq){
    Entry tempE;
    tempE.s = x;
    tempE.freq = freq;
    Node* tempN = new Node(tempE);

    if (root == nullptr){
        root = tempN;
    }
    else{
        Node* current = root;
        while(current){
            if(tempN->e.s < current->e.s){
                current = current->left;
            }
            else if(tempN->e.s > current->e){
                current = current->right;
            }
            else {
                
            }
        }

        }
    }
