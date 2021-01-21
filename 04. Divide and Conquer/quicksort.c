/*
 * Implementation of quick sort in c 
 * By Shaik Sameer, Jan 13 2021
 */

#include <stdio.h>

void swap(int array[], int a, int b)
{
    int temp = array[a]; 
    array[a] = array[b]; 
    array[b] = temp; 
}

int partition(int array[], int lo, int hi)
{
    int pivot = array[lo];  // select first element as the pivot 
    int j = lo+1; // element index after pivot

    // start from the element after pivot
    // parition in a way that at the end pivot goes into the correct position 
    // elements smaller to pivot reside at left side and everything else reside at right side of the final pivot index
    for (int i = j; i <= hi; i++)
        // if element less than pivot then swap them 
        if (array[i] < pivot) swap(array, i, j++);
    swap(array, lo, j-1);  // swap the prior pivot with the respect to the prior index with correct updated index of the pivot 
    return j-1;   // return the new index of the pivot
    
}
void sort(int array[], int lo, int hi)
{
    if (lo >= hi) return; // base case 

    int p = partition(array, lo, hi); 
    sort(array, lo, p-1);  // recursive function for the left side elements of the pivot 
    sort(array, p+1, hi);  // recursive function for the right side elements of the pivot

}
int main(int argc, char const *argv[])
{
    int N; 
    printf("Enter the number of elements: "); 
    scanf("%d", &N); 
    
    // create an array of size N 
    int array[N]; 
    // prompt user to enter elements and store them in the array 
    for (int i = 0; i < N; i++) scanf("%d", &array[i]); 

    sort(array, 0, N-1); 

    // print the array 
    printf("The sorted array is: "); 
    for (int i = 0; i < N; i++) printf("%d ", array[i]); 
    return 0;
}
