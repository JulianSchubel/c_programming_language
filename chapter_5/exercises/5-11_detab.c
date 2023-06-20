/* Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB_STOP 4

char * detab(char * s, int lim, int tab_width);
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
    int position = 0;
    int c;
    unsigned int tabstop_array_index = 0;
    while((c = getchar()) != '\0' && c != EOF) {
        unsigned int tabstop = DEFAULT_TAB_STOP;
        if (!use_default) {
            tabstop = tabstop_array[tabstop_array_index % tabstop_array_size];
            ++tabstop_array_index;
        }
        if(c == '\t') { 
            int tab_stop_offset = position % tabstop;
            int tab_stop_distance = tabstop - tab_stop_offset; 
            for(int i = 0; i < tab_stop_distance; ++i) {
                putchar(' ');
            }
            position = 0;
        }
        else if( c == '\n') {
            putchar(c);
            position = 0;
        }
        else {
            ++position;
            putchar(c);
        }
    }
    return 0;
}
