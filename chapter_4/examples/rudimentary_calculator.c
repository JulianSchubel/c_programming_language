#include <stdio.h>

#define MAXLINE 100

/* rudimentary_calculator: reads one number per line optionally preceded by a sign, and adds them up, printing the running sum after each input */
int main(int argc, char * * argv)
{
    double sum, atof(char []);
    char line[MAXLINE];
    int _getline(char s[], int limit);

    sum = 0;
    while(_getline(line, MAXLINE) > 0) {
        printf("\t%g\n", sum += atof(line));
    }
    return 0;
}

/* getline: get line into s, return length */
int _getline(char s[], int limit)
{
    int c, i;
    i = 0;

    while(--limit > 0 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if( c == '\n' ) {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

