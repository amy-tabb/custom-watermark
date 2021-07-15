#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <vector>
#include <stdlib.h>
#include <inttypes.h>
#include <iostream>
#include <algorithm>
#include <vector>

#include <cmath>
#include <cstdint>

#include <sys/stat.h>

#include <filesystem>

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>

using std::vector;
using std::ifstream;
using std::string;

namespace filesys = std::filesystem;

using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

#include <getopt.h>


bool CheckExistenceOfDirectory(string write_directory){

	bool exists= true;
	struct stat info;
	if( stat( write_directory.c_str(), &info ) != 0 ){
		cout << "Path to directory is wrong and/or cannot access " << write_directory << endl;
		exists = false;
	}

	return exists;

}


void EnsureDirHasTrailingBackslash(string& write_directory){
	int n_letters = write_directory.size();
	bool eval =  (write_directory[n_letters - 1] == '/');
	cout << "Last character compare " << write_directory << " " <<  eval << endl;
	if (eval == false){
		write_directory = write_directory + "/";
	}

}


template<class T>
T FromString(const std::string& s)
{
	std::istringstream stream (s);
	T t;
	stream >> t;
	return t;
}

template<class T>
string ToString(T arg)
{
	std::ostringstream s;

	s << arg;

	return s.str();

}


using namespace std;

bool SortbyLength(string s0, string s1){
	if (s0.length() < s1.length()){
		return true;
	}	else {
		if (s0.length() > s1.length()){
			return false;
		}	else {
			if (s0.compare(s1) < 0){
				return true;
			}	else {
				return false;
			}
		}
	}
}

void ReadDirectory(string dir_name, vector<string>& content_names){

	struct dirent * dp;

	// Enter path to directory existing below

	DIR * dir = opendir (dir_name.c_str());
	string s;
	dp = readdir(dir);
	while ( dp != NULL) {

		if (dp->d_name[0] != '.'){
			s= dp->d_name;
			if (s.at(s.size() - 1) != '~'){
				content_names.push_back(dp->d_name);
				//cout << "Reading ..." << dp->d_name << endl;
			}
		}

		dp = readdir(dir);
	}
	closedir (dir);

	std::sort(content_names.begin(), content_names.end(), SortbyLength);

	for (int i = 0; i < int(content_names.size()); i++){
		cout << "Sorted order .... " << content_names[i]<< endl;
	}

}


int main(int argc, char** argv) {

	// hardcoded item # 1
	std::uintmax_t maxfilesize = 10*1000000;

	/////////////////////////////************************************/////////////////////////////
	string read_directory = "";

	ifstream in;
	ofstream out;

	// hardcoded item # 2
	string watermark_directory = "/home/atabb/Pictures/KeepStamps";

	// hardcoded item #3
	string watermark_filename = "trans_stamp3.png";
	int print_help = 0;


	while (1)
	{
		static struct option long_options[] =
		{
				{"help",   no_argument,       &print_help, 1},
				/* These options don’t set a flag.
				             We distinguish them by their indices. */
				{"input",   required_argument, 0, 'a'},

		};


		if (print_help == 1){
			cout << "Printing help for custom-watermark" << endl;


			cout << endl;
			cout << "DIRECTORIES AND PATHS ----------------------- " << endl;
			cout << std::left << setw(30) << "--input=[STRING] "<< "Mandatory, has to be a directory." << endl;

			exit(1);
		}
		/* getopt_long stores the option index here. */
		int option_index = 0;
		int opt_argument;

		opt_argument = getopt_long (argc, argv, "a",
				long_options, &option_index);

		/* Detect the end of the options. */
		if (opt_argument == -1)
			break;

		switch (opt_argument)
		{
		case 0:
			if (long_options[option_index].flag != 0)
				break;
			printf ("option %s", long_options[option_index].name);
			if (optarg)
				printf (" with arg %s", optarg);
			printf ("\n");
			break;

		case 'a':
			read_directory = optarg;
			break;
		default: {
			cout << "This argument is not handled by the program.  Exiting." << endl; exit(1);
		}
		break;

		}

	}

	if (read_directory.size() == 0){
		cout << "Please enter a read directory --input=[STRING] argument.  Use --help to see the options." << endl; exit(1);
	}

	/// check that both directories exist first.
	if (!CheckExistenceOfDirectory(read_directory)){
		exit(1);
	}

	EnsureDirHasTrailingBackslash(read_directory);
	EnsureDirHasTrailingBackslash(watermark_directory);


	vector<string> image_names;
	ReadDirectory(read_directory, image_names);

	string filename, new_filename;

	string command;

	int n = image_names.size();

	//	exiftool -imagewidth DSC_1014.jpg
	//	Image Width                     : 3846

	string temp;

	int imagewidth, imageheight;

	int stamp_width; int stamp_height;

	string write_name;

	for (int i = 0; i < n; i++){
		filename = read_directory + image_names[i];

		filesys::path currentPath(filename);

		filesys::path ext = currentPath.extension();

		cout << "Extension " << ext.c_str() << endl;

		bool image_file = false;

		// image filename extensions, hitting the highlights here.
		strcmp(ext.c_str(), ".png") == 0 ? image_file = true : 0;

		strcmp(ext.c_str(), ".jpg") == 0 ? image_file = true : 0;

		strcmp(ext.c_str(), ".jpeg") == 0 ? image_file = true : 0;

		strcmp(ext.c_str(), ".JPG") == 0 ? image_file = true : 0;

		cout << "image file " << filename << " " << image_file << endl;
		if (image_file == true){

			string templogfile = read_directory + "out" + ToString<int>(i) + ".txt";

			command = "exiftool -imagewidth " + filename + " > " + templogfile;

			system(command.c_str());

			in.open(templogfile.c_str());

			in >> temp; //cout << "temp 0 "
			in >> temp;
			in >> temp;
			in >> temp;

			in.close();

			imagewidth = FromString<int>(temp);

			// do imageheight too.
			command = "exiftool -imageheight " + filename + " > " + templogfile;

			system(command.c_str());

			in.open(templogfile.c_str());

			in >> temp; //cout << "temp 0 "
			in >> temp;
			in >> temp;
			in >> temp;

			in.close();

			imageheight = FromString<int>(temp);

			// hardcoded item #4
			// landscape
			if (imageheight < imagewidth){
				stamp_width = round(double(imagewidth)*0.12);  //(*.12)
				stamp_height = round(double(stamp_width)/3.2);
			}	else {
				// portrait
				stamp_width = round(double(imagewidth)*0.22);  //(*.12)
				stamp_height = round(double(stamp_width)/3.2);
			}

			// hardcoded item #5, where the watermark will be placed.
			command = "composite " + watermark_directory + watermark_filename + " " + filename + " -gravity southeast -geometry "
					+ ToString<int>(stamp_width) + "x" + ToString<int>(stamp_height) + "+10+10 " + read_directory + "water-" + image_names[i];

			cout << command << endl;


			system(command.c_str());


			command = "rm " + templogfile;

			system(command.c_str());

			string watermarkedFilename = read_directory + "water-" + image_names[i];
			filesys::path watermarkedPath(watermarkedFilename);

			std::uintmax_t filesize = filesys::file_size(watermarkedPath);

			// 1 MB to 1000000 bytes. so

			cout << "Current size as a proportion, " << float(filesize)/float(maxfilesize) << endl;
			while (filesize > maxfilesize){

				command = "convert " + watermarkedFilename + " -resize 85% " + watermarkedFilename;

				system(command.c_str());
				filesize = filesys::file_size(watermarkedPath);

				cout << "Current in the resize loop. " << float(filesize)/float(maxfilesize) << " over " << endl;

			}

		}
	}



	return 0;
}

