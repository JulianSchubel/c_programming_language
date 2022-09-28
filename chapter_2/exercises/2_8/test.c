#include <stdio.h>
#include <stdlib.h>

/* bit_length: returns the number of bits required to represent d */
int bit_length(unsigned int d)
{
    int n_bits = 0;
    for(; d; d >>= 1)
    {
        n_bits++;
    }
    return n_bits;
}

int main(int argc, char * * argv)
{
    printf("%i\n", bit_length(atoi(argv[1])));
    return 0;
}
