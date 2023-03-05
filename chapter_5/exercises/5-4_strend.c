/* Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s, and zero otherwise */
#include <stdio.h>
#include <stdlib.h>

int strend(char *s, char *t) {
    unsigned int t_len = 0;
    /* increment to the end of t and record it's length */
    while(*t) {
        ++t_len;
        ++t;
    }

    /* incremnt s to its null terminator */
    while(*s) {
        ++s;
    }

    /* loops exit on \0 and so we don't need to include that in t_len if we walk back s and t one char.
     * don't need to comapre \0 as it is a necessary condition for prior loop termination) */
    --s;
    --t;
    /* both s and t point to their last character, now iterate backwards over t_len chars checking for char equality */
    for (; t_len > 0; --t_len) {
        if(*s != *t) {
            return 0;
        }
        --s;
        --t;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    char s[] = "Hello, World!";
    char t[] = "World!";
    int result = strend(s,t);
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return EXIT_SUCCESS;
}
