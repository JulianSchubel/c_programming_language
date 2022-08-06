/* Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. */

#include <stdio.h>
#define TAB_STOP 8
int main(int argc, char * * argv)
{
    int position = 0;
    int c;
    while((c = getchar()) != '\0' && c != EOF) {
        if(c == '\t') { 
            int tab_stop_offset = position % TAB_STOP;
            int tab_stop_distance = TAB_STOP - tab_stop_offset; 
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
