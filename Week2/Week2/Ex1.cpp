#include "Ex1.h"


void bracketFilter(vector<int> & open, vector<int> & close, const string input)
{
	int i = 0;
	for each (char bracket in input)
	{
		if (bracket == '(')
		{
			open.push_back(i);
		}
		if (bracket == ')')
		{
			close.push_back(i);
		}
		i++;
	}
}

string fixBracketString(string inputBracket)
{
	vector<int> oBrac, cBrac, aBrac;
	bracketFilter(oBrac, cBrac, inputBracket);
	aBrac = additionBrackets(oBrac, cBrac);
	for (auto pos : aBrac)
	{
		inputBracket.insert(pos, (pos == 0) ? "(" : ")");
	}
	return inputBracket;
}


vector<int> additionBrackets(vector<int> oBrac, vector<int> cBrac)
{
	int i = 0, j = 0, size = oBrac.size() + cBrac.size();
	vector<int> aBrac;
	while ((i < oBrac.size()) || (j < cBrac.size()))
	{
		if (j == cBrac.size())
		{
			aBrac.push_back(size + aBrac.size());
			i++;
			continue;
		}
		if (i == oBrac.size())
		{
			aBrac.push_back(0);
			j++;
			continue;
		}
		if (oBrac.at(i) > cBrac.at(j))
		{
			aBrac.push_back(0);
			j++;
			continue;
		}
		i++; j++;
	}
	return aBrac;
}