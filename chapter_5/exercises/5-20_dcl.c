/* Expand dcl to handle declarations with function argument types, qualifiers like const, and so on */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100 

enum { NAME, PARENS, BRACKETS, TYPE, QUALIFIER };

void dcl(void);
void dirdcl(void);
int getch(void);
void ungetch(int);
int gettoken(void);
int type_specifier(void);
void parameter_declaration(void);
void declaration_specifier(void);

int tokentype;              /* type of last token */
_Bool use_last_token;
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */
char buf[BUFSIZE];          /* buffer for ungetch() */
int bufp = 0;               /* next free position in buf */

unsigned int number_of_error_messages;
char error_flags;

int main() {
    while( gettoken() != EOF ) { /* 1st token on line */
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();                   /* parse the rest of the line */
        if(tokentype == '\n') {
            printf("%s: %s %s\n", name, out, datatype);
        }
    }
    return 0;
}

/* dcl: parse a declaration */
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

// dirdcl: parse a direct declaration
void dirdcl(void) 
{
    extern char error_flags;
    int type;
    if( tokentype == '(' ) {                /* (dcl) */
        dcl();
        if( tokentype != ')' ) {
            printf("missing ')'\n");
            exit(1);
        }
    } else if( tokentype == NAME ) {        /* variable name */
        strcpy(name, token);
    } else {
        use_last_token = 1;
    }
    while( (type = gettoken()) == PARENS || type == BRACKETS || type == '(' ) {
        if( type == PARENS ) {
            strcat(out, " function returning");
        } else if(type == '(') {
            strcat(out, " function expecting");
            parameter_declaration();
            strcat(out, " and returning");
        }
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

// type_specifier: return 1 if a token is a type specifier, else 0.
int type_specifier(void) {
    static char * types[] = {
        "_Bool", 
        "_Complex",
        "char",
        "double",
        "float",
        "int",
        "long",
        "short",
        "signed",
        "unsigned",
        "void"
    };

    //find the size of the types array
    int types_array_len = sizeof(types) / sizeof(char *);
    for(char **i = types; i < types + types_array_len; ++i) {
        /* compare the string at i with the token
         * ∙ return 1 if they are equal
         */
        if(!strcmp(*i, token)) {
            return 1;
        }
    }
 
    return 0;
}

// storage_class: return 1 if a token specifies a storage class, else 0.
int storage_class(void) {
    static char *storage_classes[] = {
        "_Thread_local", 
        "auto", 
        "extern", 
        "register", 
        "static"
    };
    return 0;
}

// type_qualifier: return 1 if a token is a type qualifier, else 0.
int type_qualifier(void) {
    static char * qualifiers[] = {
        "const",
        "restrict",
        "volatile",
        "_Atomic"
    };

    char *p = token;
    //find the size of the types array
    int types_array_len = sizeof(qualifiers) / sizeof(char *);
    for(char **i = qualifiers; i < qualifiers + types_array_len; ++i) {
        /* compare the string at i with the token
         * ∙ return 1 if they are equal
         */
        if(!strcmp(*i, token)) {
            return 1;
        }
    }

    return 0;
}

// parameter_declaration: parse a parameter declaration
void parameter_declaration(void) {
    do {
        declaration_specifier();
    } while (tokentype ==',');
}

// declaration_specifier: parse a declaration specifier
void declaration_specifier(void) {
    char temp[MAXTOKEN] = {};
    gettoken();
    do {
        if(tokentype != NAME) {
            dcl();
        } else if(type_specifier()) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        } else if(type_qualifier()) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        } else {
            printf("Unkown type or qualifier in parameter list\n");
            exit(1);
        }
    } while(tokentype != ',' && tokentype != ')');
    strcat(out, temp);
    if(tokentype == ',') {
        strcat(out, ",");
    }
}


/* gettoken: finds the next token in the input. Skips blanks and tabs. */
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if(use_last_token) {
        use_last_token = 0;
        return tokentype;
    }

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
