/* Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. */
/* Extend detab to accept the shorthand -m +n to mean tab stops every nth column, starting at column m. */

/* interpretting -m to mean ignore tab stops before column m */
/* interpretting +n to mean tabs of width n */
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB_STOP 4

char * detab(char * s, int lim, int tab_width);
int getln(char s[], int lim);

int main(int argc, char * * argv)
{
    int c;
    unsigned int min_columns = 0;
    unsigned int min_column_flag = 0, invalid_argument = 0;
    unsigned int tabstop = DEFAULT_TAB_STOP;
    while(--argc > 0) {
        c = (*++argv)[0];
        if(c == '-') {
            c = *++argv[0];
            switch (c) {
                case 'm':
                    --argc;
                    min_columns = atoi(*++argv);
                    min_column_flag = 1;
                    break;
                default:
                    argc = 0;
                    break;
            }
        }
        if(c == '+') {
            c = *++argv[0];
            switch (c) {
                case 'n':
                    --argc;
                    tabstop = atoi(*++argv);
                    break;
                default:
                    argc = 0;
                    invalid_argument = 1;
                    break;
            }
        }
    }
    
    if(invalid_argument) {
        printf("Usage: detab [-m, -n]\n");
        exit(EXIT_FAILURE);
    }

    int position = 0;
    unsigned int column = 1;
    while((c = getchar()) != '\0' && c != EOF) {
        if(min_column_flag && column < min_columns) {
            ++column;
            putchar(c);
        }
        else if(c == '\t') { 
            int tab_stop_offset = position % tabstop;
            int tab_stop_distance = tabstop - tab_stop_offset; 
            for(int i = 0; i < tab_stop_distance; ++i) {
                putchar('s');
            }
            position = 0;
        }
        else if( c == '\n') {
            putchar(c);
            position = 0;
            column = 0;
        }
        else {
            ++column;
            ++position;
            putchar(c);
        }
    }
    
    return 0;
}
