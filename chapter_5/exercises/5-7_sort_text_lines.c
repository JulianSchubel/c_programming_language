/* Rewrite readlines to store lines in an array supplied by main rather than calling alloc (malloc) to maintain storage. How much faster is the program?
 * Ambiguity in intent with regards to the above question. Interpreting as follows: create an array on the stack instead of using the heap and have pointers to array offsets corresponding to the start of individual lines.
 * Cannot use a multidimensional array for 2 reasons: 
 *     1) cannot assign to an array, therefore the qsort implementation will not work, and the author almost certainly intended for this to be the case 
 *     2) this concept has not been covered at this pointers
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLINES 5000           /* max lines to be sorted */
#define MAXLEN 1000             /* max length of any input line */
#define MAXBUFFER 5000000       /* MAXLINES * MAXLEN */
char *lineptr[MAXLINES];        /* pointers to text lines */
char line_buffer[MAXBUFFER];    /* Stack storage for all lines */

int readlines(char *lineptr[], int nlines);
int readlines_stack_buffered(char *lineptr[], int nlines, char *line_buffer);
void writelines(char *lineptr[], int nlines);
int get_line(char output_buffer[], unsigned int limit);
char *alloc(int);
void _qsort(char *v[], int left, int right);

/* sort input lines */
int main() {
    int nlines; /* number of input lines read */

    if ((nlines = readlines_stack_buffered(lineptr, MAXLINES, line_buffer)) >= 0) {
        _qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = len = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= MAXLINES || (p = (char *) malloc(sizeof(char) * len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0'; /* delete newline; get_line includes '\n' */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

int readlines_stack_buffered(char *lineptr[], int maxlines, char *line_buffer) {
    /* pointer to start of line address */
    char *p = line_buffer;
    char line[MAXLEN];
    int nlines = 0;
    int len = 0;
    /* could replace MAXLEN with MAXBUFFER - strlen(line_buffer), but this is closer to the original K&R example */
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines > MAXLINES || (len + strlen(line_buffer)) > MAXBUFFER) {
            return -1;
        }
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            /* update p to the next available address */
            p += len;
        }
    }
    return nlines;
}

/* get_line: read in a line of input at a time. Returns the number of characters read. */
int get_line(char output_buffer[], unsigned int limit) {
    int c, i;
    for( i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        output_buffer[i] = c;
    }
    if( c == '\n') {
        output_buffer[i] = c;
        ++i;
    }
    output_buffer[i] = '\0';
    return i;
}

void writelines(char * lines[], int nlines) {
    for( int i = 0; i < nlines; ++i ) {
        printf("%s\n", lines[i]);
    }
}

/* qsort: sort v[left] ... v[right] into increasing order */
void _qsort(char *v[], int left, int right) 
{
    int i, last;
    void swap(char *v[], int i, int j);
    /* do nothing if array containes fewer than two elements */
    if(left >= right) 
        return; 
    /* move partition element to v[0]*/
    swap(v, left, (left + right) / 2); 
    last = left;
    /* partition */
    for (i = left + 1; i <= right; ++i) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    /* resotore partition element */
    swap(v, left, last);    
    _qsort(v, left, last-1);
    _qsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
