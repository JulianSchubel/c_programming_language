#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* escape: converts escape characters to visible escape sequences. Copies t to s. Assumes s is large enough to hold t */
void escape(char * s, char * t)
{	
	int j;
	for(int i = 0, j = 0; i < strlen(t); ++i, ++j)
	{
		switch (t[i])
		{
			case '\n':	
				s[j] = '\\';
				j++;
				s[j] = 'n';
				break;
			case '\t':
				s[j] = '\\';
				j++;
				s[j] = 't';
				break;
			case '\v':
				s[j] = '\\';
				j++;
				s[j] = 'v';
				break;
			case '\r':
				s[j] = '\\';
				j++;
				s[j] = 'r';
				break;
			case '\f':
				s[j] = '\\';
				j++;
				s[j] = 'f';
				break;
			default:
				s[j] = t[i];
				break;
		}
	}
}
