/* Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab. */

/*
    If space, read and count the number of spaces until non space.
    Find quotient and remainder of spaces divided by tab stop.
    Output the quotient amount of tabs, and remainder amount of spaces.
    Else, check for EOF or '\n', in which case break, or output the character.
*/

#include <stdio.h>
#define TAB_STOP 4
#define MAXLINE 10

int getln(char s[], int lim);

int main(int argc, char * * argv)
{
    int line[MAXLINE];
    int space_count = 0;
    int c;
    while((c = getchar()) != EOF && c != '\n') {
        while(c == ' ') {
            ++space_count;
            c = getchar();
        }
        if(space_count > 0) {
            int tabs = space_count / TAB_STOP;
            int spaces = space_count % TAB_STOP;
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
        else {
            putchar(c);
        }
    }
    return 0;
}
