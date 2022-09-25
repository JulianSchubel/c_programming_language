/* Verify that getchar() != EOF is 0 or 1 
   If end of file  0, else 1.
*/
#include <stdio.h>

int main(int argc, char * * argv)
{
	int c;
	while((c = getchar() != EOF) == 1) //Equivalent to c = (getchar() != EOF), != higher precedence than =
        if(c)
	        printf("EOF is: %d\n", c);
    printf("EOF is: %d\n",c);
	return 0;
}
