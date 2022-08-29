/*   
    Write the function any(s1,s2) which returns the first location in the string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. (The standard library function strpbrk does the same job but returns a pointer to the location).
*/
#include <string.h>

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

