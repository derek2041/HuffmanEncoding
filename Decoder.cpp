#include <iostream>
#include "Decoder.h"
#include <string>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <bitset>
#include "HuffTree.h"
#include "TreeNode.h"

Decoder::Decoder(string huff_file_path) {
	this->file = huff_file_path;
	buildFrequencyTableFromFile();
}

void Decoder::buildFrequencyTableFromFile() {
	ifstream infile(this->file.c_str(), ifstream::binary);
	//Read # unique chars from header (2 bytes)
	//unsigned int uniquechars = 0;
	infile.read(reinterpret_cast<char*>(&this->uniquechars), 2);
	
	//Read char and frequency from header (1 byte, 4 bytes)
	//to build frequency table
	for (int i = 0; i < uniquechars; i++) {
		unsigned char ch;
		infile.read(reinterpret_cast<char*>(&ch), 1);
		unsigned int freq;
		infile.read(reinterpret_cast<char*>(&freq), 4);
		
		this->frequency_table[ch] = freq;
	}
	infile.close();
}

unsigned * Decoder::getFrequencyTable() {
	return this->frequency_table;
}

void Decoder::decode() {

}

void Decoder::writeUncompressedFile(string input_file_path, string output_file_path, HuffTree * hufftree) {
	ifstream infile(input_file_path.c_str(), ios::binary);
	ofstream outfile(output_file_path.c_str(), ofstream::out);
	unsigned int garbage = 0;
	unsigned char ch;
	unsigned int freq;
	infile.read(reinterpret_cast<char*>(&garbage), 2);
	for (int i = 0; i < this->uniquechars; i++) {
		//unsigned char ch;
		infile.read(reinterpret_cast<char*>(&ch), 1);
		//unsigned int freq;
		infile.read(reinterpret_cast<char*>(&freq), 4);
	}
	/*
	for (int i = 0; i < hufftree->getRoot()->getFrequency(); i++) {
		
	} 
	int i = 0;
	bitset<8> tmp;
	while (i < hufftree->getRoot()->getFrequency()) {
		
	}
	*/
	int numCharsPrinted = 0;
	TreeNode * traverse = hufftree->getRoot();
	unsigned char tmp;
	unsigned char tmp2;
	while (numCharsPrinted < hufftree->getRoot()->getFrequency()) {
		infile.read(reinterpret_cast<char*>(&tmp), 1);
		for (int i = 7; i >= 0; i--) {
			if (numCharsPrinted == hufftree->getRoot()->getFrequency()) {
				break;
			}
			if (((tmp >> i) & 1) == 1) {
				traverse = traverse->getLeft();
			} else if (((tmp >> i) & 1) == 0) {
				traverse = traverse->getRight();
			}
			if (traverse->isLeafNode()) {
				tmp2 = traverse->getVal();
				outfile.put(tmp2);
				numCharsPrinted++;
				traverse = hufftree->getRoot();
			}
		}
	}
	infile.close();
	outfile.close();	
}

Decoder::~Decoder() {
	
}
