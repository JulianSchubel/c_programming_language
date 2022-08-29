/* Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged */
/* Bit position count p starts from 0 and at right end. Assume p and n are sensible positive values */

#include <stdio.h>
#include <stdlib.h>

unsigned int set_bits(unsigned int x, int p, int n, unsigned int y)
{
        /* Non-sensical p and n values provided */
        if(((p+1) - n) < 0) {
            exit(EXIT_FAILURE);
        }
        unsigned int mask;
        //Create a mask of n right aligned 1s
        mask = ~(~0u << n);
        //Shifting the mask to position p in x and inverting such that 0's correspond to bit positions [p, p+n-1]
        mask = ~(mask << p);
        //Set target bits in x to 0;
        x = x & mask;
        //Shifting the rightmost n bits of y to align with the range in x from p
        y = y << p;
        //Applying OR to set bits of x to bits of y (x's are zero and therefore take on the value of y)
        x = x | y;
        return x;
}

