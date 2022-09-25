#include <stdio.h>

/* count characters in input; 2nd version */

int main(int argc, char * argv[])
{
    double nc;
    for(nc = 0; getchar() != EOF; ++nc)
        ;
    printf("%.0f\n", nc); /* %.0f suppresses printing of decimal point and fractional part */
    return 0;
}
