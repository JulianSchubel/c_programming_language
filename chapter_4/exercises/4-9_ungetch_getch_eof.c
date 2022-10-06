/* Our getch() and ungetch() do not handle a pushed-back EOF correctly. Decide what their properties ought to be if an EOF is pushed back, then implement your design.
    A: Two possible problems with handling EOF:
    1) The program continues running after an EOF character is pushed back.
        Solution: ungetch() can either ignore or exit on encountering EOF;
    2) The 'buf' array is an array of characters and, depending on machine implementation, this could cause unexpected results (i.e. underflow and non termination).
        Solution: change the type of elements in the 'buf' array to signed integers.

    The former is debatable as to the degree of correctness/incorrectness.
    The latter is more questionable and of greater certainty to be an error, as it contributes to the possibility of unexpected behaviour.
*/

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <string.h>
#include <math.h>

/* ASCII charset bounds */
#define ASCII_LC_LB 97  /* ASCII lower case lower bound */
#define ASCII_LC_UB 122  /* ASCII lower case upper bound */

#define MAXOP       100 /* max size of operand or operator */
#define MAXVAL      100 /* maximum depth of val stack */
#define BUFSIZE     100 /* shared buffer size */
#define VARBUFSIZE  27  /* size of variable value array */

int getch(void);
void ungetch(int);
int getch_old(void);
void ungetch_old(int);

char buf_old[BUFSIZE];      /* buffer for ungetch() */
int buf[BUFSIZE];
int bufp_old = 0;           /* next free position in buf */
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

/* getch: retrieve a character from the shared buffer if one is present, else from stdin */
int getch_old(void)         /* get a (possible pushed back) character */
{
    return (bufp_old > 0) ? buf_old[--bufp_old] : getchar();
}

/* ungetch: place a character onto the shared buffer */
void ungetch_old(int c)     /* push character back on input */
{
    if(bufp_old >= BUFSIZE) 
        printf("ungetch: too many characters\n");
    else 
        buf_old[bufp_old++] = c;
}

int main(int argc, char * * argv)
{
    ungetch_old(EOF);
    int i, c;

   /* c is char: cuases incorrect handling of EOF */
    while((c = getch_old()) != EOF) {
        putchar(c);
    }
    ungetch(EOF);
    return 0;
}
