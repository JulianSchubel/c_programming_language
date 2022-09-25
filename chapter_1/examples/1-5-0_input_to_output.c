#include <stdio.g>

int main()
{
    int c;
    c = getchar();
    while( c != EOF) {
        putchar(c);
        c = getchar(c);
    }
    return 0;
}
