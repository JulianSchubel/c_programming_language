/* Add the options -f to fold the upper and lower case together, so that case destinctions are not made during sorting
 * for example, a and A compare equal */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char * allocp = allocbuf; /* next free position */
char *lineptr[MAXLINES];    /* pointers to text lines */
char *alloc(int);

int _getline(char *, int);
int readlines( char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void swap(void *v[], int, int);
void _qsort(void *lineptr[], int left, int right, int (*comp) (void *, void *)); 
int numcmp(char *, char *);
int case_insensitive_lexicographic_cmp(char *, char *);

/* option flags */
#define NUMERIC 1       /* 0000 0001 */
#define DECREASING 2    /* 0000 0010 */
#define FOLD 4          /* 0000 0100 */

/* used to flip comparision */
int order = 1;

/* store option flags */
static char options = 0;

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;                 /* number of input lines read */
    extern int order;           /* 1 if reverse (descending) sort */

    while( argc > 1) {
        ++argv;
        --argc;
        if(strcmp(*argv, "-n") == 0 ) {
            options |= NUMERIC;
        }
        if(strcmp(*argv, "-r") == 0) {
            options |= DECREASING;
            order = -1;
        }
        if(strcmp(*argv, "-f") == 0) {
            options |= FOLD;
        }
    }

    if( (nlines = readlines(lineptr, MAXLINES)) >= 0 ) {
        if(options & FOLD) {
            _qsort( (void **) lineptr, 0, nlines-1, (int (*) (void*, void*)) ((options & NUMERIC) ? numcmp : case_insensitive_lexicographic_cmp));

        }
        else {
            _qsort( (void **) lineptr, 0, nlines-1, (int (*) (void*, void*)) ((options & NUMERIC) ? (int (*) (const char *, const char *)) numcmp : strcmp));
        }
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("input too big to sirt\n");
        return 1;
    }
    return EXIT_SUCCESS;
}

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

/* getline: get line into s, return length */
int _getline(char s[], int limit) {
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

/* _qsort: sort v[left]...v[right] into inreasing order */
void _qsort(void *v[], int left, int right, int (*comp)(void*, void*)) {
    int i, last; 
    extern int order;
    if( left >= right) {  /* do nothing if array contains fewer than two elements */
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for( i = left+1; i <= right; ++i ) {
        /* easiest to handle mathematically by multiplying by order (1 or -1) to flip the result */
        if( order * (*comp)(v[i], v[left]) < 0 ) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    _qsort(v, left, last-1, comp);
    _qsort(v, last+1, right, comp);
}

/* swap v[i] and v[j] */
void swap(void *v[], int i, int j)
{
    void *temp;
    temp =  v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2) {
    double v1, v2;
    extern int order;

    v1 = atof(s1);
    v2 = atof(s2);

    /* handle numerical comparison on strings */
    /* atof returns 0 for a character otherwise */
    if ( !(v1 && v2) ){
        double sum = 0;
        unsigned int i = 0;
        while(s1[i]) {
            /* if the fold option has been provided convert to lower case */
            if( options & FOLD ) {
                int c = s1[i];        
                c = tolower(c);
                sum += (double) c;
            }
            else {
                sum += (double)s1[i];
            }
            ++i;
        }
        v1 = sum;
        sum = 0;
        i = 0;
        while(s2[i]) {
            /* if the fold option has been provided convert to lower case */
            if( options & FOLD ) {
                int c = s1[i];        
                c = tolower(c);
                sum += (double) c;
            }
            else {
                sum += (double)s2[i];
            }
            ++i;
        }
        v2 = sum;
    }
    if( v1 < v2 ) {
        return -1;
    }
    else if( v1 > v2 ) {
        return 1;
    }
    else {
        return 0;
    }
}

/* alloc: return pointer to n characters */
char * alloc(int n)
{
    /* it fits */
    if(allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        /* old allocp */
        return allocp - n;
    }
    /* not enough room */
    else {
        return 0;
    }
}

/* afree: free storage pointed to by p */
void afree(char *p) {
    if(p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
    }
}

/* case_insensitive_lexicographic_cmp: return < 0 if s < t; 0 if s == t, > 0 if s > t. Treats s and t as lower case. */
int case_insensitive_lexicographic_cmp(char *s, char *t) {
    while(*s != '\0' && (tolower(*s) == tolower(*t))) {
        ++s;
        ++t;
    }
    if(*s == '\0') {
        return 0;
    }
    return (tolower(*s) - tolower(*t));
}
