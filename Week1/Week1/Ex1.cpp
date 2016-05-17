#include "Ex1.h"

int digitNumber(int number)
{
	int noDigits = 0;
	if (number < 0)
		number = 0 - number;
	while ((number /= 10) > 0)
		noDigits++;
	return ++noDigits;
}

bool numberInput(int & number, unsigned int noDigit)
{
	printf("Input a number with %ld digit(s): ", noDigit);
	if (digitNumber(number) != noDigit)
		return false;
	return true;
}

int descendingOrder(int number)
{
	int noDigit = digitNumber(number);
	int prefix = 1;
	if (number < 0)
	{
		prefix = -1;
		number = 0 - number;
	}
	int digit = 0, orderNum = 0;
	list<int> digitList;
	while (noDigit-- != 0)
	{
		digit = number / (pow(10, noDigit));
		number %= (int) pow(10, noDigit);
		digitList.push_back(digit);
	}
	digitList.sort(); digitList.reverse();
	while (digitList.size())
	{
		orderNum = orderNum * 10 + digitList.front();
		digitList.pop_front();
	}
	return orderNum*prefix;
}