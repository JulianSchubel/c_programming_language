/* Suppose that there will never be more than one character of pushback. Modify getch() and ungetch() accordingly. */

#include <stdio.h>
#include <stdlib.h> /* for atof(), exit */
#include <string.h>

int getch(void);
void ungetch(int);
void ungets(char * s);

/* Buffer must be able to contain a non-character value in order to determine "empty" buffer */
int buf = EOF;      /* buffer for ungetch() */

/* getch: retrieve a character from the shared buffer if one is present, else from stdin */
int getch(void)         /* get a (possible pushed back) character */
{
    int c;
    /* If buffer holds a value */
    if(buf != EOF) {
        c = buf;
        buf = EOF;
    }
    /* Buffer is "empty" get a character from stdin */
    else {
        c = getchar();
    }
    return c;
}

/* ungetch: place a character onto the shared buffer */
void ungetch(int c)     /* push character back on input */
{
    /* Buffer not "empty" */
    if(buf != EOF) 
        printf("ungetch: too many characters\n");
    else 
        buf = c;
}

int main(int argc, char * argv[])
{
    /* replace tabs with spaces */
    int c;
    while((c = getch()) != EOF) {
        (c == '\t') ? ungetch(' ') : putchar(c);  
    }
    return 0;
}
