#include <stdio.h>
/* symbolic constants*/

#define LOWER 0
#define UPPER 300
#define STEP 20

/* Print Fahrenheit - Celsius table reverse order. 300 -> 0*/
void fahr_cel_r()
{
	int fahrenheit;

	for (fahrenheit = UPPER; fahrenheit >= LOWER; fahrenheit -= STEP)
	{
		printf("%3d\t%6.1f\n", fahrenheit, (5.0/9.0)*(fahrenheit - 32));
	}
}

int main(int argc, char * * argv)
{
	fahr_cel_r();
	return 0;
}
