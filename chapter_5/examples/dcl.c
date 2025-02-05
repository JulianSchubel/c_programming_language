/* dcl: converts a C declaratio into a word description */

/* dcl: option *'s direct-dcl */
/* direct-dcl:  name
 *              (dcl) 
 *              direct-dcl()
 *              direct-dcl[optional size]
 */

/* parse tree of (*pfa[])():

            dcl
             |
            dir-dcl
             |  \_____()
            dir-dcl
    (________|________)
            dcl
    *________|
            dir-dcl
             |________[]
            name
             |
            pfa
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100 


enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int getch(void);
void ungetch(int);
int gettoken(void);

int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */
char buf[BUFSIZE];          /* buffer for ungetch() */
int bufp = 0;               /* next free position in buf */

int main() {
    while( gettoken() != EOF ) { /* 1st token on line */
        strcpy(datatype, token); /* is the datatype */
        out[0] = '\0';
        dcl();                   /* parse the rest of the line */
        if( tokentype != '\n' ) {
            printf("syntax error\n");
        }
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

/* dcl: parse a declarator */
void dcl(void) 
{
    int ns;

    for( ns = 0; gettoken() == '*'; ) {     /* count *'s */
        ns++;
    }
    dirdcl();
    while(ns-- > 0) {
        strcat(out, " pointer to");
    }

}

void dirdcl(void) 
{
    int type;
    if( tokentype == '(' ) {                /* (dcl) */
        dcl();
        if( tokentype != ')' ) {
            printf("error: missing )\n");
        }
    } else if( tokentype == NAME ) {        /* variable name */
        strcpy(name, token);
    }
    else {
        printf("error: expected name or (dcl)\n");
    }
    while( (type = gettoken()) == PARENS || type == BRACKETS ) {
        if( type == PARENS ) {
            strcat(out, " function returning");
        }
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

/* gettoken: finds the next token in the input. Skips blanks and tabs. */
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while( (c = getch()) == ' ' || c == '\t' ) {
        ;
    }
    if( c == '(' ) {
        if( (c = getch()) == ')' ) {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if( c == '[' ) {
        for( *p++ = c; (*p++ = getch()) != '['; ) {
            ;
        }
        *p = '\0';
        return tokentype = BRACKETS;
    } else if( isalpha(c) ) {
        for( *p++ = c; isalnum(c = getch()); ) {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
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

