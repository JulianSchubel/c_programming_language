#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "./getword.h"

#define MAXWORD 100

struct key {
    char * word;
    int count;
} keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"else", 0},
    {"for", 0},
    {"if", 0},
    {"switch", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

/* keytab is an array of n key objects 
∙sizeof is a compile-time unary operator 
∙sizeof cannot be used in a #if line because the preprocessor does not parse type names
∙ here the expression in #define is not evaluated by the preprocessor so the code here is legal
*/
#define NKEYS sizeof(keytab) / sizeof(struct key)

int getword(char *, int);
struct key* binsearch(char *, struct key*, int);

/* count C keyword; pointer version */
int main() {
    char word[MAXWORD];
    struct key* p;

    while(getword(word, MAXWORD) != EOF) {
        if(isalpha(word[0])) {
            if((p=binsearch(word, keytab, NKEYS)) != NULL) {
                p->count++;
            }
        }

        for(p = keytab; p < keytab + NKEYS; p++) {
            if(p->count > 0) {
                printf("%4d %s\n", p->count, p->word);
            }
        }
        return 0;
    }
}

/* binsearch: find word in tab[0]...tab[n-1] */
struct key* binsearch(char* word, struct key* tab, int n) {
    int cond;
    struct key* low = &tab[0];
    struct key* high = &tab[n];
    struct key* mid;

    while(low < high) {
        mid = low + (high-low) / 2;
        if((cond = strcmp(word, mid->word)) < 0) {
            high = mid;
        } else if(cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return NULL;
}

