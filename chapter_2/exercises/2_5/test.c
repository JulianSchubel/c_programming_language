#include <stdio.h>
#include "any.h"

int main(int argc, char * argv[])
{
	printf("%d\n", any(argv[1], argv[2]));
	return 0;
}
