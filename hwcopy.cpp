#include "hwcopy.h"

int main(int argc, char*argv[]) {

	string config_file;
	string doc_root;
	string output_area;
	map<string, string> aliases;		
	
	config_file = "default_config.txt";	

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
				//aliases.push_back(tokens[1]);	
			} 				
			

		}
	}			
		
	copy_files(doc_root, output_area, aliases);	

}

string valid_input_filename(string& filename, string& doc_root, map<string,string>& aliases) {
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
				origin = alias.second;
			} 
		}
		if (dirs[i] == ".." && i>0) {
			dirs.erase(dirs.begin() + (i-1), dirs.begin() + (i+1));
		}
	
	}

	stringstream ss;
	for(size_t i = 0; i < dirs.size(); ++i)	{
	  if(i != 0)
	    ss << "/";
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

			ofstream output_file;
			output_file.open(tokens[1]);
		
			if (input_file.is_open() && output_file.is_open() ) {
				
				string line;			
		
				while ( getline( input_file, line) ) {
				
				output_file<<line<<"\n";				

				}
			}
		}			
	}


}


