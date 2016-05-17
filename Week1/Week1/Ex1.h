#pragma once 

//INPUT A NUMBER HAS 3 DIGITS AND PRINT ON SCREEN THOSE DIGITS WITH DESCENDING ORDER

#include <list>
#include <cstdio>
#include <conio.h>
#include <math.h>
#include "ClearStdin.h"

using namespace std;

//find no. of digits of a number
int digitNumber(int number);
//Input a number with no. of digits
bool numberInput(int & number, unsigned int noDigit);
//print a number in descending order of it's digits
int descendingOrder(int number);