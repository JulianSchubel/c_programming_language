#include <stdio.h>

/* Rudimentary C syntax checking for unbalanced parentheses, brackets, braces, quotes (single and double) and nested multiline comments */

int main(int argc, char * argv[])
{
        
        int c, brackets, braces, parentheses, in_char_literal, in_string_literal, in_single_line_comment, in_multiline_comment, possible_nesting, nested_multiline_comment, invalid_character_literal;
        /* Accumulators */
        brackets = braces = parentheses = 0;
        /* Flags */
        in_char_literal = in_string_literal = in_single_line_comment = in_multiline_comment = possible_nesting = nested_multiline_comment = invalid_character_literal = 0;

        while((c = getchar()) != EOF) { 
            /* Handle invalid character literals */
            if(in_char_literal) {
                if(c == '\\') {
                    c = getchar();
                    c = getchar();
                    if( c != '\'') {
                        invalid_character_literal = 1; 
                    }
                }
                else {
                    c = getchar();
                    if( c != '\'') {
                        invalid_character_literal = 1;
                    }
                }
            }
            /* Handle character literals */
            if(c == '\'' && in_single_line_comment != 1 && in_multiline_comment != 1) {
                printf("Check character start\n");
                if(in_char_literal == 0) {
                    /* If not in, set flag */
                    in_char_literal = 1;
                }
                else {
                    /* If in, unset flag */
                    in_char_literal = 0;
                }
            }
            /* Handle string literals */
            else if(c == '\"' && in_single_line_comment != 1 && in_multiline_comment != 1) {
                printf("Check string start\n");
                if(in_string_literal == 0) {
                    /* If not in, set flag */
                    in_string_literal = 1;
                }
                else {
                    /* If in, unset flag */
                    in_string_literal = 0;
                }
            }
            /* Handle single line comments */
            /* Encounters '/' not within a character or string literal */
            else if(c == '/' && in_char_literal != 1 && in_string_literal != 1) {
                printf("Checking comment start\n");
                c = getchar();
                /* Single line comment if not in any comment */
                if( c == '/' && in_single_line_comment == 0 && in_multiline_comment == 0) {
                    in_single_line_comment = 1;
                }
                /* Multi line comment if not in any comment */
                else if (c == '*' && in_single_line_comment == 0 && in_multiline_comment == 0) {
                    in_multiline_comment = 1;
                } 
                /* Check for start of possible nested multiline comments */
                else if (c == '*' && in_multiline_comment) {
                    possible_nesting = 1;
                } 
            }
            else if( c == '*' && in_char_literal != 1 && in_string_literal != 1) {
                printf("Checking comment end\n");
                c = getchar(); 
                if(c == '/' && in_multiline_comment && possible_nesting != 1) {
                    in_multiline_comment = 0;
                }
                if(c == '/' && possible_nesting) {
                    nested_multiline_comment = 1;
                }
                
            }
            else if( in_string_literal || in_char_literal ) {
                ;
            }
            else {
                switch (c) {
                    case '{':
                        ++brackets;
                        break;
                    case '}':
                        --brackets;
                        break;
                    case '[':
                        ++braces;
                        break;
                    case ']':
                        --braces;
                        break;
                    case '(':
                        ++parentheses;
                        break;
                    case ')':
                        --parentheses;
                        break;
                }
            }
        }
        
        if(brackets) {
            printf("Unbalanced brackets '{'\n");
        }
        if(braces) {
            printf("Unbalanced braces '['\n");
        }
        if(parentheses) {
            printf("Unbalanced parentheses '('\n");
        }
        if(nested_multiline_comment) {
            printf("Nested multiline comments /* ... /* ... */ ... */\n");
        }
        if(invalid_character_literal) {
            printf("Invalid character literal: Attempted to express a string as a character\n");
        }
        if(in_char_literal) {
            printf("Unclosed character literal '\''\n");
        }
        if(in_string_literal) {
            printf("Unclosed string literal '\"'\n");
        }
        return 0;
}
