/*
Shell sort: Invented in 1959 by D.L. Shell. In early stages, far-apart elements are compared rather than adjacent ones as in simpler interchange sorts.
This tends to eliminate large amounts of disorder quickly, so later stages ahve less woek to do.
The interval between compared elements is gradually decreased to one, at which point the sort effectively becomes an adjacent interchange method.
*/

/*shell_sort: sort v[0]...v[n-1] into increasing order*/

void shell_sort(int v[], int n)
{
	int gap, i, j, temp;
	
	for( gap = n/2; gap > 0; gap /= 2 )
	{
		for(i = gap; i < n; ++i )
		{
			for( j = i - gap; j >= 0 && v[j] > v[j+gap]; j -= gap )
			{
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
		}
	}
}
