#include <stdio.h>
/* Word Counting. Count lines, words, and characters in input. */

#define IN 1		// inside a word
#define OUT 0		// outside a word

int main()
{
	int c, lines, words, characters;
	short state;

	lines = words = characters = 0;
	state = OUT;

	while ((c = getchar()) != EOF)
	{
		++characters;
		if (c == '\n')
		{
			++lines;
		}
		if ((c == ' ') || (c == '\n') || (c == '\t'))
		{
			state = OUT;
		}
		else if (state == OUT)
		{
			state = IN;
			++words;
		}
	}
	printf("%s\t%6d\n", "Number of characters: ", characters);
	printf("%s\t%6d\n", "Number of words: ", words);
	printf("%s\t%6d\n", "Number of lines: ", lines);
}