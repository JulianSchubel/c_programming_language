#include <stdio.h>
/* Arrays */
/* Count digits, white space, others */

int main ()
{
	int c, i, nwhite, nother;
	int ndigit[10];

	nwhite = nother = 0;

	for (i = 0; i < 10; ++i)
	{
		ndigit[i] = 0;
	}

	while ((c = getchar()) != EOF)
	{
		if ((c >= '0') && (c <= '9'))
		{
			++ndigit[c - '0']; //the ASCII numeric value for the charcter '0' is 48. '0', '1', ..., '9', have consecutively increasing numeric values from 48.
		}
		else if ((c == ' ') || (c == '\n') || (c == '\t'))
		{
			++nwhite;
		}
		else
		{
			++nother;
		}
	}
	printf("digits =");
	for (i = 0; i < 10; ++i)
	{
		printf(" %d", ndigit[i]);
	}
	printf(", white space = %d, other = %d\n", nwhite, nother);
}