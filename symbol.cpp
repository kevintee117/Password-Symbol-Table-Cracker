#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include "key.hpp"
#include "symbol.hpp"

std::string me;
std::string encrypted;
std::string table_filename;
bool verbose = false;

Symbol::Symbol(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();
	
	// insert your code here
}

void Symbol::decrypt(const std::string& encrypted) {
	int middleIndex;
	if(encrypted.size() %2 == 0) {
		middleIndex = encrypted.size()/2;
	} else {
		middleIndex = (encrypted.size()/2) +1;
	}
	//bitMiddleIndex = middleIndex*5;
	//long encryptedBits = stringTobits(encrypted);
	std::string firstHalf = encrypted.substr(0, middleIndex);
	std::string secondHalf = encrypted.substr(middleIndex);
	std::map <Key,std::vector<std::string>> topHalf = runBruteForce(firstHalf.length());
	std::map <Key,std::vector<std::string>> bottomHalf = runBruteForce(secondHalf.length());

	// insert your code here
}
std::map<Key,std::vector<std::string>> Symbol::runBruteForce(int charLen) {
	std::map<Key,std::vector<std::string>> finalMap;
 	//Key k(encrypted);
    char res[charLen];
    char add[charLen];
    char first = 'a';
    char second = 'b';
    for(int i = 0; i < charLen ; i++) {
        res[i] = first;
        add[i] = first;
    }
    Key current(res);
    add[C - 1] = second;
    Key adder(add);
    long long length  = std::pow(32, charLen);
    int i = 0;
	//key is an encrypted(subset sum)key and the value at each key is a vector of unencrypted keys
    while(i < length) {
		Key k = current.subset_sum(T,false);
		if(finalMap.count(k) > 0) {
			finalMap[k].push_back(current.get_string());
		 } else {
			std::vector<Key> valueVector;
			valueVector.push_back(current.get_string());
		}
        //finalMap.insert(std::pair<Key, Key>(k, current))
        current += adder;
        i++;
    }
	return finalMap;
    
}
//converts individual chars from a string into their bit form stored as a char
char charToInt(char x) {
	char returnVal;
	if( x <= 'a') {
		returnVal = x - 'a'; 
	} else {
		returnVal = x - '0' + 26;
	}
	return returnVal;
}
//converts the entire string into bits in long form
long stringToBits(std::string& encrypted) {
	long total = 0;
	char temp;
	for(int i = 0; i < encrypted.size(); i++) {
		total = total << C; //or 5 instead of C
		temp = charToInt(encrypted[i]);
		total += temp;
	}
	return total;
}
void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Symbol table-based cracking of Subset-sum password"
		<< " with " << B << " bits precision\n"
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
	Symbol s(table_filename);
	s.decrypt(encrypted);
	// std::string x = "0";
	// std::cout << stringToBits(x) << "\n";
	
	// insert your code here
	
	return 0;
}
