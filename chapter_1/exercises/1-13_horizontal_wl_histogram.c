#include <stdio.h>
/* Write a program to print a histogram of the lengths of words in its input */
/* horizontal bars */

#define IN 1
#define OUT 0

int main()
{
	int i, c, nwchars, nwords, state;

	nwchars = nwords = 0;
	state = OUT;

	while ((c = getchar()) != EOF)
	{
		if ((state == OUT) && ((c != '\t') && (c != '\n') && (c != ' ')))
		{
			state = IN;
			++nwords;
			++nwchars; 
		}
		else if ((state == IN) && ((c != '\t') && (c != '\n') && (c != ' ')))
		{
			++nwchars;
		}
		else if ((state == IN) && ((c == '\t') || (c == '\n') || (c == ' ')))
		{
			for (i = 0; i < nwchars; ++i)
			{
				printf("%c", '*');
			}
			printf("\n");
			nwchars = 0;
			state = OUT;
		}
		else
		{
			state = OUT;
		}

	}
	printf("%s%d\n", "Number of words: ", nwords);
}
