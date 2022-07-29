#include <stdio.h>
#include <stdlib.h>

int tolower(int argc, char * argv[])
{
	int c = *argv[1];
	return (c >= 65 && c <= 90) ? 97 + (c - 65) : c;
}
