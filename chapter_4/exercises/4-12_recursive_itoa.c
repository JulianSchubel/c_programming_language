/* Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer to a string by calling a recursive routine. */

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

/*itoa_recursive: convert n to characters in s, using a recursive method*/
void itoa_recursive(int n, char s[])
{

    static int i = 0;
    static int sign;
    if(n < 0) /*record sign*/
    {
        n = -n; /*make n positive*/
        sign = 1;
    }
    if(n % 10) {
        s[i++] = abs(n%10) + '0';
        itoa_recursive(n / 10, s);
    }
    else {
        if(sign) {
            s[i++] = '-';
        }
        s[i] = '\0';
        reverse(s);
    }
}

int main(int argc, char * * argv)
{
    char s[5];
    itoa_recursive(-128, s);
    printf("%s\n", s);
    return 0;
}
