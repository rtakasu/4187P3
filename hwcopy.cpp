// Rafael Takasu - rgt2108
// Security Architecture and Engineering W4187 HW3

#include "hwcopy.h"

int main(int argc, char*argv[]) {

	string config_file;
	string doc_root;
	string output_area;
	map<string, string> aliases;		
	
	config_file = "default_config.txt";	
	
	// Take in -c to set config file
	int c;
	while( (c = getopt(argc, argv, "c:")) != -1) {
		switch (c) {
			case 'c':
				config_file = optarg;
				break;
			default:
				abort();
		}
	}

	cout<<"Config file: "<<config_file<<"\n";

	// Open and parse config file
	ifstream c_file;
	c_file.open(config_file);

	if (c_file.is_open()) {	
		string line;
		while ( getline( c_file, line) ) {
	
			istringstream iss(line);
			vector<string> tokens;
			copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));		
			if ( tokens[0] == "DocumentRoot") {
				doc_root = tokens[1];
			} else if ( tokens[0] == "OutputArea") {
				output_area = tokens[1];
			} else if ( tokens[0] == "Alias") {
				aliases[tokens[1]] = tokens[2];	
			} 				
		}
	}			
		
	copy_files(doc_root, output_area, aliases);	

}

string valid_input_filename(string& filename, string& doc_root, map<string,string>& aliases) {
	// Check if input filename is valid. If it is valid, return the "real" filename 
	// (processed) file name (ie. /a/../t.txt will be /t.txt)
	// If filename is out of Document root or aliases scopes, return "Invalid" string
		
	string origin;
	origin = doc_root;
	
	string real_filepath;	
	real_filepath = doc_root + "/" + filename;

	vector<string> dirs;	
	boost::split(dirs, real_filepath, boost::is_any_of("/"), boost::token_compress_on);

	int i;
	for (i=0; i<dirs.size() ;i++){
		for (auto const& alias : aliases) {
	   		
			string sub_alias;
			sub_alias = alias.first.substr(1,alias.first.length()-2);
			if (dirs[i] == sub_alias) {
				
				cout<<"Substitute: "<<dirs[i]<<" for "<<alias.second<<"\n";
	
				vector<string> new_origin;	
				boost::split(new_origin, alias.second, boost::is_any_of("/"), boost::token_compress_on);	
				dirs.erase(dirs.begin(), dirs.begin() + (i+1));
				dirs.insert(dirs.begin(), new_origin.begin(), new_origin.end());
				origin = alias.second;
				i=0;
				break;
			} 
		}

		if (dirs[i] == ".." && i>0) {
			dirs.erase(dirs.begin() + (i-1), dirs.begin() + (i+1));
			i=i-2;
		}
	
	}

	stringstream ss;
	for (size_t i = 0; i < dirs.size(); ++i) {
		if (i != 0) {
	   		ss << "/";
		}
	 	ss << dirs[i];
	}	
	real_filepath = ss.str();	
	
	if (real_filepath.substr(0, origin.length()) == origin) {
		cout<<"Real filepath: "<<real_filepath<<"\n";
		return real_filepath;
	} else {
		return "Invalid";
	}
	
}

int copy_files(string& doc_root, string& output_area, map<string,string>&aliases) {
	// Function prompts user for input and output files.
	// Take in input file, check if it is valid, open and retrive its contents.
	// Take in output file name and run 'chroot /copyfile' and send in the 
	// name of output file and contents of the input file. The /copyfile program
	// will copy the contents into the output file inside a chroot jail
	
	while(1) {	
			
		char user_input[100];	

		// Get file names		
		cout << "Input a file name: ";	
		cin.getline(user_input,sizeof(user_input));		
		cout << "Files inputted: " << user_input << "\n";
	
		istringstream iss(user_input);
		vector<string> tokens;
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

		string input_filename;
		input_filename = valid_input_filename(tokens[0], doc_root, aliases);

		if (input_filename == "Invalid") {
			cout<<"File path not under Document Root\n";
		} else {
			
			// Open input and output file
			ifstream input_file;	
			input_file.open(tokens[0]);
			if (input_file.fail()){
				cout<<"file not found\n";
			}
	
			string in_file_string;

			in_file_string = "";
	
			if (input_file.is_open() ) {
				
				string line;			
		
				while ( getline( input_file, line) ) {
					in_file_string = in_file_string + line + "\n";	
					
				}
			}
			
			prepare_output_area(output_area);
			string command;	
			command = "chroot " + output_area + " /copyfile " + tokens[1] + " '" + in_file_string+ "'";			
			system(command.c_str());
			clean_output_area(output_area);

		}			
	}
}

int prepare_output_area(string& output_area) {
	// Prepare the output area for use with chroot. Chroot prevents access to directories outside the chroot
	// jail, so basic dependencies to run the program need to be copied into the new root directory to 
	// run the program inside it

	string command;
	command = "cp ./copyfile " + output_area + ";cd " + output_area + "; mkdir -p bin usr lib lib64; mount --bind /bin ./bin; mount --bind /lib ./lib; mount --bind /lib64 ./lib64; mount --bind /usr ./usr;"; 
	system(command.c_str());	

}

int clean_output_area(string& output_area) {
	// Clean up output directory after using chroot so that just the output files are in it.
	
	string command;
	command = "cd " + output_area + "; umount ./bin ./lib ./lib64 ./usr; rm ./copyfile; rm -rf ./bin ./lib ./lib64 ./usr;"; 
	system(command.c_str());	
	
}

