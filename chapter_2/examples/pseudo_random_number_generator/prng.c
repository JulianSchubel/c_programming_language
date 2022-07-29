int prng(void)
{
	extern unsigned long int prng_seed;
        prng_seed = prng_seed * 1103515245 + 12345;
	printf("%lu", prng_seed);
        return (unsigned int) (prng_seed/65536) % 32768;
}

void seed_prng(unsigned int seed)
{
	extern unsigned long int prng_seed;
        prng_seed = seed;
}
