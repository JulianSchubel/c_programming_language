#include <stdio.h>
/* count lines in input */

int main()
{
	int c, newline,blanks,tabs;

	newline = blanks = tabs = 0;

	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
		{
			++newline; 
		}
		if (c == ' ')
		{
			++blanks;
		}
		if (c == '\t')
		{
			++tabs;
		}
	}
	printf("\n%s%d\n", "Number of new lines: ", newline);
	printf("%s%d\n", "Number of blanks: ", blanks);
	printf("%s%d\n", "Number of tabs: ", tabs);
}