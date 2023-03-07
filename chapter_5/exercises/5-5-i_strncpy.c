/* Write version of the library functions strncpy, strncat, and strncmp, which operate on at most n characters of their argument strings. Pad s with \0 if t has < n chars */

#include <stdio.h>
#include <stdlib.h>

/* str_cpy_n: Copy at most n characters of t to s. It is assumed s and t are \0 terminated, and s can hold n additional chars. */
void str_copy_n(char * s, char * t, unsigned int n) {
    /* Iterate to the end of s */
    while(*s) {
        ++s;
    }

    /* Get the length of t */
    char * temp = t;
    while(*temp++) {
        ;
    }
    /* calculate difference in address to get t's length */
    unsigned int t_len = temp - t;

    /* determine extent of padding requirements */
    unsigned int pad_n = (n - t_len > 0) ? n - t_len : 0;

    for(; n > pad_n; --n) {
        *s++ = *t++;
    }
    /* Pad with \0 for pad_n chars in excess of t's length */
    for(; pad_n > 0; --pad_n) {
        *s++ = '\0';
    }
}

int main() {
    char s[25] = "Hello,";
    char t[] = " World!";
    str_copy_n(s, t, 8);
    printf("%s\n", s);
}
