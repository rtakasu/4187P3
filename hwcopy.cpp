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

		// Open input and output file
		ifstream input_file;
		ofstream output_file;
		input_file.open(tokens[0]);
		output_file.open(tokens[1]);

		if (input_file.is_open() && output_file.is_open() ) {
			
			string line;			
	
			while ( getline( input_file, line) ) {
				
				output_file<<line<<"\n";				

			}

		}	
		

		
	}

}
