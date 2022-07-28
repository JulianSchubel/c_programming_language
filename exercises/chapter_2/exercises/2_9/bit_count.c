#include "bitwise_utils.h"
/*
int bit_count(unsigned int x)
{
	int count = 0;
	while(x)
	{
		if(x & 1)
		{
			count++;
		}
		x >>= 1;
	}
	return count;
}
*/

//Using the fact that x & (x - 1) eliminates the right most digit of x
int bit_count(unsigned int x)
{
	int count = 0;
	while(x != 0)
	{
		count++;
		x &= (x-1);
	}
	return count;
}
