#include "Ex4.h"

void drawTriangle(unsigned int height)
{
	int startPoint, i = 1, j, k = 1;
	if (height > 40 || height <= 0)
	{
		printf("\nCannot draw triangle with this height\n");
		return;
	}
	startPoint = height;
	while (i <= height)
	{
		for (j = 0; j < startPoint; j++)
		{
			printf(" ");
		}
		for (j = 0; j < k; j++)
		{
			printf("*");
		}
		printf("\n");
		startPoint--;
		k += 2;
		i++;
	}
}