/* Rewrite readlines to store lines in an array supplied by main rather than calling alloc (malloc) to maintain storage. How much faster is the program?
 * Ambiguity with regards to the above question. Interpreting as follows: create an array on the stack instead of using the heap and have pointers to array offsets corresponding to the start of individual lines.
 * Cannot use a multidimensional array for 2 reasons: 
 *     1) cannot assign to an array, therefore the qsort implementation will not work, and the author almost certainly intended for this to be the case 
 *     2) this concept has not been covered at this point.
 *
 *
 * Non scientific runtime execution checks (naive runs using perf stat):
 * 
        Performance counter stats for './a.out':

              0.94 msec task-clock                #    0.000 CPUs utilized          
                 4      context-switches          #    4.270 K/sec                  
                 2      cpu-migrations            #    2.135 K/sec                  
                61      page-faults               #   65.120 K/sec                  
         1,116,862      cycles                    #    1.192 GHz                    
         1,033,442      instructions              #    0.93  insn per cycle         
           192,462      branches                  #  205.462 M/sec                  
             6,598      branch-misses             #    3.43% of all branches        

        10.750454805 seconds time elapsed 

        0.001925000 seconds user        <--- THIS IS WHAT WE CARE ABOUT
        0.000000000 seconds sys

        -------------------------------------------------------------------

        Performance counter stats for './a.out 2':

              1.27 msec task-clock                #    0.000 CPUs utilized          
                 4      context-switches          #    3.157 K/sec                  
                 0      cpu-migrations            #    0.000 /sec                   
                62      page-faults               #   48.932 K/sec                  
         1,165,978      cycles                    #    0.920 GHz                    
         1,060,403      instructions              #    0.91  insn per cycle         
           197,421      branches                  #  155.810 M/sec                  
             6,737      branch-misses             #    3.41% of all branches        

       8.789955315 seconds time elapsed

       0.002649000 seconds user         <--- THIS IS WHAT WE CARE ABOUT
       0.000000000 seconds sys

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
int main(int argc, char **argv) {
    int nlines; /* number of input lines read */
    
    if (argc > 1 && atoi(argv[1]) == 2) {
        int t1 = clock() / CLOCKS_PER_SEC;
        if ((nlines = readlines_stack_buffered(lineptr, MAXLINES, line_buffer)) >= 0) {
            _qsort(lineptr, 0, nlines-1);
            writelines(lineptr, nlines);
            int t2 = (clock() / CLOCKS_PER_SEC) - t1;
            printf("TIMING: %d\n", t2);
            return 0;
        } else {
            printf("error: input too big to sort\n");
            return 1;
        }
    } else {
        int t1 = clock() / CLOCKS_PER_SEC;
        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
            _qsort(lineptr, 0, nlines-1);
            writelines(lineptr, nlines);
            int t2 = (clock() / CLOCKS_PER_SEC) - t1;
            printf("TIMING: %d\n", t2);
            return 0;
        } else {
            printf("error: input too big to sort\n");
            return 1;
        }
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
