#include "itob.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DECIMAL_SYMBOL_UPPER_BOUND
/* itob(n,s,b): converts the integer n, into a base b character representation stored in the string s */
void itob(int n, char * s, int b)
{
	int remainder, quotient;
	quotient = n;
	//Determine the number of positions to hold the value in the given base
	int positions = ceil(log(n) / log(b));
	//Accommodating for the fact that if n % b == 0 then we will have 1 too few positions.
	( (n%b) == 0) ? ++positions : positions;
	//Create a positional number array
	int * array = malloc(sizeof(int) * positions);
	//Note: technically not required to initialize array elements as we will never traverse beyond an assigned value
	for(int i = 0; i < positions; ++i)
	{
		array[i] = 0;
	}
	for(int i = positions-1; i >= 0; --i)
	{
		remainder = quotient % b;
		quotient = quotient / b;
		array[i] = remainder;
	}
	//traverse from MSP (Most Significant Position) to LSP to give correct order in string
	for(int i = 0; i < positions; ++i)
	{
		if(array[i] <= DECIMAL_SYMBOL_UPPER_BOUND) //i never below 0 therefore only one comparison
		{
			s[i] = '0' + array[i];
		}
		else
		{
			//Use an uppercase letter from the english alphabet for values 10 or greater
			s[i] = 55 + (array[i] % 26);
		}
	}	
	s[positions] = '\0';
	free(array);
}
