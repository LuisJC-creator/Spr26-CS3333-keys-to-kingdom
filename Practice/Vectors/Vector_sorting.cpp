#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

vector<int> genVec(int size, int seed){
    vector<int> temp;
    srand(seed);
    for(int i = 0; i < size; i++){
        int num = rand() % 100;
        temp.push_back(num);
    }
    return temp;
}

void printVec(vector<int> A){
    for(int i = 0; i < A.size(); i++){
        cout << A[i] << " ";
    }
    cout << " <- End of list." << endl;
}

void slowSort(vector<int> &A){
    int smallest = 0;
    for(int i = 0; i < A.size(); i++){
        int smallest = i;
        for(int j = i+1; j < A.size(); j++){
            if(A[j] < A[smallest])
                smallest = j;
        }
    swap(A[i], A[smallest]);
    }
}



int main(){
    vector<int> temp = genVec(1000, 70);
    printVec(temp);
    slowSort(temp);
    printVec(temp);
    return 0;
}