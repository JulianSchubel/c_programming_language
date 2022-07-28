/* Verify that getchar() != EOF is 0 or 1 
   If end of file  0, else 1.
*/
#include <stdio.h>

int main(int argc, char * * argv)
{
	int c;
	c = getchar() != EOF; //Equivalent to c = (getchar() != EOF), != higher precedence than =
	
	printf("%d", c);
	return 0;
}
