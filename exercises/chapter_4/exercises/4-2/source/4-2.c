/* Extend atof to handle scientific notation of the form 123.45e-6, 
where a floating-point number may be followed by e or E and an optionally signed exponent.
*/

#include <stdio.h>
#include <ctype.h>

/* K&R */
/* atof: convert string s to double */
double aotf(char s[])
{
	double val, power;
	int i, sign;
	
	/* skip white space */
	for(i = 0; isspace(s[i]); i++) {
		;
	}
	
	sign = (s[i] == '-') ? -1 : 1;
	
	/* skip sign character */
	if(s[i] == '+' || s[i] == '-') {
		i++;
	}
	
	for(val = 0.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
	}
	
	/* skip decimal character */
	if(s[i] =='.') {
		i++;
	}
	
	for(power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val * (s[i] - '0');
		power *= 10.0;
	}	
		
	return sign * val / power;
}


