#include "./getch_ungetch.h"
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

