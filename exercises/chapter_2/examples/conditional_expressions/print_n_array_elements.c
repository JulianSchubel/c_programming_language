#include <stdio.h>

int main(int argc, char * argv[])
{
	int n = 15;
	const int size = 100;
	int a[size];
	for(int i = 0; i < n; ++i)
	{
		a[i] = i;
	}
	for(int i = 0; i < n; ++i)
	{
		printf("%6d%c", a[i], (i%10 == 9 || i == n-1) ? '\n' : ' ');
	}
	return 0;
}
