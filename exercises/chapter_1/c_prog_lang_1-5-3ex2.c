#include <stdio.h>
/* write input to output and remove duplicate spaces */

int main()
{
	int c, last, blanks;

	while ((c = getchar()) != EOF)
	{
		if ((c == ' ') && (last == ' '))			// if c and last are both blanks (i.e two spaces in input)
		{
			while (c == last)						// get the next character until c != last (i.e not two or more consecutive spaces)
			{
				c = getchar(); 
			}
		}
		last = c;
		putchar(c);
	}
}