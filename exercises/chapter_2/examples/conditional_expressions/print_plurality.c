#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	int n = atoi(argv[1]);
	printf("You have %d item%s.\n", n, (n == 1) ? "" : "s");	
	return 0;
}
