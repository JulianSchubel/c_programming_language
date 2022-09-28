#include <stdio.h>

void squeeze(char * s, int c)
{
	int i, j;
	for(i = j = 0; s[i] != '\0'; i++)
	{
		if(s[i] != c)
		{
			//j++: value of j used before incrementing
			s[j++] = s[i];
		}
	}
	s[j] = '\0';
}

int main(int argc, char * argv[])
{
    char * string = argv[1];
    squeeze(string, *argv[2]);
    printf("%s\n",string);
    return 0;
}
