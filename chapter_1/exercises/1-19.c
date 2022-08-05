/* Write a function reverse(s) that reverses the character string s. Use it to write a program that reverses its input a line at a time. */

#include <stdio.h>
#define MAXLINE 1000

int getln(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char s[]);

int main(int argc, char * * argv)
{
    int len;            /* Current line length  */
    char line[MAXLINE]; /* Current input line  */

    while((len = getln(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s", line);
    }
    return 0;
}

/* reverse: reverses the character string s */
void reverse(char s[])
{
    int i = 0;
    int j = 0;
    char nl_flag = 0;

    /* Find the length of the character array */
    while(s[j] != '\n' && s[j] != '\0') {
        ++j;    
    }

    /* j is index position of either \n or \0 */
    --j;

    /* Swap first and last entries until index position cross (or are equal in which case we have a string of odd length and middle char need not be swapped) */
    while(i < j) {
      char c = s[i];
      s[i] = s[j];
      s[j] = c;
      ++i;
      --j;
      //printf("i: %d, j: %d", i, j);
    }
}

/* getln: read a line into s, return length  */
int getln(char s[], int lim)
{
    int c, i;
    for(i = 0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
