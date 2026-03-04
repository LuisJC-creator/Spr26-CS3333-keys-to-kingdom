
#include <iostream>
#include <string>
#include "heap.h"
using namespace std;

int main()
{
	minHeap H;

	H.insert(50);
	H.insert(12);
	H.insert(7);
	H.insert(64);
	H.insert(52);
	H.insert(16);
	H.insert(11);
	H.insert(17);
	H.insert(37);
	H.insert(90);
	H.insert(61);
	H.insert(5);
	H.insert(43);
	H.insert(3);

	H.testDisplay();


	return 0;
}