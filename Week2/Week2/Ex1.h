#include <string>
#include <iostream>
#include <vector>

using namespace std;


//fix the wrong bracket by adding correct bracket to the correct position
string fixBracketString(string);

//return a list of addition bracket position
vector<int> additionBrackets(vector<int>, vector<int>);

//find open and close bracket in bracket string
void bracketFilter(vector<int> &, vector<int> &, const string);