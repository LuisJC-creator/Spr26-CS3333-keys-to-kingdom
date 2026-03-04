#include <vector>
#include <iostream>
using namespace std;

class minHeap {
    private:
    vector<double> T;

    int parent(int i){
        return (i - 1) / 2;
    }

    void bubbleUp(int index){
        int i = index;
        while(T[i] < T[parent(i)]){
            swap(T[i], T[parent(i)]);
            i = parent(i);
        }
    }

    public:

    void insert(double x){
        // insert in the valid spot
        T.push_back(x);

        // bubble up the problem
        bubbleUp(T.size()-1);

    }

    void testDisplay(){
        for(int i = 0; i < T.size(); i++){
            cout << "Item: " << T[i] << " Index: " << i << endl;
        }
    }
};