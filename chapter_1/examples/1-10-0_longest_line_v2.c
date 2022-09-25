
/* pg. 29  */

#include <stdio.h>
#define MAXLINE 1000

/* Extern variables */
int max;            /* Maximum length seen so far  */
char line[MAXLINE]; /* Current input line  */
char longest[MAXLINE]; /* Longest line saved here */

int getln(void);
void copy(void);

int main(int argc, char * * argv)
{
    int len;            /* Current line length  */
    extern int max;
    extern char longest[];
    
    max = 0;
    while((len = getln()) > 0) {
        if (len > max) {
            max = len;
            copy();
        }
    }
    if (max > 0) {        /* There was a line  */
        printf("%s", longest);
    }
    return 0;
}

/* getln: specialized version */
int getln(void)
{
    int c, i;
    extern char line[];

    for(i =0; i < MAXLINE-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }
    if(c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

/* copy: specialised version */
void copy(void) 
{
    int i;
    extern char line[], longest[];
    i = 0;
    while((longest[i] = line[i]) != '\0') {
        ++i;
    }
}

