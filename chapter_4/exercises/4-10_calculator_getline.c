/* An alternative organization uses getline to read an entire input line; this makes getch and ungetch unnecessary. Revise the calculator to use this approach. */

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

int getop(char []);
void push(double);
double pop(void);
int lookup(char * key);
void help(void);

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */

char buf[BUFSIZE];      /* buffer for ungetch() */
int bufp = 0;           /* next free position in buf */

size_t input_size = 0;
int input_index = 0;
char * input;

double variable_values[VARBUFSIZE];     /* contains the value of a set variable */
int var_index;

/* Flags */
int sign_flag = 0;      /* indicates a negative value was entered as operand */
int text_input_flag = 0;/* indicates that a text command was issued */

enum signals {
    NUMBER = '0',       /* signal that a number was found */
    TOP = 100,          /* print the top operand in the stack */
    DUP,                /* duplicate the top operand in the stack */
    SWP,                /* swap the top two elements of the stack */
    CLR,                /* clear the stack */
    SIN,                /* calls the sin(double) library function on the top operand in the stack */
    ASIN,               /* calls the asin(double) library function on the top operand in the stack */
    COS,                /* calls the cos(double) library function on the top operand in the stack */
    ACOS,               /* calls the acos(double) library function on the top operand in the stack */
    TAN,                /* calls the tan(double) library function on the top operand in the stack */
    ATAN,               /* calls the atan(double) library function on the top operand in the stack */
    SQRT,               /* calls the sqrt(double) library function on the top operand in the stack */
    EXP,                /* calls the exp(double) library function (base-e exponentiation) on the top operand in the stack */
    POW,                /* calls the pow(double double) library function on the top to elements of the stack*/
    VAR,                /* indicates a variable has been encountered */
    RESULT,             /* pushes the most recently printed (popped) value onto the stack */
    QUIT,               /* terminates the program */
    INVALID_KEY         /* failed to find a key associated with a command */
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
    {"clr", CLR},
    {"sin", SIN},
    {"asin", ASIN},
    {"cos", COS},
    {"acos", ACOS},
    {"tan", TAN},
    {"atan", ATAN},
    {"sqrt", SQRT},
    {"exp", EXP},
    {"pow", POW},
    {"result", RESULT},
    {"quit", QUIT}
};

#define LOOKUP_TABLE_SIZE   (sizeof(lookup_table) / sizeof(symbol_t))   /* Number of keys in the lookup table */

/* reverse Polish calculator */
int main(int argc, char * * argv)
{
    int type;
    double op2;
    char s[MAXOP];
    while(getline(&input, &input_size, stdin) != EOF) {
        while((type = getop(s)) != '\0') {
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
                case '=':
                    /* variable assignment */
                    op2 = pop();
                    /* pop off variable value */
                    pop();
                    variable_values[var_index] = op2; 
                    push(op2);
                    break;
                case '\n':
                    {
                        double result = pop();
                        variable_values[VARBUFSIZE-1] = result;
                        printf("\t%.8g\n", result);
                    }
                    break;
                case TOP:
                    (sp) ? printf("\t%.8g\n", val[sp-1]) : printf("\t%s\n", "error: stack empty\0");
                    break;
                case SWP:
                    if(sp > 1) {
                        double temp;
                        temp = val[sp-1];
                        val[sp-1] = val[sp-2];
                        val[sp-2] = temp;
                    }
                    else {
                        printf("\t%s\n", "error: insufficient values on the stack\0");
                    }
                    break;
                case DUP:
                    (sp) ? push(val[sp-1]) : printf("\t%s\n", "error: stack empty\0");
                    break;
                case CLR:
                    for(int i = 0; i < MAXVAL; ++i) {
                        val[i] = 0;
                    }
                    sp = 0;
                    break;
                case SIN:
                    push(sin(pop())); 
                    break;
                case ASIN:
                    push(asin(pop()));
                    break;
                case COS:
                    push(cos(pop()));
                    break;
                case ACOS:
                    push(acos(pop()));
                    break;
                case TAN:
                    push(tan(pop()));
                    break;
                case ATAN:
                    push(atan(pop()));
                    break;
                case SQRT:
                    push(sqrt(pop()));
                    break;
                case EXP:
                    push(exp(pop()));
                    break;
                case POW:
                    op2 = pop();
                    push(pow(pop(), op2));
                    break;
                case VAR:
                    var_index = (int)s[0] - ASCII_LC_LB;
                    push(variable_values[var_index]);
                    break;
                case RESULT:
                    push(variable_values[VARBUFSIZE-1]);
                    break;
                case QUIT:
                    exit(EXIT_SUCCESS);
                    break;
                case INVALID_KEY:
                default:
                    printf("error: unknown command %s\n", s);
                    break;
            }
            sign_flag = 0;
            text_input_flag = 0;
        }
        input_index = 0;
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
    i = 0;
    /* discard white space */
    while((s[i] = c = input[input_index++]) == ' ' || c == '\t')
        ;
    /* read ASCII text for commands */
    while(c >= ASCII_LC_LB && c <= ASCII_LC_UB) {
        (!text_input_flag) ? text_input_flag = 1 : text_input_flag;
        s[i++] = c;
        c = input[input_index++];
    }
    if(text_input_flag) {
        s[i] = '\0';
        int signal = lookup(s);
        switch (signal) {
            case SIN:
            case ASIN:
            case COS:
            case ACOS:
            case TAN:
            case ATAN:
            case SQRT:
            case EXP:
            case POW:
                /* push \n onto the shared buffer: causes the value to be popped off the stack by the '\n' case in main() */
                --input_index;
                return signal;
                break;
            default:
                return signal;
                break;
        }
    }
    /* check non digit or '.' characters */
    if(!isdigit(c) && c != '.') {
        /* handle possible sign character */ 
        if(c == '-' || c == '+') {
            int temp = input[input_index++];
            if(isdigit(temp) || temp == '.') {
                (c == '-') ? sign_flag = 1 : 0;
                s[0] = c = temp;
            }
            else {
                --input_index;
                return c;
            }
        }
        else
            return c;
    }
    i = 0;
    if(isdigit(c))      /* collect integer part */
        while(isdigit(s[++i] = c = input[input_index++]))
            ;
    if(c == '.') {      /* collect fractional part */
        while(isdigit(s[++i] = c = input[input_index++]))
            ;
    }
    s[i] = '\0';
    if(c != EOF)
        --input_index;
    return NUMBER;
}

/* lookup: iterate over the lookup table entries and return the integer value associated with a matching string */
int lookup(char * key) 
{
    if(strlen(key) == 1) {
        return VAR;
    }
    for(int i = 0; i < LOOKUP_TABLE_SIZE; ++i) { 
        if(strcmp(lookup_table[i].key, key) == 0) {
            return lookup_table[i].value;
        }
    }
    return INVALID_KEY;
}