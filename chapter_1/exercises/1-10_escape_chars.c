#include <stdio.h>
/* write out escape characters to make \t (tabs), \b (backspaces), aand \\ (backslashes) visible */

int main ()
{
	int c;

	while ((c = getchar()) != EOF)
	{
		switch (c)
		{
			case '\t':
				putchar('\\');
				putchar('t');
				break;
			case '\b':
				putchar('\\');
				putchar('b');
				break;
			case '\\':
				putchar('\\');
				putchar('\\');
				break;
			default:
				putchar(c);
				break;
		}
	}
}
