/* Add the modulus (%) operator and provisions for negative numbers */

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <string.h>

/* ASCII charset bounds */
#define ASCII_LC_LB 97  /* ASCII lower case lower bound */
#define ASCII_LC_UB 122  /* ASCII lower case upper bound */
#define MAXCOMMAND  10  /* max length for a command */
#define MAXOP       100 /* max size of operand or operator */

#define MAXVAL      100 /* maximum depth of val stack */
#define BUFSIZE     100 /* shared buffer size */

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
int lookup(char * key);

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */


char buf[BUFSIZE];      /* buffer for ungetch() */
int bufp = 0;           /* next free position in buf */

/* Flags */
int sign_flag = 0;          /* indicates a negative value was entered as operand */
int command_flag = 0;       /* indicates that a text command was issued */

enum signals {
    NUMBER = '0',   /* signal that a number was found */
    TOP = 1,        /* print the top operand in the stack */
    DUP,            /* duplicate the top operand in the stack */
    SWP,            /* swap the top two elements of the stack */
    CLR,            /* clear the stack */
    INVALID_KEY     /* Failed to find a key associated with a command */
};

/* Structure to map strings to integer values */
typedef struct symbol_t {
    char * key;
    int value;
} symbol_t;

/* array of symbol_t to form lookup table */
symbol_t lookup_table[] = { 
    {"top", TOP},
    {"dup", DUP},
    {"swp", SWP},
    {"clr", CLR}
};

#define LOOKUP_TABLE_SIZE   (sizeof(lookup_table) / sizeof(symbol_t))   /* Number of keys in the lookup table */

/* lookup: iterate over the lookup table entries and return the integer value associated with a matching string */
int lookup(char * key) 
{
    for(int i = 0; i < LOOKUP_TABLE_SIZE; ++i) { 
        if(strcmp(lookup_table[i].key, key) == 0) {
            return lookup_table[i].value;
        }
    }
    return INVALID_KEY;
}

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
                if(op2 != 0.0) {
                    push((int)pop() % (int)op2);
                }
                else {
                    printf("error: zero divisor\n");
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            case TOP:
                (sp) ? printf("\t%.8g\n", val[sp-1]) : printf("\t%s\n", "error: stack empty\0");
                break;
            case SWP:
                double temp;
                if(sp > 1) {
                    temp = val[sp-1];
                    val[sp-1] = val[sp-2];
                    val[sp-2] = temp;
                }
                else {
                    printf("\t%s\n", "error: insufficient values on the stack\0");
                }
                break;
            case DUP:
                (sp) ? push(val[sp-1]) : push("\t%s\n", "error: stack empty\0");
                break;
            case CLR:
                for(int i = 0; i < MAXVAL; ++i) {
                    val[i] = 0;
                }
                sp = 0;
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
        sign_flag = 0;
        command_flag = 0;
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
    char command[MAXCOMMAND];
    i = 0;
    /* discard white space */
    while((s[i] = c = getch()) == ' ' || c == '\t')
        ;
    /* read ASCII text for commands */
    while(c >= ASCII_LC_LB && c <= ASCII_LC_UB) {
        (!command_flag) ? command_flag = 1 : command_flag;
        command[i++] = c;
        c = getch();
    }
    command[i] = '\0';
    if(command_flag) {
        switch (lookup(command)) {
            case TOP:
                return TOP;
            case DUP:
                return DUP;
            case SWP:
                return SWP;
            case CLR:
                return CLR;
            default:
                return INVALID_KEY;
                break;
        }
        /* stop '\n' case popping after a command entry */
        (c == '\n') ? c = ' ' : c;
    }
    i = 0;
    /* check non digit or '.' characters */
    if(!isdigit(c) && c != '.') {
        /* handle possible sign character */ 
        if(c == '-' || c == '+') {
            int temp = getch();
            if(isdigit(temp) || temp == '.') {
                (c == '-') ? sign_flag = 1 : 0;
                s[i] = c = temp;
            }
            else {
                ungetch(temp);
                return c;
            }
        }
        else
            return c;
    }
    s[++i] = '\0';
    if(isdigit(c))      /* collect integer part */
        while(isdigit(s[i++] = c = getch()))
            ;
    if(c == '.') {      /* collect fractional part */
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

