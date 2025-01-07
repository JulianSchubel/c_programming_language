/* Modify undcl so that it does not add redundant parenthesis to declarations */

/* necessary parenthesis are for function pointers and functions returning pointers to arrays 
 * in the abbreviated input syntax this occurs when * () or * [] is given
 * therefore we can scan for a '(' ot '[' symbol on encountering a '*' token */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 1000
#define BUFSIZE 1000

enum { NAME, PARENS, BRACKETS };

int getch(void);
void ungetch(int);
int gettoken(void);
void undcl(void);
int check_pointer_type(void);

int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[BUFSIZE];             /* output string */
char buf[BUFSIZE];          /* buffer for ungetch() */
int bufp = 0;               /* next free position in buf */

int main(int argc, char **argv) {
    undcl();
}

/* undcl: convert a word description to a declaration */
void undcl(void) 
{
    int type;
    char temp[MAXTOKEN * 2 + 100];

    /* get the first token and place it into token array */
    while( gettoken() != EOF ) {
        /* copy the token into the output */
        strcpy(out, token);
        while( (type = gettoken()) != '\n' ) {
            if( type == PARENS || type == BRACKETS ) {
                strcat(out, token);
            } else if( type == '*' ) {
                int c;
                while((c = getch()) == ' ' || c == '\t') 
                    ;
                if(c == '(' || c == '[') {
                    sprintf(temp, "(*%s)", out);
                }
                else {
                    sprintf(temp, "*%s", out);
                }
                ungetch(c);
                strcpy(out, temp);
            } else if( type == NAME ) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
}

/* gettoken: finds the next token in the input. Skips blanks and tabs. */
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    /* skip whitespace */
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
        for( *p++ = c; (*p++ = getch()) != ']'; ) {
            ;
        }
        *p = '\0';
        return tokentype = BRACKETS;
    } else if( isalpha(c) ) {
        /* if the symbols are alphanumeric characters the token is a name and as such read until a non-alphanumeric character is encountered. */
        for( *p++ = c; isalnum(c = getch()); ) {
            *p++ = c;
        }
        *p = '\0';
        /* the last character will be the non-alphanumeric character that caused loop termination */
        ungetch(c);
        /* return the token enum variant */
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

