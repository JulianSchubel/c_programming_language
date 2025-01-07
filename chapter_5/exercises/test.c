#include <stdio.h>
#include <stdlib.h>

/* read_field: reads field field_number from line, putting it in s.
 * fields are separated by whitespace and consist of contiguous non whitespaces characters */
void read_field(char *s, char *line, unsigned int field_number);

int main(int argc, char *argv[])
{
    char s[128];
    char line[128] = "A B C D";
    printf("%s\n", line);
    read_field(s, line, 4);
    printf("%s\n", s);
    int i = 0;
    return EXIT_SUCCESS;
}

/* read_field: reads field field_number from line, putting it in s.
 * fields are separated by whitespace and consist of contiguous non whitespaces characters */
void read_field(char *s, char *line, unsigned int field_number) {
    unsigned int fields_read = 0;
    int c;
    int i = 0;
    int j = 0;
    char *field_index = 0;
    while( (c = line[i++]) != '\0' && fields_read + 1 <= field_number ) {
        if( c == '\t' || c == ' ' ) {
            ++fields_read;
            if( fields_read + 1 <= field_number ) {
                continue;
            }
            else {
                break;
            }
        }
        else if (fields_read + 1 == field_number ) {
            s[j++] = c;
        }
    }
    s[j] = '\0';
}
