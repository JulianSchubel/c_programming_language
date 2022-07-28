#include <stdio.h>

// Centigrade = (5/9)(Fahrenheit-32)
/* Print Fahrenheit-Celsius table */

int main()
{
	float fahrenheit, celcius;
	int lower, upper, step;

	lower = 0;			/* lower limit of temperature table */
	upper = 300;		/* upper limit */
	step = 20;			/* step size */

	fahrenheit = lower;
	printf("Fahrenheit - Celsius\n");
	while (fahrenheit <= upper) {
		celcius = 5.0 * (fahrenheit - 32.0) / 9.0;
		printf("%3.0f\t%.2f\n", fahrenheit, celcius);
		fahrenheit += step;
	}
}
