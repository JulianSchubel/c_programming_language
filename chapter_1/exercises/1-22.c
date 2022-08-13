/* Write a program to "fold" long input lines into two or more shorter lines after the last non-blank character that occurs before the n-th column of input. 

Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column. */

#include <stdio.h>

#define MAXLINE 100
#define COLUMN_WIDTH 25
#define IN 1
#define OUT 0

int getln(char s[], int lim);
int fold(char s[], int column_width);

int main(int argc, char * * argv)
{
    int len;
    short state = OUT;
    char line[MAXLINE];

    while((len = getln(line, MAXLINE)) > 0) {
        fold(line, COLUMN_WIDTH);
    }

    return 0;
}

int fold(char s[], int column_width)
{
    int i;
    int state = OUT;
    int last_word_start_index = 0;
    int last_word_end_index = 0;
    int marker = 0; //Indicates on which index a fold must begin

    for(i = 0; s[i] != '\0'; ++i) {    
        /* Determine whether we are in or out of a word. Affects how the marker is updated */
        if(s[i] != ' ' && s[i] != '\t') {
            if(state == OUT) {
                last_word_start_index = i;
            }
            state = IN; 
        }
        if(s[i] == ' ' || s[i] == '\t' || s[i] == '\n') {
            if(state == IN) {
                last_word_end_index = i - 1;
            }
            state = OUT;
        }
        
        if(i % column_width == 0 && i / column_width != 0) {
            /* Do not output blanks; Only applies to marker updates when state was OUT */
            while(s[marker] == ' ' || s[marker] == '\t') {
                ++marker;
            }

            for(int j = marker; j <= last_word_end_index; ++j) {
                putchar(s[j]);
            }
            putchar('\n');

            /* Update marker to depending on the nearest known word boundary; Determiend by state */
            /* Nearest known word boundary is the beginning of the current word. Current word excluded in last fold */
            if(state == IN) {
                marker = last_word_start_index;
            }
            /* Nearest known word boundary is the end of the last word, marker must be the index after this. Last word included in last fold */
            else {
                marker = last_word_end_index + 1;   //
            }
        }
    }

    /* Handle remaining indices */
    for(int j = marker; j < i; ++j) {
        putchar(s[j]);
    }

    return 0;
}

/* getln: read a line into s, return length  */
int getln(char s[], int lim)
{
    int c, i;
    for(i = 0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

