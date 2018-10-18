#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <bitset>
#include "Encoder.h"
#include "TreeNode.h"
#include "HuffTree.h"

Encoder::Encoder(string file_path) {
	this->file = file_path;
	buildFrequencyTable();
}

void Encoder::buildFrequencyTable() {
	unsigned int ch; //unsigned char ch
	FILE * fd = fopen(file.c_str(), "r");
	if (fd != NULL) {
		do {
			ch = fgetc(fd);
			if (ch != EOF && ch < 256 && ch >= 0) {
				frequency_table[ch] = frequency_table[ch] + 1;
			}
		} while (ch != EOF);
		fclose(fd);
	}
}

unsigned * Encoder::getFrequencyTable() {
	return this->frequency_table;
}

void Encoder::encode() {

}

void Encoder::writeEncodedFile(string input_file_path, string output_file_path, HuffTree * hufftree) {
	ofstream outfile(output_file_path.c_str(), ofstream::binary);
	unsigned uniquechars = 0;
	//[[[HEADER]]]
	//write # of unique chars in 2 bytes
	for (int i = 0; i < 256; i++) {
		if (this->frequency_table[i] != 0) {
			uniquechars++;
		}
	}
	bitset<16> tmp(uniquechars);
	unsigned long n = tmp.to_ulong();
	outfile.write(reinterpret_cast<const char*>(&n), 2);

	//write char in 1 byte, frequency in 4 bytes
	for (int i = 0; i < 256; i++) {
		if (this->frequency_table[i] != 0) {		
			bitset<8> tmp3(i);
			unsigned long m = tmp3.to_ulong();
			outfile.write(reinterpret_cast<const char*>(&m), 1);
			
			bitset<32> tmp2(frequency_table[i]);
			unsigned long lmao = tmp2.to_ulong();
			outfile.write(reinterpret_cast<const char*>(&lmao), 4);
		}
	}
	/*		
	unsigned char ch;
	fstream fin(input_file_path.c_str(), fstream::in);
	string buildthis = "";
	while (fin >> noskipws >> ch) {
		buildthis += hufftree->bitstring_table[ch];	
		if (buildthis.length() >= 8) {
			bitset<8> tmp4(buildthis.substr(0,8));

			unsigned long xd = tmp4.to_ulong();

			outfile.write(reinterpret_cast<const char*>(&xd), 1);
			buildthis = buildthis.substr(8);
		}
	}
	buildthis.resize(8,'0');

	bitset<8> tmp4(buildthis);

	unsigned long xd = tmp4.to_ulong();

	outfile.write(reinterpret_cast<const char*>(&xd), 1);
	*/
	unsigned char bit_buffer;
	unsigned char c;
	int bitsInBuffer = 0;
	string code = "";
	fstream fin(input_file_path.c_str(), fstream::in);
	while (fin >> noskipws >> c) {
		code = hufftree->bitstring_table[c];
		for (int i = 0; i < code.length(); i++) {
			bit_buffer = bit_buffer << 1;
			bit_buffer = bit_buffer | (code[i] - '0');
			bitsInBuffer++;
			if (bitsInBuffer == 8) {
				outfile.write(reinterpret_cast<const char*>(&bit_buffer), 1);
				bitsInBuffer = 0;
				bit_buffer = 0;
			}
		}
	}
	if (bitsInBuffer != 8) {
		//pad zeroes
		while (bitsInBuffer != 8) {
			bit_buffer = bit_buffer << 1;
			bitsInBuffer++;
		}		
		outfile.write(reinterpret_cast<const char*>(&bit_buffer), 1);
	}	
	fin.close();
	outfile.close();
}

Encoder::~Encoder() {
	//delete
}
