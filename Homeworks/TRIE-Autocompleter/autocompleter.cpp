#include "autocompleter.h"

Autocompleter::Autocompleter(){
    // blank trees should have one node (the root) with all children poitning to nullptr (handled in the constructor).
    root = new Node();
}

void Autocompleter::updateTop(Node* p, Entry e){
    vector<Entry> &list = p->top; // just make this cleaner to read.
    bool inList = false;
    for(int i = 0; i < list.size(); i++){
        if(e.s == list[i].s)
            inList = true;
    }

    if(!inList){
        // push in new element
        list.push_back(e);

        //sort new list.
        int smallest;
        for(int i = 0; i < list.size(); i++){
            smallest = i;
            for(int j = i+1; j < list.size(); j++){
                if(list[j].freq > list[smallest].freq)
                    smallest = j; // index
            }
            swap(list[i], list[smallest]);
        }

        if(list.size() > 3)
            list.resize(3);
    }
}

void Autocompleter::insert(string x, int freq){
    // create what we need
    Node* current = root;
    Entry tempE;
    tempE.s = x;
    tempE.freq = freq;

    updateTop(root, tempE);
    
    for(int i = 0; i < x.size(); i++){
        char temp = x[i];
        Node* next = current->children[temp];
        if(next){
            updateTop(next, tempE);
            current = next;
        }
        else{
            // create node first
            next = new Node();
            current->children[temp] = next;
            // do things
            updateTop(next, tempE);
            current = next;
        }
    }
    if(current->marked)
        return; // it's a duplicate, helper makes sure we don't add any extra entries.
    else
        current->marked = true;
}

// implementation for my recursive helper.
int Autocompleter::numStrings(Node* p){
    if(p == nullptr){
        return 0;
    }
    
    int count = 0;
    if(p->marked){
        count = 1;
    }

    for(int i = 0; i < 256; i++){
        count += numStrings(p->children[i]);
    }
    return count;

}

int Autocompleter::size(){
    return numStrings(root);
}

void Autocompleter::completions(string x, vector<string> &T){
    Node* current = root;
        for(int i = 0; i < x.length(); i++){
            if(current->children[x[i]]){
                // itereate until you get to the word
                current = current->children[x[i]];
            }
            else{
                // there are no completions.
                T.clear();
                return;
            }
        }
        
        T.clear();
        for(int i = 0; i < current->top.size(); i++){
            // copy all the elements of top into T.
            T.push_back(current->top[i].s);
        }
}