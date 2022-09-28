/* Write a version of binary search with only one test inside the loop and measure the difference in run time */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* CLOCKS_PER_SEC = CPU clock cycles per second */
#define EXECUTION_TIME(x) {\
    clock_t start = clock();\
    x;\
    clock_t end = clock();\
    double execution_time = ((double) (end - start)) / CLOCKS_PER_SEC;\
    printf("%.10lfs\n", execution_time);\
}

/*binary_search: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binary_search(int x, int v[], int n)
{
    //Index positions
    int low, mid, high;
    low = 0;
    high = n-1;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if( x < v[mid] )
        {
            high = mid - 1;
        }
        else if( x > v[mid] )
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

/* binary_search_v2: implements binary search to find x in a, where n is the size of a */
int binary_search_v2(int x, int a[], int n)
{
    //Index positions
    int low, mid, high;
    low = 0;
    high = n-1;
    while(low < high) {
        mid = (low + high) / 2;
        if( x < a[mid] ) {
            high = mid - 1;
        }
        else {
            low = mid + 1;    
        }
    }
    return (x == a[mid]) ? mid : -1;
}

int main(int argc, char * * argv)
{
    const int SIZE = 15;
    int a[] = {1,2,5,16,24,63,78, 92, 93,94, 100, 116, 255, 256,999};

    EXECUTION_TIME(binary_search(100,a,SIZE))
    EXECUTION_TIME(binary_search_v2(100,a,SIZE))

    return 0;
}
