/* Write a program to print a historgram of the frequencies of different characters in its input*/

#include <stdio.h>

#define ARRAY_LEN 95
#define ASCII_RANGE_LOWER 32
#define ASCII_RANGE_UPPER 126

int main(int argc, char * * argv)
{
	//Array indices will serve as offset "labels" for ascii characters with value 32 - 126
	//Contiguous array len = m - n + 1, m = upper, n = lower
	int array[ARRAY_LEN];

    /* 0 initialize the array */
    for(int i = 0; i < ARRAY_LEN; ++i) {
        array[i] = 0;
    }

	int c;
	while((c = getchar()) != EOF && c != '\n') {
		if(c >= ASCII_RANGE_LOWER && c <= ASCII_RANGE_UPPER)
		{
			++array[c-ASCII_RANGE_LOWER];
		}	
	}
	for(int i = 0; i < ARRAY_LEN; ++i) {
        /*
		if(array[i] != 0)
			printf("%c: %d\n", i+ASCII_RANGE_LOWER, array[i]);
        */
		if(array[i] != 0)
		{
			printf("%c: ", i+ASCII_RANGE_LOWER);
			while(array[i] > 0)
			{
				printf("%c", '*');
				--array[i];
			}
			printf("\n");
		}
	}
	return 0;
}
