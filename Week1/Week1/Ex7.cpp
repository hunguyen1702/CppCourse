#include "Ex7.h"


int greatestCommonDivisor(int const a, int const b)
{
	return a*b / leastCommonMultiple(a, b);
}


int leastCommonMultiple(int const a, int const b)
{
	return (b == 0) ? a : leastCommonMultiple(b, a%b);
}

