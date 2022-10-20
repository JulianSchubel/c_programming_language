/* As written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
#define print(x) \
{\
    printf("%d\n",x);\
}

int buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
int getint(int *pn);

int main(int argc, char * * argv)
{
    int n;     
    printf("%d\n", getint(&n));
    return 0;
}

/* getint: get next integer from input into *pn */
/* Returns EOF for end of file, zero if the next input is not a number, and a positive value if the input contains a valid number */
int getint(int *pn)
{
    int c, sign;
    while (isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        /* holds next character */
        int temp;
        /* check if '+' or '-' is being used as a sign */ 
        if(!isdigit(temp = getch())) {
            ungetch(temp);
            ungetch(c);
            /* return 0: next input is not a number */
            return 0;
        }
        else
            c = temp;
    }
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }
    *pn *= sign; 
    if(c != EOF) {
        ungetch(c);
    }
    return c;
}

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
