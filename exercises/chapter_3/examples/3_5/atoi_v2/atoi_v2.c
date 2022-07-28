#include <ctype.h>

/*
 atoi: convert s to integer; version 2
*/
int atoi(char s[])
{
	int i, n, sign;
	/*Skip prefixing white space if any*/
	for( i = 0; issapce(s[i]); ++i )
	{
		;
	}
	/*get sign if any*/
	sign = (s[i] == '-') ? -1 : 1;
	/*skip sign character if any*/
	if(s[i] == '+' || s[i] == '-')
	{
		++i;
	}
	/*get integer part and convert it if any*/
	for(n = 0; isdigit(s[i]); ++i)
	{
		n = 10 * n + (s[i] - 0);
	}
	return sign * n;
}

