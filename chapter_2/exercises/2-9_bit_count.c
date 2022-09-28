/* In a two's complement number system, x &= (x - 1) deletes the rightmost 1 bit in x. Explain why. Use this observation to write a faster version of bitcount. */

/*  
    Assuming x = yyyy 1000, where y can be 0 or 1
    -1 in two's complement = 1111 1111
    x - 1 = x + (-1)

        yyyy 1000
       +1111 1111
       ----------
        yyyy 0111

        then 

        yyyy 1000
       &yyyy 0111
       ----------
        yyyy 0000

    If y = 0, y + 1 from carry (y = 1) and then + 1 from adding the corresponding bit (y = 0) = y. In other words y + 1 + 1 = y.
    Similarly if y = 1, y + 1 from carry (y = 0) and then + 1 from adding the corresponding bit (y = 1) = y.
    Then given the law of idempotence for conjunction (p ^ p = p), all y's remain the same.
    Note that overflowed carries are discarded.

    This demonstrates that the rightmost set bit (1 bit) is deleted by x &= (x-1)
*/

//Using the fact that x & (x - 1) eliminates the right most digit of x in a two's complement number system
int bit_count(unsigned int x)
{
	int count = 0;
	while(x != 0)
	{
		count++;
		x &= (x-1);
	}
	return count;
}
