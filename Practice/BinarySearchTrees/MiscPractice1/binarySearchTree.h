#include <iostream>
#include <vector>
using namespace std;

class binarySearchTree{
    public:
    class node{
        public:
        double data;
        node* left;
        node* right;

        node(double x){
            data = x;
            left = nullptr;
            right = nullptr;
        }
    };

    node* root;

    binarySearchTree(){
        root = nullptr;
    }

    void recInsert(node* &p, double x){
        if(p == nullptr){
            p = new node(x);
        }
        else if(x < p->data)
            recInsert(p->left, x);
        else
            recInsert(p->right, x);
    }
    
    void insert(double x){
        recInsert(root, x);
    }

    int rec_num_leaf(node* p){
        if(p == nullptr){
            return 0;
        }
        else{
            int lC = rec_num_leaf(p->left);
            int rC = rec_num_leaf(p->right);
            
            if(p->left == nullptr && p->right == nullptr){
                // if node is a leaf
                return 1 + lC + rC;
            }
            else 
                return lC + rC;
        }
    }

    int num_leaf(){
        return rec_num_leaf(root);
    }

    void recDisplay(node* p){
        if (p == nullptr){

        }
        else {
            recDisplay(p->left);
            cout << p->data << " ";
            recDisplay(p->right);
        }
    }
    
    void display(){
        recDisplay(root);
        cout << endl;
    }
};