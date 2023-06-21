/* Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab. */
/* Extend entab to accept a list of tab stops as arguments. Use default tab settings if there are no arguments */

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
    /* use DEFAULT_TAB_STOP if no arguments provided */
    char use_default = 0;
    if (argc < 2) {
        use_default = 1;
    }
    unsigned int tabstop_array[argc-1];
    unsigned int tabstop_array_size = 0;
    if (!use_default) {
        while(--argc > 0) {
            tabstop_array[tabstop_array_size++] = atoi(*++argv);
        }
    }
    int line[MAXLINE];
    unsigned int space_count = 0;
    int c;
    unsigned int tabstop_array_index = 0;
    while((c = getchar()) != EOF && c != '\n') {
        while(c == ' ') {
            ++space_count;
            c = getchar();
        }
        if(space_count > 0) {
            unsigned int tabstop = DEFAULT_TAB_STOP;
            if (!use_default) {
                tabstop = tabstop_array[tabstop_array_index % tabstop_array_size];
                ++tabstop_array_index;
            }
            unsigned int tabs = space_count / tabstop;
            unsigned int spaces = space_count % tabstop;
            for(unsigned int i = 0; i < tabs; ++i) {
                putchar('\t');
            }
            for(unsigned int i = 0; i < spaces; ++i) {
                putchar(' ');
            }
            space_count = 0;
        }
        if(c == EOF || c == '\n') {
            break;
        }
        else {
            putchar(c);
        }
    }
    return 0;
}
