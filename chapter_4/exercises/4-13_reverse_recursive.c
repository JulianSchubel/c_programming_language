/* Write a recursive version of the function reverse(s), which reverses the string s in place */

#include <stdio.h>
#include <string.h>

void reverse(char * string)
{
    static int i = 0;
    static int len = 0;
    /* If it is the first function call in the stack */
    if(i == 0) {
        len = strlen(string);
    }
    char c;
    if(i < len - 1) {
        c = string[len-1];
        string[len - 1] = string[i];
        string[i] = c;
        ++i;
        --len;
        reverse(string);
    }
    /* We assume a well formed string and len is last index not '\0', so the null terminator is left in place */
}

int main(int argc, char * * argv)
{
    char s[] = "Hello, world!";
    reverse(s);
    printf("%s\n",s);
    return 0;
}
