#include "Ex3.h"



float taxiCost(float const km)
{
	float cost = 10000;
	if (km > 1)
	{
		float m = (km - 1) * 1000;
		cost += m / 200 * 1500;
		if (km > 30)
		{
			m = (km - 31) * 1000;
			cost += m / 200 * 100;
		}
	}
	return cost;
}