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



