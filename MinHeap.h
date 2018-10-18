#ifndef MINHEAP_H
#define MINHEAP_H

#include "TreeNode.h"
#include <string>
#include <vector>

using namespace std;

class MinHeap
{
	private:
		int numElements;
		int numMax;
		//vector<TreeNode*> myheap;
	public:
		vector<TreeNode*> myheap;
		MinHeap();
		TreeNode * removeMin(); //returns root of heap
		void insert(TreeNode * val); //adds element to heap
		int getSize(); //returns size of heap
		~MinHeap();
};

#endif
