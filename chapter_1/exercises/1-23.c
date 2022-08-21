/* 
    Write a program to remove all comments from a C program.
    Don't forget to handle quoted strings and charcter constant. 
    C comments do not nest.
*/

/* Replace fgetc() with getchar() for non file pointer version */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXLEN 1024
#define IN 1
#define OUT 0 

int main(int argc, char * * argv)
{
    FILE * fp;
    char fn[] = "./1-23.c";
    fp = fopen(fn, "r");
    int c;
    int in_string = 0;
    while((c=fgetc(fp)) != EOF) {
        if(c == '"' && !in_string) {
            in_string = 1;
            putchar(c);
        }
        else if (c == '"' && in_string) {
            in_string = 0;
            putchar(c);
        }
        else if(c == '/' && !in_string) {
            if((c = fgetc(fp)) == '*') {
                while(true) {
                   c = fgetc(fp);
                   if(c == '*') {
                        c = fgetc(fp);
                        if(c == '/') {
                            break;
                        }
                        else {
                            continue;
                        }
                    }
                }
            }
            else if(c == '/') {
                while((c=fgetc(fp)) != '\n' && c != EOF) {
                    ;
                }
                if(c == EOF) {
                    break;
                }
                else {
                    putchar(c);
                }
            }
        }
        else {
            putchar(c);
        }
    }
    fclose(fp);
    return 0;
}
