/* Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab. */
/* Extend entab to accept the shorthand -m +n to mean tab stops every nth column, starting at column m. */

/* interpretting -m to mean ignore tab stops before column m */
/* interpretting +n to mean the a sequence of spaces of length n is to be replaced with a tab */

/*
    If space, read and count the number of spaces until non space.
    Find quotient and remainder of spaces divided by tab stop.
    Output the quotient amount of tabs, and remainder amount of spaces.
    Else, check for EOF or '\n', in which case break, or output the character.
*/

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB_STOP 4
#define MAXLINE 10

int getln(char s[], int lim);

int main(int argc, char * * argv)
{
    int line[MAXLINE];
    int space_count = 0;
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
    unsigned int columns = 1;
    while((c = getchar()) != EOF && c != '\n') {
        while(c == ' ' && columns >= min_columns) {
            ++space_count;
            c = getchar();
        }
        if(space_count > 0) {
            int tabs = space_count / tabstop;
            int spaces = space_count % tabstop;
            for(int i = 0; i < tabs; ++i) {
                putchar('\t');
            }
            for(int i = 0; i < spaces; ++i) {
                putchar(' ');
            }
            space_count = 0;
        }
        if(c == EOF || c == '\n') {
            break;
        }
        if(min_column_flag && columns < min_columns) {
            ++columns;
            putchar(c);
        }
        else {
            putchar(c);
        }
    }
    return 0;
}
