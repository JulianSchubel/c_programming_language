/* Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines  */

#include <stdio.h>
#define MAXLINE 1000

int getln(char line[], int maxline);
void copy(char to[], char from[]);

int main(int argc, char * * argv)
{
    int len;            /* Current line length  */
    char line[MAXLINE]; /* Current input line  */
    char non_empty = 0;

    while((len = getln(line, MAXLINE)) > 0) {
        /* Note: line[len] == '\0' */
        /* Set a flag indicating '\n' was input: handles case if EOF encountered without \n */
        char nl_flag = 0;

        /* Find first non \n or \0 character */
        while(line[len] == '\0' || line[len] == '\n') {
            if(line[len] == '\n') {
                nl_flag = 1;
            }
            --len;
        }

        /* Find first non ' ' or '\t' character or pass beyond start of line */
        while(len >= 0 && (line[len] == ' ' || line[len] == '\t')) {
            --len;
        }

        /* If len >= 0 start of line was not passed */
        if(len >=0) {
            if(nl_flag) {
                line[++len] = '\n'; //Comment out to check removal - cursor will indicate.
            }
            line[++len] = '\0';
            printf("%s", line);
        }
    }
    return 0;
}

/* getln: read a line into s, return length  */
int getln(char s[], int lim)
{
    int c, i;
    for(i =0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to': assume 'to' is big enough */
void copy(char to[], char from[]) 
{
    int i;
    i = 0;
    while((to[i] = from[i]) != '\0') {
        ++i;
    }
}
