/* Rewrite fahrenheit to celsius temperature conversion program to use a function for conversion  */
#include <stdio.h>

double fahr_cels(double fahr)
{
	double celsius = (5.0/9.0)*(fahr - 32);
	return celsius; 
}

int main(int argc, char * * argv)
{
	printf("%.2f\n", fahr_cels(271.2));
	return 0;
}
