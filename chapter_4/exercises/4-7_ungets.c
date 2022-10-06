/* Write a routine ungets(s) that will push back an entire string onto the input.
 * Q: Should ungets know about buf and bufp, or should it just use getch? 
 * A: Ungets() should be built on top of ungetch() as this allows for a uniform interface to whatever the underlying buffer data structure is, enabling easier modification and troubleshooting. */

#include <stdio.h>
#include <stdlib.h> /* for atof(), exit */
#include <string.h>

#define BUFSIZE     100 /* shared buffer size */

int getch(void);
void ungetch(int);
void ungets(char * s);

char buf[BUFSIZE];      /* buffer for ungetch() */
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
    else 
        buf[bufp++] = c;
}

/* ungets: push a string onto the shared buffer */
void ungets(char * s)
{
    unsigned long int s_len = strlen(s);
    while(s_len > 0) {
        /* must push last character onto the stack first to preserve order (FILO) */
        ungetch(s[--s_len]);
    }
}

int main(int argc, char * argv[])
{
    char * s = "Hello, world!"; 
    int c;
    ungets(s);
    while((c = getch()) != EOF) {
        putchar(c);
    }
    return 0;
}
