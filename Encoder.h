#ifndef ENCODER_H
#define ENCODER_H


#include <string>
#include <fstream>
#include "HuffTree.h"

using namespace std;

class Encoder
{
	private:
		unsigned frequency_table[256];
		string file;
		//FILE * read;
		// You need to add more class memeber and methods
	public:
		//test_file_path is the input (decoded) file
		Encoder(string file_path);
		
		//Fills up the frequency_table array where frequency_table[i] 
		//will contain the frequency of char with ASCII code i		
		void buildFrequencyTable(); 
		
		unsigned * getFrequencyTable();
		//Builds the min head and run the encoding algorithm
		void encode();

		//Generates the encoded file and save it as output_file_path
		void writeEncodedFile(string input_file_path, string output_file_path, HuffTree * hufftree);

		~Encoder();
};

#endif
