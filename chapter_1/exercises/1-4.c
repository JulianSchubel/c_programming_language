#include <stdio.h>

// Centigrade = (5/9)(Fahrenheit-32)
/* Print Celsius-Fahrenheit table */

int main()
{
	float fahrenheit, celcius;
	int lower, upper, step;

	lower = 0;			/* lower limit of temperature table */
	upper = 20;		/* upper limit */
	step = 1;			/* step size */

	celcius = lower;
	printf("Celcius - Fahrenheit\n");
	while (celcius <= upper) {
		//celcius = 5.0 * (fahrenheit - 32.0) / 9.0;
		fahrenheit = (9.0 * (celcius) / 5.0) + 32;
		printf("%3.0f\t%.2f\n", celcius, fahrenheit);
		celcius += step;
	}
}
