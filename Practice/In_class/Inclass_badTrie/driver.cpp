#include <iostream>
#include <fstream>
#include <string>
#include "trie.h"
using namespace std;

int main(){
    // open file
    ifstream infile("words2.txt");
    trie T;

    // read in words from file, insert into trie
    string word;
    int freq;
    while (infile >> word){
        infile >> freq;
        T.insert(word);
    }

    // play the word completion game
    while (true) {
        cout << "Enter a prefix: " << endl;
        string pre;
        cin >> pre;

        cout << "The most likely thing you are typing is: " << T.worstCompletion(pre) << endl;
    }

    return 0;
}