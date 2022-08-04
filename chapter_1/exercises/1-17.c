/* Write a program to print all input lines that are longer than 80 characters.  */

#include <stdio.h>
#define MAXLINE 1000

int getln(char line[], int maxline);
void copy(char to[], char from[]);

int main(int argc, char * * argv)
{
    int len;            /* Current line length  */
    char line[MAXLINE]; /* Current input line  */

    while((len = getln(line, MAXLINE)) > 0) {
        if (len > 80) {
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

