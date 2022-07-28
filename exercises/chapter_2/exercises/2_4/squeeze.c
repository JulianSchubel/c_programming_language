#include "squeeze.h"

void squeeze(char * string, char * omission_string)
{
        int i, j; 
        for(i = j = 0; string[i] != '\0'; i++)
        {
		int omission_string_length = strlen(omission_string);
		char found;
		for(int k = 0; k < omission_string_length + 1; ++k)
		{
			found = 0;
                	if(string[i] == omission_string[k])
                	{
				found = 1;
				break;
                	}
		}
		if(!found)
		{
			//j++: value of j used before incrementing
			string[j++] = string[i];
		}
        }
        string[j] = '\0';
}

