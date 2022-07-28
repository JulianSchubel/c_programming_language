#include <stdio.h>
#include <stdlib.h>
#include "set_bits.h"
#include "../../examples/bitwise_operators/bitwise_utils.h"

int main (int argc, char * argv[])
{
	unsigned int x = atoi(argv[1]);
	unsigned int y = atoi(argv[2]);
	int p = atoi(argv[3]);
	int n = atoi(argv[4]);
	unsigned int mask;
	//Create a mask of 1's
	mask = ~(~0 << n);
	//Shifting the mask to correspond to the range in x and inverting such that 0's correspond to our range
	mask = ~(mask << p+1 - n);
	//Set target bits in x to 0;
	x = x & mask;
	//Shifting the rightmost n bits of y to align with the range in x from p
	y = y << p+1 - n;
	//Applying OR to set bits of x to bits of y (x's are zero and therefore take on the value of y)
	x = x | y;
	display_bits(x);
	printf("\n%d", x);
	return 0;
}
