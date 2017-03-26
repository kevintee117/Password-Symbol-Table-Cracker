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
	std::map<Key, Key> mainMap;
	std::string main(C,'a');
	std::string adder = main;
	int half = C/2;
	if(C % 2 == 1) {
		half++;
	}
	adder[half-1] = 'b';
	Key base(main);
	long long numIterations = std::pow(32,C/2);
	for(long long i = 0; i < numIterations; i++) {
		mainMap[base.subset_sum(T,false)] = base;
		// std::cout << "encrypted value is "<< base.get_string() << "\n";
		// std::cout << "Regular value is " << base.subset_sum(T, false).get_string() << "\n";
		base += adder;
	}
}

	// std::map<long long,std::vector<long long>> finalMap;
	// long long firstIterator = 1LL << (N/2);
	// long long amountShift = 0;
	// Key lastKey(encrypted);
	// for(long long i = 0; i < firstIterator+1; i++) {
	// 	Key current = longToKey(amountShift);
	// 	//current.showString();
	// 	Key encrypt = current.subset_sum(T,false);
	// 	//encrypted.showString();
	// 	long long decryptedLong = encrypt.keyToLong();
	// 	finalMap[decryptedLong].push_back(amountShift);
	// 	//finalMap[current].push_back(decrypted.get_string());
	// 	//std::cout<< "firstIterator is " << firstIterator << "\n";
	// 	//std::cout<< "amountShift is " << amountShift << "\n";

	// 	amountShift += firstIterator;
	// }
	// long long ending = lastKey.keyToLong();
	// long long counter = firstIterator;
	// if(counter % 2 != 0) {
	// 	counter++;
	// }
	// for(long long i = 0; i < counter; i++)  {
	// 	Key current = longToKey(i);
	// 	Key currentSum = current.subset_sum(T,false);
	// 	long long difference = ending - currentSum.keyToLong();
	// 	if(difference < 0) {
	// 		difference += (1LL << N);
	// 	}
	// 	std::map<long long,std::vector<long long>>::iterator move = finalMap.find(difference);
	// 	if(move != finalMap.end()) {
	// 		for(int j = 0; j < move->second.size(); j++) {
	// 			//std::cout<< "hi" << "\n";
	// 			Key x = longToKey(i+move->second[j]);
	// 			x.showString();
	// 			Key ending = longToKey(result);
	// 			ending.showString();

// void Symbol::subtractKeys(long long ending, long long iterator, long long amountShift, std::map<long long,std::vector<long long>> 
// 	sepMap) {
// 	long long counter = iterator;
// 	if(counter % 2 == 0) {
// 		counter;
// 	}
// 	for(long long i = 0; i < counter; i++)  {
// 		Key current = longToKey(i);
// 		Key currentSum = current.subset_sum(T,false);
// 		long long difference = ending - currentSum.keyToLong();
// 		if(difference < 0) {
// 			difference += (1LL << N);
// 		}
// 		std::map<long long,std::vector<long long>>::iterator move = sepMap.find(difference);
// 		std::cout<< "hi"  << "\n";
// 		if(move != sepMap.end()) {
// 			std::cout<< "hi"  << "\n";

// 			for(int j = 0; j < move->second.size(); j++) {
// 				Key x = longToKey(i+move->second[j]);
// 				x.showString();
// 				//Key ending = longToKey(result);
// 				//ending.showString();
// 			}
// 		}

// 	}
// }
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
long long stringToBits(std::string& encrypted) {
	long long total = 0;
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
	clock_t start = (double) clock();
	Symbol s(table_filename);
	s.decrypt(encrypted);
	clock_t end = (double) clock();
    double time = (double) (end-start)/CLOCKS_PER_SEC;
	std::cout<< time << std::endl;
	
	return 0;
}
