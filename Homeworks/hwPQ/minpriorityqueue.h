#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
	// For the mandatory running times below:
	//
	// n is the number of elements in the MinPriorityQueue.
	//
	// Assume that the operations of unordered_map are O(1) time 
	// (they are average case, but not worst-case).

	public:
		// Creates an empty MinPriorityQueue
		MinPriorityQueue()
		{
			// TODO
            // Constructor can be empty, we just need to create the empty internal array, which is done, and nothing else.
		}

		// Returns the number of elements in the MinPriorityQueue.
		//
		// Must run in O(1) time.
		int size()
		{
			// TODO
            // just return the size of the vector of pairs.
            return H.size();
		}	

		// Pushes a new value x with priority p
		// into the MinPriorityQueue.
		//
		// Must run in O(log(n)) time.		 
		void push(T x, int p)
		{
			// TODO
            pair<T, int> temp(x, p);
            H.push_back(temp);
            bubbleUp(H.size()-1);
            
		}

		// Returns the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		// 
		// Must run in O(1) time.
		T front()
		{
			if(H.size() > 0){
                return H[0].first;
            }
            // throw some generic error if front() is called on an empty array.
            throw exception();
            
		}

		// Removes the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		//
		// Must run in O(log(n)) time. 
		void pop()
		{
			// TODO	
            // check array size first, in case someone calls it on something dumb
            if(H.size() == 0){
                throw exception();
            }
            else if(H.size() == 1){ // easy case
                H.pop_back();
            }
            else{ // standard extractMin stuff
                swap(H[0], H[H.size()-1]);
                H.pop_back();
                bubbleDown(0);
            }
		}

		// If x is in the MinPriorityQueue 
		// with current priority at least new_p,  
		// then changes the priority of x to new_p.
		// Undefined behavior otherwise.
		//
		// Must run in O(log(n)) time. 
		void decrease_key(T x, int new_p)
		{
			// TODO
		}

	private:
		// You don't need any other instance variables,
		// but you can add some if you want to.
		vector< pair<T, int> > H; // The heap.
		unordered_map<T, int> I;  // Maps values to their indices in H.

        int parent(int index){
            return (index - 1) / 2;
        }
        
        void bubbleUp(int index){
            // bubble up, insert at available spot (done, now this is called)
            // we need to compare this element against its parent, if it is smaller, swap.
            while(index > 0 && H[index].second < H[parent(index)].second){ // check index > 0 to prevent accessing invalid array indicies.
                swap(H[index], H[parent(index)]);
                index = parent(index);
            }
        }
        
        void bubbleDown(int index){
            int left = 2*index - 1;
            int right = 2*index - 2;
            while(H[index].second > ){
                if()
            }
        }
};

#endif 

