/* 
Write a loop equivalent to:

    for(i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
        s[i] = c;

without using && and ||
*/

#include <stdio.h>

int main(int argc, char * * argv)
{
    const int lim = 32;
    int s[lim];

    for(int i=0; i < lim-1; ++i) {
        int c;
        if((c = getchar()) == '\n')
            break;
        if(c == EOF)
            break;
        s[i] = c;
    }

    return 0;
}
