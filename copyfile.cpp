#include "hwcopy.h"

using namespace std;

int main( int argc, char*argv[] ) {
	// Takes in an output file as first parameter, and a string with the contents
	// to output to the file as another parameter. Outputs string into file

	ofstream output_file;
	output_file.open(argv[1]);

	if (output_file.is_open()) {
		output_file<<argv[2];
	}		

}
