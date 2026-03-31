#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <queue>
using namespace std;

//Let n = V.size()
//run time: O(n) + O(n) + O(1) = O(n)
void printList(vector<double> V) // O(n)
{
	// #loops*body= n*O(1) = O(n)
	for (int i = 0; i < V.size(); i++) //#loops: n
	{
		cout << V[i] << endl; //O(1)
	}

	cout << endl; //O(1)
}

//run time: O(n)
void printListv2(vector<double> V)
{
	for (auto x : V)
	{
		cout << x << endl;
	}
	cout << endl;
}

//Let n= end-start+1 (number of items in search space)
//run time: O(1)+O(1)+O(n)+O(1) = O(n)
int findSmallest(vector<double> &V, int start, int end) //O(1)
{
	int smallIndex = start; //O(1)

	//run time: #loops*body = n*O(1) = O(n)
	for (int i = start; i <= end; i++) //#loops: n
	{
		if (V[i] < V[smallIndex]) //O(1)
			smallIndex = i;
	}

	return smallIndex; //O(1)
}

//let n=V.size();
//run time: O(1)+O(n^2)=O(n^2)
void selectionSort(vector<double> &V)//O(1)
{
	//run time loop: #loops*body = n*O(n)= O(n^2)
	for (int i = 0; i < V.size(); i++) //#loops: n
	{ //body: O(n)+O(1)=O(n)
		int smallIndex = findSmallest(V, i, V.size() - 1); //O(n)
		swap(V[i], V[smallIndex]); //O(1)
	}
}

//run time: O(1)+O(1)+O(n log n)+O(n log n) = O(n log n)
void heapSort(vector<double>& V) //O(1)
{
	priority_queue<double> H; //a heap!  O(1)

	//step 1: insert all items into the heap
	//run time: #loops*body = n*O(log n) = O(n log n)
	for (int i = 0; i < V.size(); i++) //#loops: n
	{
		H.push(V[i]); //O(log n)
	}

	//step 2: pull items out in sorted order
	//run time: #loops*body = n*O(log n) = O(n log n)
	for (int i = 0; i < V.size(); i++) //#loops: n
	{ //body: O(1)+O(log n)=O(log n)
		V[i] = H.top(); //O(1)
		H.pop(); //O(log n)
	}
}

int main()
{
	vector<double> X;

	X.push_back(15.3);		//At index 0
	X.push_back(8);			//1
	X.push_back(568);		//2
	X.push_back(45);		//3
	X.push_back(3.14);		//4
	X.push_back(93.7);		//5
	X.push_back(703);		//6
	X.push_back(57);		//7
	X.push_back(347.2);		//8
	X.push_back(1.5);		//9
	X.push_back(752);		//10
	X.push_back(57);		//11
	X.push_back(12);		//12
	X.push_back(53);		//13

	//Warmup:
	//Print the list
	//printList(X);


	//Challenge #2:
	//Search list for smallest item:
	//return the index of smallest in specified range

	cout << findSmallest(X, 0, X.size() - 1) << endl;  //9
	cout << findSmallest(X, 5, 8) << endl;   //7
	cout << endl << endl;


	//Challenge #3
	//Sort the list

	selectionSort(X);
	//printList(X);  //should now be sorted


	//Stress test with large list
	int huge = 10000000;
	//int huge = 100;
	vector<double> L;

	for (int i = 0; i < huge; i++)
		L.push_back(rand());

	auto start = chrono::high_resolution_clock::now();
    //selectionSort(L);
    heapSort(L);
	auto finish = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = finish - start;
	cout << "Algorithm took: " << elapsed.count() << endl;

	//printList(L);


	return 0;
}


///Timing code
/*
auto start = chrono::high_resolution_clock::now();
//method to time...
auto finish = chrono::high_resolution_clock::now();

chrono::duration<double> elapsed = finish - start;
cout << "Algorithm took: " << elapsed.count() << endl;
*/