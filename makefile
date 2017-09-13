all:
	g++ -std=c++11 -DUSE_8_CHARS -o encrypt encrypt.cpp
	g++ -std=c++11 -O2 -DUSE_8_CHARS -o symbol symbol.cpp
