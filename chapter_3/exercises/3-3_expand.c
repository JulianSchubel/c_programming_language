#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * expand(char * s1, char * s2)
{
	int i, j, left_bound, right_bound, range;	
        //Wille require this value more than once
	int s1_length = strlen(s1);
	printf("Input string length: %d\n", s1_length);
	for(i = 0, j = 0; i < s1_length; ++i)
	{
		//Check for a range when a '-' is encountered and the previous and subsequent values are in a-z, A-Z, or 0-9
		//Also check that the previous and subsequent indices are in range. I.e. an expansion is possible to have been indicated
		if( (s1[i] == '-') && (i-1 >= 0 && i+1 < s1_length) && ( (s1[i-1] >= 65 && s1[i+1] <= 90) || (s1[i-1] >= 97 && s1[i+1] <= 122) || (s1[i-1] >= 48 && s1[i+1] <= 57) ) )
		{
			//Would have outputted the left bound and will output the right bound so only need to output what is between
			left_bound = s1[i-1];
			right_bound = s1[i+1];
			//If the left bound is lower we have an increasing range: k must increment
			if(left_bound < right_bound)
			{
				for(int k = left_bound + 1; k < right_bound; ++k)
				{
					s2[j]=k;
					++j;
				}
			}
			//If the right bound is lower we have a decreasing range: k must decrement
			else
			{
				for(int k = left_bound - 1; k > right_bound; --k)
				{
					s2[j]=k;
					++j;
				}
			}
		}
		//If no '-' encountered copy the character verbatim
		else
		{
			s2[j] = s1[i];
			++j;
		}
	}
}
