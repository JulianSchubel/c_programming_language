/* Make dcl recover from input errors */

/* Interpretting recovery from input errors to be a more standard response to invalid input. 
 * At current program outputs multiple error messages but continues processing. 
 * Changing behaviour to output either the declaration or single error response. 
 * In the case of expected dcl errors, outputing the dcl and direct dcl definition below */

/* dcl and direct-dcl definition 
 *
 * dcl: 
 *      optional *'s direct-dcl
 * direct-dcl:  
 *      name
 *      (dcl)  
 *      direct-dcl() 
 *      direct-dcl[optional size]
*/

 /* example parse tree of (*pfa[])():

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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100 
#define ERROR_MESSAGE_SIZE 128
#define MAX_ERROR_MESSAGES 8
#define PARENTHESIS_ERROR 1             /* 0000 0001 */
#define BRACKET_ERROR 2                 /* 0000 0010 */
#define DIRDCL_ERROR 4                  /* 0000 0100 */

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

char *error_message_table[MAX_ERROR_MESSAGES];
unsigned int number_of_error_messages;
char error_flags;

int main() {
    /* allocate memory for error messages */
    for(unsigned int i = 0; i < MAX_ERROR_MESSAGES; ++i) {
        error_message_table[i] = malloc(sizeof(char) * ERROR_MESSAGE_SIZE);
    }
    while( gettoken() != EOF ) { /* 1st token on line */
        strcpy(datatype, token); /* is the datatype */
        out[0] = '\0';
        dcl();                   /* parse the rest of the line */
        if(number_of_error_messages > 0) {
            printf("Syntax errors found:\n");
            for(unsigned int i = 0; i < number_of_error_messages; ++i) {
                printf("%d:\t%s", i, error_message_table[i]);
            }
            number_of_error_messages = 0;
        }
        else if(tokentype == '\n') {
            printf("%s: %s %s\n", name, out, datatype);
        }
    }
    /* free error message memory */
    for(unsigned int i = 0; i < MAX_ERROR_MESSAGES; ++i) {
        free(error_message_table[i]);
    }
    return 0;
}

/* dcl: parse a C declaration into a word description */
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
    extern char error_flags;
    int type;
    if( tokentype == '(' ) {                /* (dcl) */
        dcl();
        if( tokentype != ')' ) {
            strncpy(error_message_table[number_of_error_messages], "error: missing )\n", ERROR_MESSAGE_SIZE);
            number_of_error_messages++;
        }
    } else if( tokentype == NAME ) {        /* variable name */
        strcpy(name, token);
    }
    else {
        strncpy(error_message_table[number_of_error_messages],"error: expected name or (dcl)\ndcl:\n\toptional *'s direct-dcl\ndirect-dcl:\n\tname\n\t(dcl)\n\tdirect-dcl()\n\tdirect-dcl[optional size]\n", ERROR_MESSAGE_SIZE);
        number_of_error_messages++;
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

    /* skip over spaces and tabs */
    while( (c = getch()) == ' ' || c == '\t' ) {
        ;
    }
    /* if c it an open parenthesis */
    if( c == '(' ) {
        /* if the next character is a closing parenthesis */
        if( (c = getch()) == ')' ) {
            strcpy(token, "()");
            /* set tokentype as PARENS; indicates a function */
            return tokentype = PARENS;
        } else {
            /* if it isn't put back the character and continue processing */
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

