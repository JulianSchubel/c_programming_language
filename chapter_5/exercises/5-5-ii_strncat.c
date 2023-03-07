/* Implement strncat(s, t, n): concatenate at most n chars of t to s terminating in \0 */

#include <stdio.h>
#include <stdlib.h>

/* str_cat_n: concatenate n chars of t to s plus '\0' if the last concatenated char of t was not '\0' */
void str_cat_n(char * s, char * t, unsigned int n) {
    while(*s) {
        ++s;
    }

    /* concatenate */
    while(n--) {
        *s++ = *t++;
    }

    /* Check whether the last char was '\0', that is whether null termination is necessary */
    if(*(--s) != '\0') {
        *(++s) = '\0';
    }
}

int main() {
    char s[15] = "Twas ";
    char t[] = "brillig";
    str_cat_n(s, t, 3);
    printf("%s\n", s);
}
