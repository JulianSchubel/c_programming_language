/*
Modify itoa to print the largest possible negative number (-(2^wordsize-1)) regardless of the machine on which it runs.
*/
#if !defined (ITOA_H)
#define ITOA_H
void itoa(int n, char s[]);
#endif
