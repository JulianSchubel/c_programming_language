/*set_bits(unsigned int x, int p, int n, int y)
returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.
*/
#if !defined (SET_BITS_H)
#define SET_BITS_H
unsigned int set_bits(unsigned int x, int p, int n, unsigned int y);
#endif
