/*
	AUTHOR:			Julian Schubel
	CONTACT: 		schubeljulian@gmail.com
	DESCRIPTION:	Display type properties for the implementation
	LAST_UPDATED:	07/02/2021	21:32
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

int main()
{
	printf("\n===BYTE_SIZE===\n");
	printf("Number of bits in a BYTE: %d\n", CHAR_BIT);
	printf("Maxmimum number of bytes in a multi-byte character: %d\n", MB_LEN_MAX);
	printf("\n===CHARACTERS===\n");
	printf("Minimum value of a %ld byte CHAR: %d\n", sizeof(char), CHAR_MIN);
	printf("Maximum value of a %ld byte CHAR: %d\n", sizeof(char), CHAR_MAX);
	printf("Minimum value of a %ld byte SIGNED CHAR: %d\n", sizeof(signed char), SCHAR_MIN);
	printf("Maximum value of a %ld byte SIGNED CHAR: %d\n", sizeof(signed char), SCHAR_MAX);
	printf("Maximum value of a %ld byte UNSIGNED CHAR: %d\n", sizeof(unsigned char), UCHAR_MAX);
	printf("\n===INTEGERS===\n");
	printf("Minimum value of a %ld byte SHORT INT: %d\n", sizeof(short int), SHRT_MIN);
   	printf("Maximum value of a %ld byte SHORT INT: %d\n", sizeof(short int), SHRT_MAX); 
   	printf("Maximum Value of a %ld byte UNSIGNED SHORT INT: %d\n", sizeof(unsigned short int),  USHRT_MAX);
   	printf("Minimum value of a %ld byte INT: %d\n", sizeof(int), INT_MIN);
   	printf("Maximum value of a %ld byte INT: %d\n", sizeof(int), INT_MAX);
   	printf("Maximum value of a %ld byte UNSIGNED INT: %d\n", sizeof(unsigned int), UINT_MAX);
   	printf("Minimum value of a %ld byte LONG INT: %ld\n", sizeof(long int), LONG_MIN);
   	printf("Maximum value of a %ld byte LONG INT: %ld\n", sizeof(long int), LONG_MAX);
   	printf("Maximum value of a %ld byte UNSIGNED LONG INT: %ld\n", sizeof(unsigned long int), ULONG_MAX);
   	printf("\n===FLOATING_POINT===\n");
   	printf("Minimum value of a %ld byte FLOAT: %E\n", sizeof(float), FLT_MIN);
   	printf("Maximum value of a %ld byte FLOAT: %E\n", sizeof(float), FLT_MAX);
	printf("Number of digits in mantissa for type FLOAT number: %d\n", FLT_MANT_DIG);
	printf("Minimum value of a %ld byte DOUBLE: %E\n", sizeof(double), DBL_MIN);
	printf("Maximum value of a %ld byte DOUBLE: %E\n", sizeof(double), DBL_MAX);
	printf("Number of digits in mantissa for type DOUBLE number: %d\n", DBL_MANT_DIG);
	printf("Minimum value of a %ld byte LONG DOUBLE: %LE\n", sizeof(long double), LDBL_MIN);
	printf("Maximum value of a %ld byte LONG DOUBLE: %LE\n", sizeof(long double), LDBL_MAX);
	printf("Number of digits in mantissa for type LONG DOUBLE number: %d\n", LDBL_MANT_DIG);
	return 0;
}
