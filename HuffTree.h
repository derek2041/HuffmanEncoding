#ifndef HUFFTREE_H
#define HUFFTREE_H

#include "MinHeap.h"
#include "TreeNode.h"
#include <string>

#define MAXCODELENGTH 256
#define BYTESIZE 8

using namespace std;

class HuffTree
{
	private:
		//Add class members and methods	
		TreeNode * root;
		MinHeap * hufftree;
		//string bitstring_table[256];
	public:
		HuffTree(MinHeap * mh);
		string bitstring_table[256];
		//build a hiffman  tree  give a minheap
		void buildTree(MinHeap * mh);

		//generate codes by traversing the huffman tree
		//and store them in an internal data structure (array of strings for example)
		void generateCodes(TreeNode * node, string bitstring);

		//returns root of the tree
		TreeNode * getRoot();
		
		MinHeap * getHuffTree();
		//returns huffman code from  the ascii code
		string getCharCode(int c);
		
		void printHuffmanTree();

		~HuffTree();
		
};


#endif
