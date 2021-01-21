/*
 * Implementation of Merge Sort in C 
 * By Shaik Sameer, jan 13 2021
 */

#include <stdio.h>

void merge(int array[], int aux[], int lo, int mid, int hi)
{
    // copy array to aux 
    for (int i = lo; i <= hi; i++) aux[i] = array[i]; 

    // merge back to array 
    int i = lo;  // left array starts from lo
    int j = mid+1; // right array starts from mid+1
    // for every element in both left and right arrays  
    for (int k = lo; k <= hi; k++)
    {
       // if left array elements exhausted then fill with right array element
       if (i > mid) array[k] = aux[j++]; 

       // if right array elements exhausted then fill with left array element
       else if (j > hi) array[k] = aux[i++]; 

       // if left array element is less than right array element then place it in array from aux
       else if (aux[i] < aux[j]) array[k] = aux[i++]; 

       // else place right element array 
       else array[k] = aux[j++];      
    }
}

void sort(int array[], int aux[], int lo, int hi)
{
    // base case 
    if (lo >= hi) return; 

    // recursive case 
    int mid = lo + (hi - lo)/2; 
    sort(array, aux, lo, mid);   // recursive call for left array
    sort(array, aux, mid+1, hi);  // recursive call for right array
    merge(array, aux, lo, mid, hi); // recursive call to merge both left and right arrays
}

int main(int argc, char const *argv[])
{
    int N; 
    printf("Enter the number of elements: "); 
    scanf("%d", &N); 

    printf("Enter the elements: "); 
    int array[N]; 
    for (int i = 0; i < N; i++) scanf("%d", &array[i]); 
    
    // create an auxillary array of size n 
    int aux[N]; 

    // call sort function 
    sort(array, aux, 0, N-1); 

    // print the array 
    printf("The sorted array is: "); 
    for (int i = 0; i < N; i++) printf("%d ", array[i]); 
    return 0;
}
