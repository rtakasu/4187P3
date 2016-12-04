#ifndef __SANITIZER_H__
#define __SANITIZER_H__

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace std;

int copy_files(string& doc_root, string& output_area, map<string,string>& aliases);

string valid_input_filename(string& filename, string& doc_root, map<string,string>& aliases);

int prepare_output_area(string& output_area);

int clean_output_area(string& output_area);

#endif
