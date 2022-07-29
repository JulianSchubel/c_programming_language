#include <stdio.h>
#include "prng.h"

int main(int argc, char * argv[])
{
	int seed = 0;
	printf("Enter a seed value: ");
	fscanf(stdin, "%d", &seed);
	seed_prng(seed);
	printf("%d\n", prng());
	printf("%d\n", prng());
	return 0;
}
