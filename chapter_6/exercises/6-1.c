/* getword does not properly handle underscores, string constants, comments, or
 * preprocessor control lines. Write a better version */

#include "./getch_ungetch.h"
#include <ctype.h>

#define MAXWORD 100

/* getword: get next word or character from input */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch())) {
        ;
    }

    if (c!=EOF) {
        *w++ = c;
    }

    // if c is not a letter
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for ( ; --lim > 0; w++) {
        // if the char at w is not a letter or number
        if (!isalnum(*w)) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

int main(void)
{
    char word[MAXWORD];
    getword(word, MAXWORD);
    printf("%s\n", word);
    return EXIT_SUCCESS;
}
