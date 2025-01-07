/* each key represents an entry in a pair of parallel arrays */
#include <ctype.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct key {
    char * word;
    int count;
} keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"else", 0},
    {"for", 0},
    {"if", 0},
    {"switch", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

/* keytab is an array of n key objects 
∙sizeof is a compile-time unary operator 
∙sizeof cannot be used in a #if line because the preprocessor does not parse type names
∙ here the expression in #define is not evaluated by the preprocessor so the code here is legal
*/
#define NKEYS sizeof(keytab) / sizeof(struct key)
#define MAXWORD 100

int getword(char *, int);
int binsearch(char *, struct key *, int);
int getch(void);
void ungetch(int);

/* count c keywords */
int main(int argc, char *argv[])
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
                keytab[n].count++;
            }
    }

    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n",
                    keytab[n].count, keytab[n].word);
        }
    }
    return EXIT_SUCCESS;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n) 
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while( low <= high) {
        mid = (low + high)/2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1; 
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

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

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for ( ; --lim > 0; w++) {
        if (!isalnum((*w = getch()))) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

#define BUFSIZE 100
int buf[BUFSIZE];
int bufp = 0;           /* next free position in buf */

/* getch: retrieve a character from the shared buffer if one is present, else from stdin */
int getch(void)         /* get a (possible pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: place a character onto the shared buffer */
void ungetch(int c)     /* push character back on input */
{
    if(bufp >= BUFSIZE) 
        printf("ungetch: too many characters\n");
    else if(c == EOF) {
        printf("EOF: exiting\n");
        exit(EXIT_SUCCESS);
    }
    else 
        buf[bufp++] = c;
}
