/* Add the modulus (%) operator and provisions for negative numbers */

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

#define MAXVAL  100 /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

#define BUFSIZE     100 

int getch(void);
void ungetch(int);
char buf[BUFSIZE];      /* buffer for ungetch() */
int bufp = 0;           /* next free position in buf */

/* Flags */
int fractional_flag = 0;
int sign_flag = 0;

/* reverse Polish calculator */
int main(int argc, char * * argv)
{
    int type;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                (sign_flag) ? push(-1.0 * atof(s)) : push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                /* '-' not commutative, hence need to enforce order */
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                /* '/' not commutative, hence need to enforce order */
                op2 = pop();
                if(op2 != 0.0) {
                    push(pop() / op2);
                }
                else {
                    printf("error: zero divisor\n");
                }
                break;
            case '%':
                /* 
                    '%' not commutative, hence need to enforce order
                    '%' requires integer operands
                */
                op2 = pop();
                if(op2 != 0.0 && !fractional_flag) {
                    push((int)pop() % (int)op2);
                }
                else if (fractional_flag) {
                    printf("error: modulus requires integer operands\n");
                }
                else {
                    printf("error: zero divisor\n");
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
        fractional_flag = 0;
        sign_flag = 0;
    }
    return 0;
}


/* push: push f onto value pack */
void push(double f)
{
    if(sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}


/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;
    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if(!isdigit(c) && c != '.') {
        /* handle possible sign character */ 
        if(c == '-' || c == '+') {
            int temp = getch();
            if(isdigit(temp)) {
                (c == '-') ? sign_flag = 1 : 0;
                s[0] = c = temp;
            }
            else {
                ungetch(temp);
                return c;
            }
        }
        else
            return c;
    }
    i = 0;
    if(isdigit(c))      /* collect integer part */
        while(isdigit(s[++i] = c = getch()))
            ;
    if(c == '.') {      /* collect fractional part */
        fractional_flag = 1;
        while(isdigit(s[++i] = c = getch()))
            ;
    }
    s[i] = '\0';
    if(c != EOF)
        ungetch(c);
    return NUMBER;
}

int getch(void)         /* get a (possible pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)     /* push character back on input */
{
    if(bufp >= BUFSIZE) 
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
}

