/*
Explain the issue of printing the largest negative number in a two's compliment machine given the existing itoa alogrithm.
Modify itoa to print the largest possible negative number (-(2^wordsize-1)) regardless of the machine on which it runs.

Because 1000000 is the two's complement representatin of -128 converting this via n = -n results in the same number:

-128 two's compliment       10000000
one's compliment        01111111
add one             10000000

This means that the number we work with will be negative causing the n /= 10 > 0 condition at the end of the do while loop to fail, yielding only a single pass.
Additionally the character produced by n%10 +'0' stored on the first loop parse will be some character and not necessarily the least significant digit.

Therefore 2 items must be changed:
    1) the > 0 condition - can be removed, which can be safely done as successive floor division (n /= 10) will always approach 0.
    2) the n%10 value in the n%10 + '0' expression must be treated as an absolute value.

*/

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

/*itoa: convert n to characters in s*/
void itoa(int n, char s[])
{
	int i, sign;
	if((sign = n) < 0) /*record sign*/
	{
		n = -n; /*make n positive*/
	}		
	i = 0;
	do { /*generate digits in reverse order*/
		s[i++] = abs(n % 10) + '0'; /*get next digit*/
	} while (n /= 10); /*delete it*/
	if(sign < 0)
	{
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s);	
}
	
int main(int argc, char * argv[])
{
	char s[5];
	itoa(-128, s, 0);
	printf("%s", s);
}
