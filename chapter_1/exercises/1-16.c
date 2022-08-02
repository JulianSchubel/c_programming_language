/* Revise the main routine of the longest-line program so it will correctly print the length of arbitrarily long input lines, and as much as possible of the text. */

#include <stdio.h>
#define MAXLINE 10

int getln(char line[], int maxline);
void copy(char to[], char from[]);

int main(int argc, char * * argv)
{
    int len;            /* Current line length  */
    int max;            /* Maximum length seen so far  */
    char line[MAXLINE]; /* Current input line  */
    char longest[MAXLINE]; /* Longest line saved here */

    max = 0;

    while((len = getln(line, MAXLINE)) > 0) {
        /* The line exceeded the max length */
        if(line[len-1] != '\n' && line[len-1] != EOF) {
            char c;
            /* Read until a \n or EOF and increment len. Clears the input buffer as well. */
            while((c = getchar()) != '\n' && c != EOF) {
                ++len;
            }
            if(c == '\n') {
                /* As per getln, we count \n */
                ++len;
            }
            /* Print with \n: line does not contain \n or EOF */
            printf("Length: %d\nLine: %s\n", len, line);
        }
        else {
            /* Print without \n: line contains \n or EOF  */
            printf("Length: %d\nLine: %s", len, line);
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

