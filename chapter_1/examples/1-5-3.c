#include <stdio.h>
/* count lines in input */

int main()
{
	int c, newlines;

	newlines = 0;
	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
		{
			++newlines; 
		}
	}
	printf("%s%d\n", "Number of new lines: ", newlines);
}