#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>

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
	//std::map<Key, Key> mainMap;
	std::map<Key, std::vector<std::string>> mainMap;
	std::string main(C,'a');
	std::string adder = main;
	int half = C/2;
	bool odd = false;
	if(C % 2 == 1) {
		odd = true;
		//half++;
	}
	adder[half-1] = 'b';
	Key a1d(adder);
	Key base(main);
	unsigned long long numIterations = std::pow(32,half);
	// unsigned long long numIterations = std::pow(2,(5*half));
	//adding firsthalf of all possible entries
	for(int i = 0; i < numIterations; i++) {
		Key encrypt = base.subset_sum(T,false);
		//std::cout << "encrypted is " << encrypt.get_string() << "\n";
		//auto ita = mainMap.find(encrypt); // tag
		//if(ita != mainMap.end()) {
		if(mainMap.count(encrypt) >0 ){
			mainMap[encrypt].push_back(base.get_string());
			//ita->second.push_back(base.get_string());
szsxsx			//base.showString();
		} else {
			std::vector<std::string> mapVector;
			mapVector.push_back(base.get_string());
			//std::pair<Key, std::vector<std::string>> pa(base, mapVector);
			//mainMap.insert(pa);
			//base.shsxssxsxssssxssxsxsxowSsxstring();ssssssxssxsxssxsxsxsxsxssxssssxsxsxsxsxsssxssssxsssxsxsxs
			mainMap[encrypt] = mapVector;
		}
		//mainMap[encrypt] = sxsssxsxssxssxsxsxssxsxssxsxssssxsssssssxssxsxssxsxsxsxsxsxsxs
		  //std::cout << "encrypted value is "<sxssx base.get_string() << "\nsxsxsxssssxsssxssxsxssxsxssxssxsssxsxsssxsxsssxxsxssssxsxsxsxsxssxsxsxsxsxs		  //std::cout << "adder is " << a1d.get_string() << "\n";
		//mainMap[encrypt].showString();
 		//mainMap[base.subset_sum(T,false)].get_string();
		if(i != numIterations -1) {
			base += a1d;
		}
	}
	/*end of the first loop
	*
	*
	*/
	//test to see if there is a value at every key
	// auto ip = mainMap.begin();
	// while(ip != mainMap.end()) {
	// 	for(int i = 0; i < ip->second.size(); i++) {
	// 		std::cout << ip->second[i].get_string() <<"\n";
	// 	}
		
	// 	ip++;
	// }
	std::string addTwo = main;
	addTwo[C-1] = 'b';
	//may need to fix
	if(odd) {
		half++;
	}
	unsigned long long numIterationsTwo = std::pow(32,half);
	// unsigned long long numIterationsTwo = std::pow(2,(5*(C-half)));
	//end potential fix
	
	//std::cout << "Base is " << base.get_string() << "\n";
	Key originalMod(encrypted);
	Key original(encrypted);
	//Key baseTwo = base;
	Key baseTwo(main);

	//baseTwo.showString();
	Key a2d(addTwo);

	//std::cout << "a2d is " << a2d.get_string() << "\n"; 
	for(int j = 0; j < numIterationsTwo; j++) {
		//baseTwo.showString();
		if(j != numIterations -1) {
			baseTwo += a2d;
		}	
		originalMod = original;
		//originalMod.showString();
		//std::cout << "a2d is " << a2d.get_string() << "\n"; 
		Key encrypt = baseTwo.subset_sum(T, false);
		//std::cout << "Base is " << baseTwo.get_string() << "\n";
		// originalMod -= baseTwo;
		 originalMod -= encrypt;
		//std::cout << "target is " << originalMod.get_string() << "\n";
		//auto ipa = mainMap.begin();
		//ipa->first.showString();
		auto it = mainMap.find(originalMod);

		//std::cout <<"key is " << it->first.get_string() << "\n";
		//it->second.showString();
		//mainMap[originalMod].showString();
		if(it != mainMap.end()) {
			//std::cout << "hit" << "\n";
			// it->first.showString();
			for(int k = 0; k < it->second.size(); k++ ) {
				originalMod.set_string(it->second[k]); 
				originalMod += baseTwo;
				originalMod.showString();
			}
		}
	//baseTwo.showString();
	//break;	
	}


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
	Symbol *s = new Symbol(table_filename);
	s->decrypt(encrypted);
	clock_t end = (double) clock();
    double time = (double) (end-start)/CLOCKS_PER_SEC;
	//std::cout<<"Symbol Table took "<< time << " seconds"<< std::endl;
	
	return 0;
}
