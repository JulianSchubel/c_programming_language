#include <stdio.h>
/* Write a program that prints its input one word per line. */

#define IN 1
#define OUT 0

int main()
{
	int c, words;
	short state;

	words = 0;
	state = OUT;

	while ((c = getchar()) != EOF)
	{
		if ((c != ' ') && (c != '\t') && (c != '\n'))
		{	
			if (state == OUT)
			{
				++words;
			}
			state = IN;
			putchar(c);
		}
		if ((c == '\t') || (c == ' ') || (c == '\n'))
		{
			state = OUT;
			putchar('\n');
		} 
	}
	printf("%s%d\n", "The number of words is: ", words);
}
