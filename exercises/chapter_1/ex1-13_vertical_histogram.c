#include <stdio.h>
/*
	Vertical histogram representing word lengths for a given input.
*/

#define IN 1
#define OUT 0
#define MAX_WORD_LENGTH 12

int main()
{
	int c, i, j, state, num_chars, largest_count;
	int word_length_count[MAX_WORD_LENGTH];	
	
	state = OUT;
	num_chars = 0;
	for (i = 0; i < MAX_WORD_LENGTH; ++i)
	{
		word_length_count[i] = 0;
	}

	while ((c = getchar()) != '\n')
	{
		if (state == OUT && c != ' ' && c != '\n' && c != '\t')
		{
			state = IN;
		}
		if (state == IN && c != ' ' && c != '\n' && c != '\t')
		{
			++num_chars;
		}
		else if (state == IN && c == ' ' || c == '\n' || c == '\t')
		{
			state = OUT;
			++word_length_count[num_chars - 1];
			num_chars = 0;
		}
	}

	largest_count = 0;
	for (i = 0; i < MAX_WORD_LENGTH; ++i)
	{
		if (word_length_count[i] > largest_count)
		{
			largest_count = word_length_count[i];
		}
	}

	for (i = largest_count; i > 0; --i)
	{
		printf("%4d |", i);
		for (j = 0; j < MAX_WORD_LENGTH; ++j)
		{
			if (i > word_length_count[j])
			{
				printf("    ");
			}
			else 
			{
				printf("   *");
			}
		}
		printf("\n");
	}
	printf("%4c +", ' ');

	for (i = 0; i < MAX_WORD_LENGTH; ++i)
	{	
		printf("%4s", "----");
	}

	printf("\n");
	printf("%6c", ' ');

	for (i = 1; i <= MAX_WORD_LENGTH; ++i)
	{
		printf("%4d", i);
	}

	printf("\n");
	return 0;
}
