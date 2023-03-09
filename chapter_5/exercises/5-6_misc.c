/* Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. */

#include <stdio.h>
#include <stdlib.h>

/* reverse: Reverse chars in s. Assumes s is '\0' terminated */
void reverse(char *s) {
    char * t = s;
    char * null_terminator = NULL;
    /* iterate to the end of s */
    while(*t) {
        ++t;
    }
    /* Record the address of the null terminator */
    null_terminator = t;
    /* step back to the first non '\0' char */
    --t;
    /* while the addresses are not the same */
    while(s < t) {
        char c = *s;
        *s = *t;
        *t = c;
        ++s;
        --t;
    }
    *null_terminator = '\0'; 
}

int main(int argc, char *argv[])
{
    char s[] = "ni evil ew dlrow yvrut yspot a s'tI";
    reverse(s);
    printf("%s\n",s);
    return EXIT_SUCCESS;
}
