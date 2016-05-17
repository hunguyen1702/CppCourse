#include "Ex2.h"


unsigned int uppercaseCharatersNumber(string const inputString)
{
	unsigned int chNum = 0;
	for each (int ch in inputString)
		if (isupper(ch))
			chNum++;
	return chNum;
}

unsigned int lowercaseCharatersNumber(string const inputString)
{
	unsigned int chNum = 0;
	for each (int ch in inputString)
		if (islower(ch))
			chNum++;
	return chNum;
}