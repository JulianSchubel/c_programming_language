#include "bitwise_utils.h"

int bit_length(unsigned int d)
{
	int n_bits = 0;
	for(; d; d >>= 1)
	{
		n_bits++;
	}
	return n_bits;
}

unsigned int circular_shift(unsigned int x, int n, circular_shift_direction_t d)
{
	display_bits(x);
	int n_bits = ceil(minimum_positions(x,2)/8.0) * 8;
	printf("%d\n", bit_length(x));
	//Only run if a non 0 number 
	if(n_bits)
	{
		//Prevent redundant rotations
		n = n % n_bits;

		//Circular right shift
		if(n && d == 1)
		{
			unsigned int mask = ~(~0 << n);
			display_bits(mask);
			unsigned int shifted_bits = x & mask;
			display_bits(shifted_bits);
			x >>= n;
			x = (shifted_bits << (n_bits - n)) ^ x;
			return x;
		}
		//Circular left shit
		else if (n && d == 0)
		{
			unsigned int mask = ~(~0 >> n);
			unsigned int shifted_bits = x & mask;	
			x <<= n;
			x = (shifted_bits >> (n_bits - n)) ^ x;
			return x;
		}
		//If the circular shift would result in a complete period, return the original value x
		else
		{
			return x;
		}
	}
	else
	{
		return 0;
	}
}
