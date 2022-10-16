/* Quicksort: C. A. R. Hoare - 1962. 
    Given an array, one element is chosen and the others are partitioned into two subsets - those less than the partition element and those greate than or equal to it. The same process is then applied recursively to the two subsets.
*/

/* qsort: sort v[left] ... v[right] into increasing order */
void qsort(int v[], int left, int right) 
{
    int i, last;
    void swap(int v[], int i, int j);
    /* Do nothing if array containes fewer than two elements */
    if(left >= right) 
        return; 
    /* move partition element to v[0]*/
    swap(v, left, (left + right) / 2); 
    last = left;
    /* partition */
    for (i = left + 1; i <= right; ++i) {
        if (v[i] < v[left]) {
            swap(v, ++last, i);
        }
    }
    /* resotore partition element */
    swap(v, left, last);    
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void swap(int v[], int i, int j)
{
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
