#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* atof: convert string s to double  */
double _atof(char * s)
{
	double val, power;
	int i, sign, signed_exponent, exponent;

	/* Skip whitespace  */
	for(i = 0; isspace(s[i]); ++i)
		;

	/* Capture a multiplicative identity that will replicate the sign */
	sign = (s[i] == '-') ? -1 : 1;	
	
	/* Skip over sign symbols  */
	if(s[i] == '+' || s[i] == '-')
		i++;

	/* Capture the integral value  */
	for(val = 0.0; isdigit(s[i]); ++i)
		val = 10.0 * val + (s[i] - '0');
	
	/* Skip over the decimal point  */
	if(s[i] == '.')
		i++;

	/* Capture the fractional value  */
	for(power = 1.0; isdigit(s[i]); ++i)
	{
		val = 10.0 * val + (s[i] -'0');
		power *= 10;
	}

	/* If scientific notation  */
	if(s[i] == 'e' || s[i] == 'E')
	{
		++i;
		/* Capture a sign flag */
		signed_exponent = (s[i] == '-') ? 1 : 0;

		/* Skip over sign symbols  */
		if(s[i] == '+' || s[i] == '-')
			++i;

		/* Retrieve the exponent value  */
		for(exponent = 0; isdigit(s[i]); ++i)
		{
			exponent = 10 * exponent + (s[i] - '0');
		}

		/* Determine the mantissa  */
		val = sign * (val / power);

		/* Adjust the mantissa according to exponent */
		if(signed_exponent)
		{
			while(exponent > 0)
			{
				val /= 10.0;	
				--exponent;
			}
		}
		else
		{
			while(exponent > 0)
			{
				val *= 10.0;	
				--exponent;
			}
		}

		return val;
	}
	return sign * (val / power);
}

int main(int argc, char * argv[])
{
    char s[1000];
    if(argc < 2) {
        printf("Enter a floating point number: ");
        scanf("%s", s);
	    printf("%.15f\n", _atof(s));
    }
    else {
	    printf("%.15f\n", _atof(argv[1]));
    }
	return 0;
}
