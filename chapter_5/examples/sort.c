#include <stdio.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */

char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void _qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(int argc, char **argv)
{
    int nlines; /* number of input lines read */

    if( (nlines = readlines(lineptr, MAXLINES) >= 0) ) {
        _qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 /* max length of any input line */
int _getline(char *, int);
char *alloc(int);

/* readlines: read input lines) */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while( (len = _getline(line, MAXLEN)) > 0 ) {
        if( nlines >= maxlines || (p = alloc(len)) == NULL ) {
            return -1;
        }
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    int i;
    for( i = 0; i < nlines; ++i ) {
        printf("%s\n", lineptr[i]);
    }
}

/* writelines alternative 
void writelines(char *lineptr[], int nlines) {
    while(nlines -- > 0) {
        printf("%s\n", *lineptr++);
    }
}
*/

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
