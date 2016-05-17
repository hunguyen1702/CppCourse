#include "Ex5.h"


bool isLeapYear(unsigned int year)
{
	return (((year % 400) == 0) || (((year % 4) == 0) && ((year % 100) != 0))) ?  true : false;
}


bool isValidDay(unsigned int day, unsigned int month, unsigned int year)
{
	if (year < 0)
	{
		return 0;
	}
	else
	{
		if ((month < 0) || (month > 12))
		{
			return 0;
		}
		else
		{
			switch (month)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if ((day < 0) || (day > 31))
				{
					return 0;
				}
			case 4:
			case 6:
			case 9:
			case 11:
				if ((day < 0) || (day > 30))
				{
					return 0;
				}
			case 2:
				if (isLeapYear(year))
				{
					if ((day < 0) || (day > 29))
					{
						return 0;
					}
				}
				else {
					if ((day < 0) || (day > 28))
					{
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

