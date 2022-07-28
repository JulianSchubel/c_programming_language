#include "any.h"

int any(char * string, char * find_string)
{
	signed int location = -1;
	for(int i = 0; i < strlen(string) + 1; ++i)
	{
		for(int j = 0; j < strlen(find_string) + 1; ++j)
		{
			if(string[i] == find_string[j])
			{
				location = i;
				return location;				
			}
		}
	}	
	return location;
}

