/* Define a macro swap(t,x,y) that interchanges two arguments of type t. (Block structure will help.) */

#include <stdio.h>

#define swap(t,x,y) \
{\
    t temp;\
    temp = x;\
    x = y;\
    y = temp;\
}

int main(int argc, char * * argv)
{
    int x,y;
    x = 0;
    y = 1;
    printf("x: %d, y: %d\n", x, y);
    swap(int, x, y);
    printf("x: %d, y: %d\n", x, y);
    return 0;
}
