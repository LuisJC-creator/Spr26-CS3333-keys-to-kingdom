#include <Autocompleter.h>

Autocompleter::Autocompleter(){
    //
    root = new Node();
}

void Autocompleter::insert(string x, int freq){
    Node* current = root;
    Entry tempE;
    tempE.s = x;
    tempE.freq = freq;
    for(int i = 0; i < x.size(); i++){
        char temp = x[i];
        if(!current->children[temp]){
            current->children[temp] = new Node();
            current->children[temp]->top.push_back(tempE);
            
            // push back all elements of previous node's list
            for(int i = 0; i < current->top.size(); i++){
                current->children[temp]->top.push_back(current->top[i]);
            }

            current=current->children[temp];
        }
        else {
            bool withinList = false;
            current = current->children[temp];
            for(int i = 0; i < current->top.size(); i++){
                if(current->top[i].s == x){
                    withinList == true;
                }
            }
            if(!withinList){
                current->top.push_back(tempE);
                //sort
            }
        }
    }
    current->marked = true;
}

int Autocompleter::recSize(Node* p){

}

int Autocompleter::size(){
    recSize(root);
}

void Autocompleter::completions(string x, vector<string> &T){

}