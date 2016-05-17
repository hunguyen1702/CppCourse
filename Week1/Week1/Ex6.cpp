#include "Ex6.h"



string normalizeString(const string inputString)
{
	char chBuffer = '\0';
	string outputString = "";
	for each (char ch in inputString)
	{
		if ((chBuffer == ' ' && ch == ' ') || (chBuffer == '.' && ch == '.') || (chBuffer == ',' && ch == ','))
		{
			continue;
		}
		if (chBuffer == ' ' && ((ch == ',') || (ch == '.')))
		{
			outputString = outputString.substr(0, outputString.size() - 1);
		}
		chBuffer = ch;
		outputString.append(1u, ch);
	}
	return removeRedundant(outputString);
}

string trim(string inputString)
{
	size_t first = inputString.find_first_not_of(' ');
	size_t last = inputString.find_last_not_of(' ');
	return inputString.substr(first, (last - first + 1));
}

string removeRedundant(const string inputString)
{
	string outputString;
	char chBuffer = '\0';
	for each (char ch in inputString)
	{
		if ((chBuffer == '.' && ch == '.') || (chBuffer == ',' && ch == ','))
		{
			continue;
		}
		chBuffer = ch;
		outputString.append(1u, ch);
	}
	return outputString;
}