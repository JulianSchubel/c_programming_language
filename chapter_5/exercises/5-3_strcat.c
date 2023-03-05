/* Write a pointer version of the function strcat from chapter 2: strcat(s,t) copies the string t to the ned of s */

#include <stdio.h>
#include <stdlib.h>

#define SIZE_S = 6
#define SIZE_T = 9

/* strcat: appends t to s. Assumes the underlying allocation for s is large enough to hold t and that both strings are null terminated */
static void strcat(char * s, char * t) {
    /* increment like this as postfixing will overshoot */
    while(*s) {
        //printf("%p: %c\n", s, *s);
        ++s;
    }
    /* s now points to its null terminator */
    while((*s++ = *t++)) {
        //printf("%p: %c\n", s, *s);
        ;
    }
}

int main(int argc, char *argv[])
{
    char s[6 + 9] = "Hello";
    char t[9] = ", World!";
    strcat(s, t);
    printf("%s\n", s);
    return EXIT_SUCCESS;
}
