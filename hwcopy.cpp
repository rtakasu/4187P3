#include "hwcopy.h"

int main(int argc, char*argv[]) {

	while(1) {		
		char user_input[100];	

		// Get file names		
		cout << "Input a file name: ";	
		cin.getline(user_input,sizeof(user_input));		
		cout << "Files inputted: " << user_input << "\n";
	
		// File name vector	
		istringstream iss(user_input);
		vector<string> tokens;
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

		// Open input file
		ifstream input_file;
		input_file.open(tokens[0]);

		
		

		
	}

}
