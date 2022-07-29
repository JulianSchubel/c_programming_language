#include "squeeze.h"
#include <stdio.h>

int main(int argc, char * argv[])
{
	char * string = argv[1];
	squeeze(string, *argv[2]);
	printf("%s\n",string);
	return 0;
}
