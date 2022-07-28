#include <stdio.h>
/* copies input to output*/
int main()
{
	int c;

	while((c = getchar()) != EOF) // parenthesis around the assignment statement is necessary as `!=` has higher precedence than `=`
	{
		putchar(c);
	}
}