#include "hwcopy.h"

using namespace std;

int main( int argc, char*argv[] ) {

	ofstream output_file;
	output_file.open(argv[1]);

	if (output_file.is_open()) {
		output_file<<argv[2];
	}		
	

	
	return 0;
}
