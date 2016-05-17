#include <cstdio>
#include <string>

using namespace std;

//normalize a string 
//input: "Hello ,    my name is Hung ."
//output: "Hello, my name is Hung."

//normalize string likes example above
string normalizeString(const string);

//remove all the space at the beginning & the end of a string
string trim(const string);

//remove all the redundant colons & dots
string removeRedundant(const string);