#include <iostream>
#include <string>
#include <string.h>
#include "MinHeap.h"
#include "Encoder.h"
#include "Decoder.h"
#include "HuffTree.h"

using namespace std;

void printHelp(){
	cout << "Invalid arguments." << endl;
	cout << "Type \"huffman [mode] [arguments]\" where mode and its arguments are one of the following:" << endl;
	cout << "-e [src] [dest]: encode the source file and place the result into the specified destination" << endl;
	cout << "-d [src] [dest]: decode the source file and place the result into the specified destination" << endl;
	exit(1);
}


int main (int argc, char** argv){
	if (argc != 4) {
		printHelp();
	}
	//Initialize encoder object, which builds frequency table in constructor.
	if (strcmp(argv[1], "-e") == 0) {
	
		Encoder * myencoder = new Encoder(argv[2]);
	
		//Build the MinHeap using this frequency table
		MinHeap * myminheap = new MinHeap();
		for (int i = 0; i < 256; i++) {
			if (myencoder->getFrequencyTable()[i] != 0) {
				TreeNode * node = new TreeNode(i, myencoder->getFrequencyTable()[i]);
				myminheap->insert(node);
			}
		}
	
		//Build Huffman Tree with this MinHeap (by using removeMin())
		HuffTree * myhufftree = new HuffTree(myminheap);
		//myhufftree->buildTree(myminheap);
		// this might be called during buildTree() on the last line? myminheap->removeMin();
		
		//Generate codes using Huffman Tree
		//TODO Codes = generate_codes(myminheap);
		//TODO write_codes_to_file(codes, file, outputFile);
		
		myhufftree->generateCodes(myhufftree->getRoot(), "");
		
		//Using codes and freq table, construct header and compressed text body
		
		myencoder->writeEncodedFile(argv[2],argv[3], myhufftree);
		/*
		ofstream outfile(argv[3], ofstream::binary);
		for (int i = 0; i < 256; i++) {
			if ()
		}
		*/
		delete myhufftree;
		delete myencoder;
		delete myminheap;
		return 0;
	} else if (strcmp(argv[1], "-d") == 0) {
		Decoder * mydecoder = new Decoder(argv[2]);
		MinHeap * myminheap = new MinHeap();
		for (int i = 0; i < 256; i++) {
			if (mydecoder->getFrequencyTable()[i] != 0) {
				TreeNode * node = new TreeNode(i, mydecoder->getFrequencyTable()[i]);
				myminheap->insert(node);
			}
		}
		HuffTree * myhufftree = new HuffTree(myminheap);
		myhufftree->generateCodes(myhufftree->getRoot(), "");
		mydecoder->writeUncompressedFile(argv[2], argv[3], myhufftree);
		delete myhufftree;
		delete mydecoder;
		delete myminheap;
		return 0;
	}
}
