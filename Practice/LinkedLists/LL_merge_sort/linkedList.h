#include <iostream>
using namespace std;

template <class T>
class linkedList {
public:
  class node {
    public:
    T data;
    node* next;
    
    node(T x){
        data = x;
        next = nullptr;
    }
  };
    node* head;
    node* tail;
    
  
  
  linkedList(){
    head = nullptr;
    tail = nullptr;
    }
  
  ~linkedList(){
      node* current = head;
      while(current != nullptr){
          node* next = current->next;
          delete(current);
          current = next;
      }
      head = nullptr;
      tail = nullptr;
  }
  
  void clear(){
     node* current = head;
    while(current != nullptr){
        node* next = current->next;
        delete(current);
        current = next;
    }
    head = nullptr;
    tail = nullptr;
  }
  
  void push_back(T x){
    node* temp = new node(x);
    if(head == nullptr){
        // list is empty
        head = temp;
        tail = head;
    }
    else if(head == tail){
        head->next = temp;
        tail = temp;
    }
    else{
        tail->next = temp;
        tail = temp;
    }
  }
  
  void print(){
    if(head == nullptr)
        return; // in case someone tries to print empty list.
    else{
        node* current = head;
        while(current != nullptr){
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl; //extra line for list.
    }
   }
    
  void split(linkedList &left, linkedList &right){
    //Split the contents of list A evenly into the two given (initially empty) lists.
	//If the number of items in the list is odd, put the extra item in the first list.
	//Must run in O(n) time, where n is the total number of items in the list.
	
    // don't you dare call this on an empty list check
    if(head == nullptr){
        // why are you doing this bozo
        return;
    }
    
    // calculate the size of the list. (O(n))
    node* current = head; // ptr to start of main list.
    int size = 1;
    while(current->next != nullptr){
        current = current->next;
        size++;
    }
    // this should make size right
	
    // reset current
    current = head;
    int mid = size / 2;
    int count = 1;
   
    if(size % 2 == 0) { // even case, easy
        // add elements first - mid to left list
        while(count <= mid){
            left.push_back(current->data);
            current = current->next;
            count++;
        }
        while(count <= size){
            right.push_back(current->data);
            current = current->next;
            count++;
        }
    }
    else { // odd case, add extra element to the left
            // add elements first - mid to left list
        while(count <= mid+1){
            left.push_back(current->data);
            current = current->next;
            count++;
        }
        while(count < size){
            right.push_back(current->data);
            current = current->next;
            count++;
        }
    }
    // the two lists should have our elements now.
    // clear the current list we don't need it anymore.
    this->clear();
    cout << "Don't get baited, ^ is the previous print" << endl;
    }

    void slowSort(){
        
        if(head == nullptr || head == tail){
            return; // it is empty or already sorted
        }

        node* smallest = head;
        // do selection sort on the list.
        for(node* i = head; i != nullptr; i = i->next){
            // do swaps on the elements after comparison
            smallest = i;
            for(node* j = i->next; j != nullptr; j=j->next){
                if(j->data < smallest->data){
                    smallest = j;
                }
            }
            // once we have our smallest, swap it with i
            T temp = i->data;
            i->data = smallest->data;
            smallest->data = temp;
        }
    }

};