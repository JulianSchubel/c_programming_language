/*   
    Rewrite the function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its wquivalent integer value. The allowable digits are 0 through 9, a through f, and A through F.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int htoi(char * string);

//ASCII character range a-f
#define HEX_ASCII_LC_LB 97
#define HEX_ASCII_LC_UB 102

//ASCII character range A-F
#define HEX_ASCII_UC_LB 65
#define HEX_ASCII_UC_UB 70

//ASCII zero character
#define ASCII_DECIMAL_LB 48
#define ASCII_DECIMAL_UB 57

//Hexadecimal character value lower bound
#define HEX_CHAR_VALUE_LB 10

int htoi(char * string)
{
	int n = 0;
	
	//If the string is prefixed "0x" or "0X" move the initial '0' offset to the 3rd element
	if(string[0] == '0' && (string[1] == 'x' || string[1] == 'X'))
	{
		string = &string[2];
	}

	//Length +1 to accommodate for null terminator '\0'
	for(int i = 0; string[i]; ++i)
	{
        /* lower case: a-f */
		if(string[i] >= HEX_ASCII_LC_LB && string[i] <= HEX_ASCII_LC_UB)
		{
			n = 16 * n + (HEX_CHAR_VALUE_LB + (string[i] - HEX_ASCII_LC_LB));	
		}
        /* upper case: A-F */
		if(string[i] >= HEX_ASCII_UC_LB && string[i] <= HEX_ASCII_UC_UB)
		{
			n = 16 * n + (HEX_CHAR_VALUE_LB + (string[i] - HEX_ASCII_UC_LB));	
		}
        /* decimal: 0-9 */
		if(string[i] >= ASCII_DECIMAL_LB && string[i] <= ASCII_DECIMAL_UB)
		{
			n = 16 * n + (string[i] - ASCII_DECIMAL_LB);	
		}
	}
	return n;
}

int main(int argc, char * argv[])
{
    if(argc < 2 || strlen(argv[1]) < 3) {
       printf("Expected an argument\n"); 
       exit(EXIT_FAILURE);
    }
    printf("%d", htoi(argv[1]));
    return 0;
}
