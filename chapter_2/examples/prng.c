#include <stdio.h>

/* Pseudo-random number generator (rand) and a function (srand) for initializing the seed. */
unsigned long int next = 1;

/* rand: return pseudo-random integer on 0 ..32767 */
int rand(void)
{
        next = next * 1103515245 + 12345;
        return (unsigned int) (next/65536) % 32768;
}

/* srand: set seed for rand() */
void srand(unsigned int seed)
{
        next = seed;
}

int main(int argc, char * argv[])
{
    int seed = 0;
    printf("Enter a seed value: ");
    fscanf(stdin, "%d", &seed);
    srand(seed);
    printf("%d\n", rand());
    printf("%d\n", rand());
    return 0;
}
