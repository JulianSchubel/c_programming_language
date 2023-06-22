/* Write the program tail, that prints the last n lines of its input. By default, n is 10, but can be changed by an optional argument so that tail -n prints the last n line. 
 * The program should behave rationally no matter how unreasonable the input or the value of n.
 * Write the program so it makes the best use of available storage; lines should be stored as in the sorting program of section 5.6, not in a two-dimensional array of fixed size */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define DEFAULT_NUMBER_OF_LINES 10
#define DECIMAL_RADIX 10
#define ASCII_ZERO 48
#define ASCII_NINE 57
#define MAX_LINE_LENGTH 2048

int _getline(char *output_buffer, unsigned int limit);

int _getline(char *output_buffer, unsigned int limit) {
    int c, i;
    for( i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        output_buffer[i] = c;
    }
    if( c == '\n' ) {
        output_buffer[i] = c;
        ++i;
    }
    output_buffer[i] = '\0';
    return i;
}

int main(int argc, char *argv[])
{
    unsigned int number_of_lines = DEFAULT_NUMBER_OF_LINES;
    while(--argc > 0 && (*++argv)[0] == '-') {
        int c;
        c = *++argv[0];
        switch (c) {
            case 'n':
                --argc;
                unsigned int integer_value = 0;
                ++argv;
                /* Only read digits */
                for(unsigned int i = 0; (*argv)[i] >= ASCII_ZERO && (*argv)[i] <= ASCII_NINE ; ++i) {
                        integer_value = integer_value*DECIMAL_RADIX + ((*argv)[i] - ASCII_ZERO);
                }
                number_of_lines = integer_value;
                break;
            default:
                argc = 0;
                break;
        }
    }

    printf("number_of_lines: %d\n", number_of_lines);

    /* Allocate memory for the number of lines */
    char **lines = (char**) malloc(sizeof(char *) * number_of_lines);
    char temporary_buffer[MAX_LINE_LENGTH];
    unsigned int n = 0;
    unsigned int line_counter = number_of_lines;

    while((n = _getline(temporary_buffer, MAX_LINE_LENGTH)) > 0) {
        if(line_counter > 0) {
            /* Allocate memory for the characters in the line as well as the null terminator (_getline returns the number of characters excluding '\0')*/
            lines[line_counter-1] = (char *) malloc(sizeof(char) * n+1);
            /* Copy from the temporary buffer */
            for(unsigned int i = 0; i < n; ++i) {
                lines[line_counter-1][i] = temporary_buffer[i];
            }
            lines[line_counter-1][n] = '\0';
            --line_counter;
        }
        else {
            /* Free the oldest line */
            free(lines[number_of_lines-1]);
            /* Shift remainging lines rightwards */
            for(unsigned int i = 0; i < number_of_lines - 1; ++i) {
                lines[i+1] = lines[i];
            }
            /* Allocate memory for the characters in the line as well as the null terminator (_getline returns the number of characters excluding '\0')*/
            lines[0] = (char *) malloc(sizeof(char) * n+1);
            /* Copy from the temporary buffer */
            for(unsigned int i = 0; i < n; ++i) {
                lines[0][i] = temporary_buffer[i];
            }
            lines[0][n] = '\0';
        }
    }

    /* Print and Free the individual lines */
    for(int i = number_of_lines-1; i >= 0; --i) {
        printf("%s", lines[i]);
        free(lines[i]);
    }
    /* Free the pointer to the array of lines */
    free(lines);
    return EXIT_SUCCESS;
}
