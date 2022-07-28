#include "binary_search.h"

/*binary_search: implements binary search to find x in a; An array of size n returns the index if found, else -1*/

int binary_search(int x, int a[], int n)
{
        //Index positions
        int low, mid, high;
        low = 0;
        high = n-1;
        while(low <= high)
        {
                mid = (low + high) / 2;
                if( x < a[mid] )
                {
                        high = mid - 1;
                }
                }
                else
                {
			low = mid + 1;	
                }
        }
	if(x == a[mid])
	{
		return mid;
	}
	else
	{
        	return -1;
	}
}


