#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "key.hpp"
#include "brute.hpp"

std::string me;
std::string encrypted;
std::string table_filename;
bool verbose = false;

Brute::Brute(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();
}

void Brute::decrypt(const std::string& encrypted){
	 Key k(encrypted);
    char res[C];
    char add[C];

    clock_t start = (double) clock();
    char first = 'a';
    char second = 'b';
    for(int i = 0; i < C ; i++) {
        res[i] = first;
        add[i] = first;
    }
    Key current(res);
    add[C - 1] = second;
    Key adder(add);
    long long length  = std::pow(32, C);
    int i = 0;
    while(i < length) {
        if(current.subset_sum(T, false) == k) {
            current.showString();
            
        }
        current += adder;
        i++;
    }
    clock_t end = (double) clock();
    double time = (double) (end-start)/CLOCKS_PER_SEC;
   // std::cout<< time << std::endl;
}

void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Brute force cracking of Subset-sum password with " 
		<< B << " bits precision\n"
	    << "USAGE: " << me << " <encrypted> <table file> [options]\n"
		<< "\nArguments:\n"
		<< " <encrypted>:   encrypted password to crack\n"
		<< " <table file>:  name of file containing the table to use\n"
		<< "\nOptions:\n"
		<< " -h|--help:     print this message\n"
		<< " -v|--verbose:  select verbose mode\n\n";
	exit(0);
}

void initialize(int argc, char* argv[]) {
	me = argv[0];
	if (argc < 3) usage("Missing arguments");
	encrypted = argv[1];
	table_filename = argv[2];
	for (int i=3; i<argc; ++i) {
		std::string arg = argv[i];
		if (arg == "-h" || arg == "--help") usage();
		else if (arg == "-v" || arg == "--verbose") verbose = true;
		else usage("Unrecognized argument: " + arg);
	}
}


int main(int argc, char *argv[]){	
	initialize(argc, argv);
	Brute b = Brute(table_filename);
	b.decrypt(encrypted);
    // std::string x = "hello";
	// Key k(x);
	// std::cout << k.get_string() << "\n";


	
	
	return 0;
}
