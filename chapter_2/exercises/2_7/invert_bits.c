#include "invert_bits.h"
#include "bitwise_utils.h"

unsigned int invert_bits(unsigned int x, int p, int n)
{
	unsigned int mask = x;
	int p = atoi(argv[2]);
	int n = atoi(argv[3]);
	mask = ~(~0 << n) << p + 1 - n;
	return (x ^ mask);
}
