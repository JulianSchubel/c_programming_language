/* Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n bit positions */

/* circular_shift is rightrot extended to cater for leftwards rotation in addition to rightwards */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
        LEFT = 0,
        RIGHT = 1
} circular_shift_direction_t;

int bit_length(unsigned int d)
{
	int n_bits = 0;
	for(; d; d >>= 1)
	{
		n_bits++;
	}
	return n_bits;
}

/* minimum_positions: Returns the minimum number of positional entries required to represent the number n for the given radix (base) */
int minimum_positions(double x, double radix)
{
    x = abs(x);
    if( x != 0 )
    {
        return ( (int) (log(x) / log(radix) + 1 ));
    }
    else
    {
        return 1;
    }
}

void display_bits(unsigned int n)
{
    //Determine the minimum number of positions required to display the number in a base 2 positional number system
    int minimum_bits = minimum_positions(n, 2);
    //Normalizes the number of bits to bytes
    int minimum_bytes = ceil( minimum_bits / (double)8 );
    //Each character represents a single bit. + 1 for null terminator
    int buffer_size = minimum_bytes*8;
    //Allocate buffer_size + 1 memory locations initialized to a value of 0
    unsigned char * bit_pattern = calloc((buffer_size + 1), sizeof(unsigned char));
    //Set the null terminator
    bit_pattern[buffer_size] = '\0';
    //Only accomodating values of n such that n is a member of the positive integers
    unsigned int quotient = n;
    //Determine the value of the integer n in binary
    for (int i = buffer_size-1; i >= 0; --i)
    {
        bit_pattern[i] = 48 + quotient % 2;
        quotient /= 2;
    }
    printf("%s\n", bit_pattern);
    free(bit_pattern);
}

/* circular_shift: rotates x n positions LEFT (0) or RIGHT (1) */
unsigned int circular_shift(unsigned int x, int n, circular_shift_direction_t d)
{
	//display_bits(x);
	int n_bits = ceil(minimum_positions(x,2)/8.0) * 8;
	//Only run if a non 0 number 
	if(n_bits)
	{
		//Prevent redundant rotations
		n = n % n_bits;

		//Circular right shift
		if(n && d == 1)
		{
			unsigned int mask = ~(~0 << n);
			//display_bits(mask);
			unsigned int shifted_bits = x & mask;
			//display_bits(shifted_bits);
			x >>= n;
			x = (shifted_bits << (n_bits - n)) ^ x;
			return x;
		}
		//Circular left shift
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

int main(int argc, char * * argv)
{
    display_bits(circular_shift((unsigned int) atoi(argv[1]), atoi(argv[2]), RIGHT));
    display_bits(circular_shift((unsigned int) atoi(argv[1]), atoi(argv[2]), LEFT));
    return 0;
}
