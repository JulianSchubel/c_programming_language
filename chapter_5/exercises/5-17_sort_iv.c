/* Add a field-handling capability, so sorting may be done on fields within lines, each field sorted according to an independent set of options */

/* fields are defined as whitespace delimited strings */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */
#define FIELD_SIZE 1000 /* max field size */

/* option flags */
#define NUMERIC 1           // 0000 0001
#define DECREASING 2        // 0000 0010
#define FOLD 4              // 0000 0100
#define DIRECTORY_ORDER 8   // 0000 1000
#define FIELD 16            // 0001 0000

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char * allocp = allocbuf; /* next free position */
char *lineptr[MAXLINES];    /* pointers to text lines */
char *alloc(int);
static char field_buffer_a[FIELD_SIZE];
static char field_buffer_b[FIELD_SIZE];

/* usage: output a usage message and exit the program with a failure signal */
void usage();
/* set_options: sets options flags based on the argument string provided */
void set_options(char **args);
/* readlines: read input lines) */
int readlines( char *lineptr[], int nlines);
/* writelines: write output lines */
void writelines(char *lineptr[], int nlines);
/* getline: get line into s, return length */
int _getline(char *, int);
/* _qsort: sort v[left]...v[right] into inreasing order */
void _qsort(void *lineptr[], int left, int right, int (*comp) (void *, void *)); 
/* swap: swap v[i] and v[j] */
void swap(void *v[], int i, int j);
/* substr: puts a substring of s from field_start up to but not including field_end into string */
void substr(char *s, char *str, unsigned int field_start, unsigned int field_end);
/* numcmp: compare s1 and s2 numerically */
int numcmp(char *, char *);
/* alloc: return pointer to n characters */
char * alloc(int n);
/* afree: free storage pointed to by p */
void afree(char *p);
/* lexicographic_cmp: Compares s and t in a case insensitive (converts to lower case), lexicographic manner. Returns < 0 if s < t; > 0 if s > t. Else 0 (s == t). */
int lexicographic_cmp(char *, char *);
/* read_field: reads field field_number from line, putting it in s. */
void read_field(char *s, char *str, unsigned int field_number);

/* used to flip comparision */
int order = 1;
/* field number to sort by */
static int field = 0;
/* store option flags */
static char options = 0;

/* sort input lines */
int main(int argc, char *argv[])
{
    extern unsigned int max_args_count;
    int nlines;                 /* number of input lines read */
    extern int order;           /* 1 if reverse (descending) sort */

    if( argc > 1 ) {
        ++argv;
    }

    nlines = readlines(lineptr, MAXLINES);
    if(nlines >= 0) {
        while( --argc > 0 ) {
            /* reset options from last run */
            options = 0;
            set_options(argv);
            ++argv;
            _qsort( (void **) lineptr, 0, nlines-1, (int (*) (void*, void*)) ((options & NUMERIC) ? numcmp : lexicographic_cmp));
            writelines(lineptr, nlines);
        }
    }
    else {
        printf("input too big to sort\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/* usage: output a usage message and exit the program with a failure signal */
void usage() {
    printf("sort [-MN]* where M is the field to sort by and within the range 0-99, and N a selection of the options d,f,n,r \n");
    exit(EXIT_FAILURE);
}

/* set_options: sets options flags based on the argument string provided */
void set_options(char **args) {
    extern char options;
    extern int order;
    extern int field;
    /* flag indicating whether the field number has been read */
    char field_read = 0;
    char field_counter = 0;
    int c = *args[0];
    if (c == '-') {
        /* iterate over every character in the option argument string */
        while( (c = *++args[0]) ) {
            if( isdigit(c) && !field_read ) {
                options |= FIELD;
                /* accumalate the field number from the first set of contigous digits encountered */
                field = 10*field + (c - 48);
            }
            else {
                field_read = 1;
                switch (c) {
                    case 'n':
                        options |= NUMERIC;
                        break;
                    case 'r':
                        options |= DECREASING;
                        order = -1;
                        break;
                    case 'f':
                        options |= FOLD;
                        break;
                    case 'd':
                        options |= DIRECTORY_ORDER;
                        break;
                    default:
                        printf("invalid argument option\n");
                        usage();
                        break;
                }
            }
        }
    }
    /*
    printf("numeric: %d\ndecreasing: %d\nfold: %d\ndirectory_order: %d\nfield: %d\nfield_number: %d\n",
            (options & NUMERIC) / NUMERIC,
            (options & DECREASING) / DECREASING,
            (options & FOLD) / FOLD,
            (options & DIRECTORY_ORDER) / DIRECTORY_ORDER,
            (options & FIELD) / FIELD,
            field
    );
    */
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
        /* flip the result in the case that the DESCENDING option is set */
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

/* substr: puts a substring of s from field_start up to but not including field_end into string */
void substr(char *s, char *str, unsigned int field_start, unsigned int field_end) {
    unsigned int field_length = field_end - field_start;
    unsigned int string_length = strlen(s);
    /* check bounds for field_length */
    if( field_length <= 0 || field_length > string_length ) {
        usage();
    }
    else {
        string_length = field_length;
    }
    for(unsigned int i = 0, j = field_start; j < field_end; ++i, ++j) {
        str[i] = s[j];
    }
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2) {
    double v1, v2;
    extern int order;
    extern int field;
    char field_comparison = (options & FIELD) ? 1 : 0;
    
    if(field_comparison) {
        read_field(field_buffer_a, s1, field);
        read_field(field_buffer_b, s2, field);
    }

    s1 = field_buffer_a;
    s2 = field_buffer_b;

    v1 = atof(s1);
    v2 = atof(s2);

    /* handle numerical comparison on strings */
    /* atof returns 0 for a character otherwise */
    if ( !(v1 && v2) ){
        double sum = 0;
        unsigned int i = 0;
        int c;
        while( (c = s1[i]) ) {
            /* if the fold option has been provided convert to lower case */
            if( options & FOLD ) {
                c = tolower(c);
            }
            /* if -d flag set and the character is not either alphanumeric or a blank skip the character */
            if( (options & DIRECTORY_ORDER) && !(isalnum(c) || isblank(c)) ) {
                continue;
            }
            sum += (double) c;
            ++i;
        }
        v1 = sum;
        sum = 0;
        i = 0;
        while( (c = s2[i]) ) {
            /* if the fold option has been provided convert to lower case */
            if( options & FOLD ) {
                c = tolower(c);
            }
            /* if -d flag set and the character is not either alphanumeric or a blank skip the character */
            if( (options & DIRECTORY_ORDER) && !(isalnum(c) || isblank(c)) ) {
                continue;
            }
            sum += (double) c;
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

/* lexicographic_cmp: Compares s and t in a case insensitive (converts to lower case), lexicographic manner. Returns < 0 if s < t; > 0 if s > t. Else 0 (s == t). */
int lexicographic_cmp(char *s, char *t) {
    extern int field;
    char field_comparison = (options & FIELD) ? 1 : 0;

    if(field_comparison) {
        read_field(field_buffer_a, s, field);
        read_field(field_buffer_b, t, field);
    }

    s = field_buffer_a;
    t = field_buffer_b;

    int fold = options & FOLD;
    int directory_order = options & DIRECTORY_ORDER;
    char a = 0, b = 0;

    while ( a == b ) {
        /* if the DIRECTORY_ORDER option is set only compare alphanumeric and blank characters */
        if( directory_order ) {
            /* find next alphanumeric or blank character in s and t */
            /* while s is not an alphanumeric character or a blank (\n, \t) ignore the character */
            while( (isalnum(*s) == 0 || isblank(*s) == 0) && *s != '\0' ) {
                ++s;
            }
            /* while t is not an alphanumeric character or a blank (\n, \t) ignore the character */
            while( (isalnum(*t) == 0 || isblank(*t) == 0) && *t != '\0' ) {
                ++t;
            }
        }

        /* assign character to a and b. If FOLD option set, convert the character to lowercase for comparison */
        a = fold ? tolower(*s++) : *s++;
        b = fold ? tolower(*t++) : *t++;


        /* in the case that a == b but a and b are '\0', need to break out of the loop */
        if (a == '\0' && b == '\0') {
            return 0;
        }
    }
    return a - b;
}

/* read_field: reads field field_number from line, putting it in s.
 * fields are separated by whitespace and consist of contiguous non whitespaces characters */
void read_field(char *s, char *line, unsigned int field_number) {
    unsigned int fields_read = 0;
    int c;
    int i = 0;
    int j = 0;
    while( (c = line[i++]) != '\0' && fields_read <= field_number ) {
        if( c == '\t' || c == ' ' ) {
            ++fields_read;
            if( fields_read <= field_number ) {
                continue;
            }
            else {
                break;
            }
        }
        else if (fields_read == field_number ) {
            s[j++] = c;
        }
    }
    s[j] = '\0';
}
