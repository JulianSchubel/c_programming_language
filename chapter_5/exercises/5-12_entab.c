/* Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab. */
/* Extend entab to accept the shorthand -m +n to mean tab stops every nth column, starting at column m. */

/* interpretting -m to mean use default tab stops until column m */
/* interpretting +n to mean tab stops of width n */

/*
    If space, read and count the number of spaces until non space.
    Find quotient and remainder of spaces divided by tab stop.
    Output the quotient amount of tabs, and remainder amount of spaces.
    Else, check for EOF or '\n', in which case break, or output the character.
*/

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB_STOP 8
#define MAXLINE 10

int getln(char s[], int lim);

int main(int argc, char * * argv)
{
    int line[MAXLINE];
    unsigned int space_count = 0;
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
    
    printf("%d, %d\n", min_columns, tabstop_post_m);
    if(invalid_argument) {
        printf("Usage: detab [-m, -n]\n");
        exit(EXIT_FAILURE);
    }

    unsigned int columns = 1;
    unsigned int post_m_columns = 0;
    while((c = getchar()) != EOF && c != '\n') {
        while(c == ' ') {
            ++space_count;
            ++columns;
            c = getchar();
        }
        if(c == '\t') {
            columns += tabstop;
        }
        if(!post_m_columns && columns >= min_columns) {
            tabstop = tabstop_post_m;
            post_m_columns = 1;
        }
        if(space_count > 0) {
            unsigned int tabs = space_count / tabstop;
            unsigned int spaces = space_count % tabstop;
            for(unsigned int i = 0; i < tabs; ++i) {
                if(!post_m_columns && columns >= min_columns) {
                    tabstop = tabstop_post_m;
                    tabs = space_count / tabstop;
                    spaces = space_count % tabstop;
                    post_m_columns = 1;
                }
                columns += tabstop;
                putchar('\t');
            }
            for(unsigned int i = 0; i < spaces; ++i) {
                if(!post_m_columns && columns >= min_columns) {
                    tabstop = tabstop_post_m;
                    tabs = space_count / tabstop;
                    spaces = space_count % tabstop;
                    post_m_columns = 1;
                }
                ++columns;
                putchar('s');
            }
            space_count = 0;
        }
        if(c == EOF || c == '\n') {
            break;
        }
        else {
            ++columns;
            putchar(c);
        }
    }
    return 0;
}
