//PRNG, Pseudo Random Number Generator
#if !defined(prng_seed)
unsigned long int prng_seed = 1;
#endif

#if !defined(PRNG)
#define PRNG
int prng(void);
#endif

#if !defined(SEED_PRNG)
#define SEED_PRNG
void seed_prng(unsigned int seed);
#endif
