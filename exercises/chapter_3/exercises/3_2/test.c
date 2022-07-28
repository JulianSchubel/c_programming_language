#include "escape.h"
#include <stdio.h>

int main(int argc, char * argv[])
{
	char t[10] = "h l o	";
	char s[25];
	escape(s, t);
	printf("%s", s);
	return 0;
}
