/* Rewrite the function lower, which converts upper case letterss to lower case, with a conditional expression instead of if-else. */
#include <stdio.h>
#include <stdlib.h>

/* lower: converts upper case letters to lower case */
int lower(int argc, char * argv[])
{
	int c = *argv[1];
	return (c >= 65 && c <= 90) ? 97 + (c - 65) : c;
}
