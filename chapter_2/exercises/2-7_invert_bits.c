/* Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted, leaving the others unchanged. */

/* invert_bits: Inverts n bits of x starting from p (ranging rightward) */
unsigned int invert_bits(unsigned int x, int p, int n)
{
	unsigned int mask = x;
	mask = ~(~0 << n) << p + 1 - n;
	return (x ^ mask);
}
