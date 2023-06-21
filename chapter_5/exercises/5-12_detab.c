/* Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. */
/* Extend detab to accept the shorthand -m +n to mean tab stops every nth column, starting at column m. */

/* interpretting -m to mean use the default tab stops until column m */
/* interpretting +n to mean tab stops of width n */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB_STOP 8

char * detab(char * s, int lim, int tab_width);
int getln(char s[], int lim);

int main(int argc, char * * argv)
{
    int c;
    unsigned int min_columns = 0;
    unsigned int min_column_flag = 0, invalid_argument = 0;
    unsigned int tabstop = DEFAULT_TAB_STOP;
    unsigned int tabstop_post_m = 0;
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
                    tabstop_post_m = atoi(*++argv);
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
    unsigned int columns = 1;
    unsigned int post_m_columns = 0;
    while((c = getchar()) != '\0' && c != EOF) {
        if(!post_m_columns && columns >= min_columns) {
            tabstop = tabstop_post_m;
            post_m_columns = 1;
        }
        if(c == '\t') { 
            int tab_stop_offset = position % tabstop;
            int tab_stop_distance = tabstop - tab_stop_offset; 
            for(int i = 0; i < tab_stop_distance; ++i) {
                if(!post_m_columns && columns >= min_columns) {
                    tabstop = tabstop_post_m;
                    post_m_columns = 1;
                }
                putchar(' ');
                ++columns;
            }
            position = 0;
        }
        else if( c == '\n') {
            putchar(c);
            position = 0;
            columns = 0;
        }
        else {
            ++columns;
            ++position;
            putchar(c);
        }
    }
    
    return 0;
}
