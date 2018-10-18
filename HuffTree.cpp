#include <iostream>
#include "HuffTree.h"

HuffTree::HuffTree(MinHeap * mh) {
	this->hufftree = mh;
	buildTree(hufftree);
}
void HuffTree::buildTree(MinHeap * mh) {
	while (mh->myheap.size() > 1) {
		TreeNode * node1 = mh->removeMin();
		unsigned freq1 = node1->getFrequency();

		TreeNode * node2 = mh->removeMin();
		unsigned freq2 = node2->getFrequency();

		TreeNode * internalNode = new TreeNode('$', freq1+freq2);
		internalNode->join(node1, node2);
		
		mh->insert(internalNode);
	}
	this->root = mh->removeMin();
}
void HuffTree::generateCodes(TreeNode * node, string bitstring) {
	//generate the codes from hufftree
	if (node->isLeafNode()) {
		bitstring_table[node->getVal()] = bitstring; 
	}
	if (node->getLeft() != NULL) {
		//bitstring = bitstring + "1";
		generateCodes(node->getLeft(), bitstring + "1");
	}
	if (node->getRight() != NULL) {
		//bitstring = bitstring + "0";
		generateCodes(node->getRight(), bitstring + "0");
	}
}
MinHeap * HuffTree::getHuffTree() {
	return this->hufftree;
}
TreeNode * HuffTree::getRoot() {
	return this->root;
}
string HuffTree::getCharCode(int c) {
	return bitstring_table[c];
}
void HuffTree::printHuffmanTree() {

}
HuffTree::~HuffTree() {
	delete this->root;
}
