#include <string.h>
#include "ex2_3.h"

int htoi(char * string)
{
	int n = 0;
	//Number of characters in string excluding the null terminator '\0'
	int length = strlen(string);
	
	//If the string is prefixed "0x" or "0X" move the initial '0' offset to the 3rd element
	if(string[0] == '0' && (string[1] == 'x' || string[1] == 'X'))
	{
		string = &string[2];
	}

	//Length +1 to accommodate for null terminator '\0'
	for(int i = 0; i < length + 1; ++i)
	{
		if(string[i] >= HEX_ASCII_LC_LB && string[i] <= HEX_ASCII_LC_UB)
		{
			n = 16 * n + (HEX_CHAR_VALUE_LB + (string[i] - HEX_ASCII_LC_LB));	
		}
		if(string[i] >= HEX_ASCII_UC_LB && string[i] <= HEX_ASCII_UC_UB)
		{
			n = 16 * n + (HEX_CHAR_VALUE_LB + (string[i] - HEX_ASCII_UC_LB));	
		}
		if(string[i] >= ASCII_DECIMAL_LB && string[i] <= ASCII_DECIMAL_UB)
		{
			n = 16 * n + (string[i] - ASCII_DECIMAL_LB);	
		}
	}
	return n;
}
