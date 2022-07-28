#include <time.h>
#include "binary_search.h"
#include "binary_search_v2.h"
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10000
#define ARRAY_VALUE_RANGE 10
#define EXECUTION_CYCLES 1000000

int main(int argc, char * argv[])
{
	int x;
	long double min = 999;	
	long double max = 0;	
	long double sum = 0;
	long double execution_time;
	int n = 100;
	time_t t;
	clock_t begin, end;

	//Positive if v1 slower, negative if v2 slower
	long double net_time = 0;

	//seeding prng
	time(&t);
	srand((unsigned) t);

	//Defining the array and search value
	int a[ARRAY_SIZE];
	int search_value = (int) rand() % ARRAY_VALUE_RANGE;;

	//Assigning pseudo random number values to array elements
	for(int i = 0; i < ARRAY_SIZE; ++i)
	{
		a[i] = (int) rand() % ARRAY_VALUE_RANGE;	
	}

	//Measuring K&R binary search execution time
	for(int i = 0, time ; i < EXECUTION_CYCLES; ++i)
	{
		//Initial CPU clock marker
		begin = clock();
		x = binary_search(search_value, a, ARRAY_SIZE);	
		//Terminal CPU clock marker
		end = clock();
		execution_time = (long double) (end - begin);
		sum += execution_time;	
	}
	
	net_time += sum;
	printf("V1 AVERAGE EXECUTION TIME: %1.12Lf\n", sum / EXECUTION_CYCLES); 

	//Measuring single conditional variant
	sum = 0;
	for(int i = 0; i < EXECUTION_CYCLES; ++i)
	{
		//Initial CPU clock marker
		begin = clock();
		x = binary_search_v2(search_value, a, ARRAY_SIZE);	
		//Terminal CPU clock marker
		end = clock();
		execution_time = (long double) (end - begin);
		sum += execution_time;	
	}
	net_time -= sum;
	printf("V2 AVERAGE EXECUTION TIME: %1.12Lf\n", sum / EXECUTION_CYCLES); 	
	
	printf("NET EXECUTION TIME: %1.12Lf\n", net_time); 
	return 0;
}
