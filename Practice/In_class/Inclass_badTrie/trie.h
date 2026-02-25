#pragma once
#include <string>
#include <iostream>
using namespace std;

class trie
{
private:
	class node
	{
	public:
		bool marked;
		node* children[256];

        // augmentation
        string longest; // longest string in node's subtree

		node()
		{
			marked = false;
			for (int i = 0; i < 256; i++)
				children[i] = nullptr;
            
		}
	};

	node* root;

	//print all strings in p with given
	//prefix pre stuck to front.
	void recDisplay(node* p, string pre)
	{
		if (p == nullptr)
		{
		}
		else
		{
			if (p->marked)
			{
				cout << pre << endl;
			}

			for (int i = 0; i < 256; i++)
			{
				recDisplay(p->children[i], pre + (char)i);
			}
		}
	}


public:
	trie()
	{
		root = new node;
	}

	void insert(string s)
	{
		node* arrow = root;

		for (int i = 0; i < s.size(); i++)
		{
			if (arrow->children[s[i]] == nullptr)
				arrow->children[s[i]]=new node;

			arrow = arrow->children[s[i]];

            if(s.size() > arrow->longest.size())
                arrow->longest = s;
		}

		arrow->marked = true;
	}

	void display()
	{
		recDisplay(root, "");
	}

    string worstCompletion(string pre){
        node* current = root;
        for(int i = 0; i < pre.length(); i++){
            if(current->children[pre[i]]){
                current = current->children[pre[i]];
            }
            else{
                return pre;
            }
        }
        return current->longest;
    }
};
