#include <stdio.h>
/* symbolic constants*/

#define LOWER 0
#define UPPER 300
#define STEP 20

/* Print Fahrenheit - Celsius table */
void fahr_cel()
{
	int fahrenheit;

	for (fahrenheit = LOWER; fahrenheit <= UPPER; fahrenheit += STEP)
	{
		printf("%3d\t%6.1f\n", fahrenheit, (5.0/9.0)*(fahrenheit - 32));
	}
}

int main(int argc, char * * argv)
{
	fahr_cel();	
	return 0;
}
