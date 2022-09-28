/* Write a versoin of itoa that accepts three arguments instead of two. The third argument is a minimum filed width; the converted nummber must be padded with blanks on the left if necessary to make it wide enough */

#include "itoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * string)
{
        int i, j, len;
        char c;
        len = strlen(string);
        for(i = 0, j = len-1; i < j; ++i, --j)
        {
                c = string[i];
                string[i] = string[j];
                string[j] = c;
        }
}

void itoa(int n, char * s, int min_field_width)
{
	int sign;
	int i = 0;
	((sign = n) < 0) ? (n = -n) : n;	
	do
	{
		s[i++] = abs(n % 10) + '0';
	} while(n /= 10);
	(sign < 0) ? (s[i++] = '-') : 0;
	while(i < min_field_width)
	{
		s[i++] = ' ';
	}
	s[i] = '\0';
	reverse(s);
}

int main(int argc, char * argv[])
{
        char s[5];
        itoa(-128,s,5);
        printf("%s", s);
}

