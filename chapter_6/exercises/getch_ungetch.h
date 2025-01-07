#include <stdio.h>
#include <stdlib.h>

/* getch: retrieve a character from a shared buffer if one is present, else from stdin */
int getch(void);
/* ungetch: place a character onto a shared buffer */
void ungetch(int);
