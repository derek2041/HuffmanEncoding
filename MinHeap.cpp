#include <iostream>
#include <climits>

#include "MinHeap.h"



//implement the methods in MinHeap.h

MinHeap::MinHeap()
{
	
}

void MinHeap::insert(TreeNode * val)
{
	myheap.push_back(val);
	int child = myheap.size()-1;
	int parent = (child-1)/2;
	while (child > 0) {
		if (myheap[child]->getFrequency() >= myheap[parent]->getFrequency()) {
			//No need to swap. Stop upheap.
			break;
		}
		//We need to swap parent and child
		TreeNode * tmp = myheap[child];
		myheap[child] = myheap[parent];
		myheap[parent] = tmp;
		child = parent;
		parent = (child-1)/2;
	}
}

int MinHeap::getSize()
{
	return myheap.size();
}

TreeNode * MinHeap::removeMin()
{
	
	//TreeNode * minkey = heap.front();
	if (myheap.size() == 0) {
		return NULL;
	}
	TreeNode * minkey = myheap.front();
	myheap[0] = myheap.back();
	myheap.pop_back();
	int parent = 0;
	int left = (2*(parent) + 1);
	int right = (2*(parent) + 2);
	while (left < myheap.size()) {
		int minChild = left;
		if (right < myheap.size() && myheap[right]->getFrequency() < myheap[left]->getFrequency()) {
			minChild = right;
		}
		if (myheap[parent]->getFrequency() <= myheap[minChild]->getFrequency()) {
			//No need to swap
			break;
		}
		TreeNode * tmp = myheap[minChild];
		myheap[minChild] = myheap[parent];
		myheap[parent] = tmp;
		parent = minChild;
		left = (2*(parent) + 1);
		right = (2*(parent) + 2);
	}
	return minkey;
}

MinHeap::~MinHeap() {
	
}
