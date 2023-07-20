/* Add the -d ("directory order") option, which makes comparisons onlu on letters, numbers and blanks. Make sure it works in conjunction with -f */
#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000       // max #lines to be sorted
#define MAXLEN 1000         // max length of any input line
#define ALLOCSIZE 10000     // size of available space 

/* option flags */
#define NUMERIC 1           // 0000 0001
#define DECREASING 2        // 0000 0010
#define FOLD 4              // 0000 0100
#define DIRECTORY_ORDER 8   // 0000 1000
#define FIELD 16            // 0001 0000

#define CAST_VOID_COMPARE (int (*)(void *, void*))

/* function prototypes */
int (*compare) (void* string_a, void* string_b);
char *alloc(int);
int _getline(char *, int);
int readlines( char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void swap(void *v[], int, int);
void _qsort(void *lineptr[], int left, int right, int (*comp) (void *, void *)); 
int numeric_comparison(char *, char *);
int lexicographic_comparison(char *, char *);
static void parse_arguments(int, char**);
void deallocate();
void print_byte(char options);
/* read_field: reads field field_number from line, putting it in s. */
void read_field(char *s, char *str, unsigned int field_number);
int field_comparison(char *, char *);

/* extern variables  */
static char allocbuf[ALLOCSIZE];            // storage for alloc
static char * allocp = allocbuf;            // next free position
char *lineptr[MAXLINES];                    // pointers to text lines
int order = 1;                              // used to flip comparison in the case that DECREASING ('r') is set
static char sort_options = 0;               // array of sorting options
static unsigned int *field_indices = 0;     // array of field indexes
static char *field_sort_options = 0;        // sort options for fields
static unsigned int n_field_options = 0;    // number of field sort options
static char current_options = 0;            // the current set of sort options being used

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;                         // number of input lines read
    extern int order;                   
    extern char sort_options;          
    extern char* field_sort_options;
    extern unsigned int n_field_options;
    extern unsigned int *field_indices; 
    extern char current_options;

    field_sort_options = (char *) malloc(sizeof(char) * (argc-1));
    field_indices = (unsigned int *) malloc(sizeof(unsigned int) * (argc-1));
    parse_arguments(argc, argv);

    if( (nlines = readlines(lineptr, MAXLINES)) >= 0 ) {
        if(n_field_options > 0) {
            printf("number of field options: %d\n", n_field_options);
            compare = CAST_VOID_COMPARE field_comparison;
            _qsort( (void **) lineptr, 0, nlines-1, compare);
        }
        else {
            compare = (int (*) (void*, void*)) ((sort_options & NUMERIC) ? (int (*) (char*, char*)) numeric_comparison : lexicographic_comparison);
            _qsort( (void **) lineptr, 0, nlines-1, compare);
        }
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("input too big to sort\n");
        return 1;
    }
    deallocate();
    return EXIT_SUCCESS;
}

/* parse_arguments: parse input arguments for processing */
static void parse_arguments(int argc, char **argv) {
    int c;
    extern unsigned int *field_indices;
    char options = 0;
    extern unsigned int n_field_options; 
    extern char sort_options;
    extern char* field_sort_options;
    char is_field_option = 0;
    while(--argc > 0 && (c = (*++argv)[0])) {
        printf("%p\n", *argv);
        if(c == '-') {
            options = 0;
            while(c = *++argv[0]) {
                if(isdigit(c) && !is_field_option) {
                    is_field_option = 1;
                    field_indices[n_field_options] = 10 * field_indices[n_field_options] + (c - '0');
                    /* read sequnce of digits as a field value in decimal */ 
                    while((c = *++argv[0]) && isdigit(c)) {
                        field_indices[n_field_options] = 10 * field_indices[n_field_options] + (c - '0');
                    }
                    ++n_field_options;
                }
                switch (c) {
                    case 'd':
                        options |= DIRECTORY_ORDER;
                        break;
                    case 'f':
                        options |= FOLD;
                        break;
                    case 'n':
                        options |= NUMERIC;
                        break;
                    case 'r':
                        options |= DECREASING;
                        break;
                    default:
                        break;
                }
            }
        }
        if(is_field_option) {
            is_field_option = 0;
            field_sort_options[n_field_options-1] = options;
        }
        else {
            sort_options = options;
        }
    }
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
        /* easiest to handle mathematically by multiplying by order (1 or -1) to flip the result in the case that the DESCENDING option is set */
        if(order * (*comp)(v[i], v[left]) < 0 ) {
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

/* numeric_comparison: compare s1 and s2 numerically */
int numeric_comparison(char *s1, char *s2) {
    extern char sort_options;
    double v1, v2;
    extern int order;

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
            if( sort_options & FOLD ) {
                c = tolower(c);
            }
            /* if -d flag set and the character is not either alphanumeric or a blank skip the character */
            if( (sort_options & DIRECTORY_ORDER) && !(isalnum(c) || isblank(c)) ) {
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
            if( sort_options & FOLD ) {
                c = tolower(c);
            }
            /* if -d flag set and the character is not either alphanumeric or a blank skip the character */
            if( (sort_options & DIRECTORY_ORDER) && !(isalnum(c) || isblank(c)) ) {
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

/* lexicographic_comparison: Compares s and t in a case insensitive (converts to lower case), lexicographic manner. Returns < 0 if s < t; > 0 if s > t. Else 0 (s == t). */
int lexicographic_comparison(char *s, char *t) {
    extern int order;
    extern char sort_options;
    int fold = sort_options & FOLD;
    int directory_order = sort_options & DIRECTORY_ORDER;
    volatile int a = 0, b = 0;
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

        /* if FOLD option set convert the character to lowercase for comparison */
        a = fold ? tolower(*s++) : *s++;
        b = fold ? tolower(*t++) : *t++;

        /* in the case that a == b but a and b are '\0', need to break out of the loop */
        if (a == '\0' && b == '\0') {
            return 0;
        }
    }
    return (a - b);
}

/* read_field: reads field field_number from line, putting it in s.
 * fields are separated by whitespace and consist of contiguous non whitespaces characters */
void read_field(char *s, char *line, unsigned int field_number) {
    unsigned int fields_read = 0;
    int c;
    int i = 0;
    int j = 0;
    char *field_index = 0;
    while( (c = line[i++]) != '\0' && fields_read + 1 <= field_number ) {
        if( c == '\t' || c == ' ' ) {
            ++fields_read;
            if( fields_read + 1 <= field_number ) {
                continue;
            }
            else {
                break;
            }
        }
        else if (fields_read + 1 == field_number ) {
            s[j++] = c;
        }
    }
    s[j] = '\0';
}

int field_comparison(char *s, char *t) {
    extern unsigned int n_field_options;
    printf("%d\n", n_field_options);
    extern unsigned int *field_indices;
    extern char *field_sort_options;
    extern char sort_options;
    unsigned long int s_len = strlen(s);
    unsigned long int t_len = strlen(t);
    char *field_a = (char *) malloc(sizeof(char) * s_len);
    char *field_b = (char *) malloc(sizeof(char) * t_len);
    int comparison = 0;
    for(unsigned int i = 0; i < n_field_options && comparison == 0; ++i) {
        sort_options = field_sort_options[i];
        read_field(field_a, s, field_indices[i]);
        read_field(field_b, t, field_indices[i]);
        if (sort_options & NUMERIC) {
            comparison = numeric_comparison(field_a, field_b);
            compare = CAST_VOID_COMPARE numeric_comparison;
        } else {
            comparison = lexicographic_comparison(field_a, field_b);
            compare = CAST_VOID_COMPARE lexicographic_comparison;
        }
        printf("field_a: %s\nfield_b: %s\ncomparison: %d\n", field_a, field_b, comparison);
    }
    free(field_a);
    free(field_b);
    return comparison;
}

void deallocate() {
    extern char *field_sort_options;
    extern unsigned int *field_indices;
    free(field_sort_options);
    free(field_indices);
}
