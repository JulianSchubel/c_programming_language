/* Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value? 
 * A: The same as getint, an int representing EOF for end of input, 0 for non-number, 1 for number.
 */

#include <ctype.h>
#include <stdio.h>
#include <math.h>

#define BUFSIZE 100
#define print(x) \
{\
    printf("%.5f\n",x);\
}

double buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
int getfloat(double *pn);

int main(int argc, char * * argv)
{
    double n = 0;
    getfloat(&n);
    printf("%f\n", n);
    return 0;
}


/* getfloat: get next floating point number from input into *pn */
/* Returns EOF for end of file, zero if the next input is not a number, and a positive value if the input contains a valid number */
int getfloat(double *pn)
{
    int c, sign;
    double fractional_part = 0;
    int decimal_points = 0;
    while (isspace(c = getch())) /* skip white space */
       ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
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
    if(c == '.') {
        while(isdigit(c = getch())) {
            fractional_part = 10 * fractional_part + (c-'0');
            ++decimal_points;
        }
        *pn = *pn + (fractional_part / pow(10, decimal_points));
    }
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

