#include "expand.h"
#include <stdio.h>

int main(int argc, char * argv[])
{
	char string[255] = "A test of expanding a-z or Z-A or 0-9 or a-b-c but not -9 or a-";
	char buffer[255];
	char * p = expand(string, buffer);
	printf("BUFFER VALUE: %s\n", buffer);
	return 0;
}
