#if !defined (HTOI)
#include <string.h>
#define HTOI
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

#endif
