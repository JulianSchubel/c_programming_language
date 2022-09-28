#include <stdio.h>
#include <stdlib.h>

//Note that the ?: construct is an expression and can be used anywhere an expression is legal.
//Similarly if a and b are different types the expression follows standard conversion rules such that the "widest" types is adopted.
//I.e if f is a float and n a int, the expression (n > 0) ? f : n; is always of type float, regardless of whether the condition (n > 0) is met.

int main(int argc, char * argv[])
{
	int a, b, z;
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	z = (a > b) ? a : b;
	printf("%d\n", z);
	return 0;
}
