#if !defiend (INVERT_BITS_H)
#define INVERT_BITS_H
#include <stdio.h>
#include <stdlib.h>
/*Inverts n bits of x starting from p (ranging rightward)*/
unsigned int invert_bits(unsigned int x, int p, int n);
#endif
