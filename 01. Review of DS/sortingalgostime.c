/*
 program that will generate integer array of variable sizes 
 with different data patterns and then apply all sorting algorithms 
 and display the comparative efficiency of each sorting algorithms.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int array[], int a, int b)
{
    int temp = array[a]; 
    array[a] = array[b]; 
    array[b] = temp; 
}

void bubbleSort(int arrayay[], int size) {
  for (int step = 0; step < size - 1; ++step) {

    // Swapped keeps track of swapping
    int swapped = 0;

    // Run loops two times: one for walking throught the array
    // and the other for comparison
    for (int i = 0; i < size - step - 1; ++i) {

      // To sort in descending order, change > to < in this line.
      if (arrayay[i] > arrayay[i + 1]) {
        
        // Swap if greater is at the rear position
        int temp = arrayay[i];
        arrayay[i] = arrayay[i + 1];
        arrayay[i + 1] = temp;
        swapped = 1;
      }
    }

    // If there is not swapping in the last swap, then the array is already sorted.
    if (swapped == 0)
      break;
  }
}

void insertionSort(int array[], int size) {
  for (int step = 1; step < size; step++) {
    int key = array[step];
    int j = step - 1;

    // Compare key with each element on the left of it until an element smaller than
    // it is found.
    // For descending order, change key<array[j] to key>array[j].
    while (key < array[j] && j >= 0) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = key;
  }
}

void selectionSort(int array[], int size) {
  for (int step = 0; step < size - 1; step++) {
    int min_idx = step;
    for (int i = step + 1; i < size; i++) {

      // To sort in descending order, change > to < in this line.
      // Select the minimum element in each loop.
      if (array[i] < array[min_idx])
        min_idx = i;
    }

    // put min at the correct position
    int temp = array[min_idx]; 
    array[min_idx] = array[step]; 
    array[step] = array[min_idx]; 
  }
}

void maxHeapify(int array[], int i, int N)
{
    int l = 2 * i; 
    int r = 2 * i + 1; 
    int largest = i; 
    if (l <= N && array[l] > array[largest]) largest = l;
    if (r <= N && array[r] > array[largest]) largest = r; 
    if (largest != i)
    {
        swap(array, largest, i); 
        maxHeapify(array, largest, N); 
    }
}
void buildMaxHeap(int array[], int N)
{
    for (int i = N/2; i >= 1; i--)
    {
        maxHeapify(array, i, N); 
    }
    
}

void heapsort(int array[], int N)
{
    buildMaxHeap(array, N); 
    for (int i = N; i > 1; i--)
    {
       swap(array, 1, i); 
       maxHeapify(array, 1, i-1);
    }
}

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

void mergesort(int array[], int aux[], int lo, int hi)
{
    // base case 
    if (lo >= hi) return; 

    // recursive case 
    int mid = lo + (hi - lo)/2; 
    mergesort(array, aux, lo, mid);   // recursive call for left array
    mergesort(array, aux, mid+1, hi);  // recursive call for right array
    merge(array, aux, lo, mid, hi); // recursive call to merge both left and right arrays
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

void quicksort(int array[], int lo, int hi)
{
    if (lo >= hi) return; // base case 

    int p = partition(array, lo, hi); 
    quicksort(array, lo, p-1);  // recursive function for the left side elements of the pivot 
    quicksort(array, p+1, hi);  // recursive function for the right side elements of the pivot

}


double bubble(int array1[], int N)
{
    clock_t t; 
    t = clock(); 
    bubbleSort(array1, N); 
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    return time_taken; 
}

double insertion(int array2[], int N)
{
    clock_t t; 
    t = clock(); 
    insertionSort(array2, N); 
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    return time_taken; 
}

double selection(int array3[], int N)
{
    clock_t t; 
    t = clock(); 
    selectionSort(array3, N);    
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    return time_taken; 
}

double h(int array4[], int N)
{
    clock_t t; 
    t = clock(); 
    heapsort(array4, N-1); 
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    return time_taken; 
}

double m(int array5[], int aux[], int lo, int hi)
{
    clock_t t; 
    t = clock(); 
    mergesort(array5, aux, 0, hi); 
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    return time_taken; 
}

double q(int array6[], int lo, int hi)
{
    clock_t t; 
    t = clock(); 
    quicksort(array6, 0, hi); 
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    return time_taken; 
}

int main(int argc, char const *argv[])
{
    char sorts[6][30] = {"Bubble Sort", "Insertion sort", "Selection sort", "Heap sort", "Merge Sort", "Quick Sort"};
    int N[] = {10, 100, 1000, 10000, 100000};  
    double times[6][5];  
    
    // Use current time as  
    // seed for random generator 
    srand(time(0)); 

    for (int i = 0; i < 5; i++)
    {
        int array1[N[i]];
        int array2[N[i]]; 
        int array3[N[i]]; 
        int array4[N[i]];
        int array5[N[i]];
        int array6[N[i]];

        for (int j = 0; j < N[i]; j++) 
        { 
            array1[j] = rand();
            array2[j] = array1[j]; 
            array3[j] = array1[j];
            array4[j] = array1[j]; 
            array5[j] = array1[j]; 
            array6[j] = array1[j];  
        }
       // Calculate the time taken by bubblesort() 
        times[0][i] = bubble(array1, N[i]) ; 

        // calculate the time take by insertionsort()
        times[1][i] = insertion(array2, N[i]);; 

        // calculate the time take by selecionsort()
        times[2][i] = selection(array3, N[i]);

        // calculate the time take by heapsort()
        times[3][i] = h(array4, N[i]);

        // calculate the time take by mergesort()
        int aux[N[i]]; 
        times[4][i] =  m(array5, aux, 0, N[i]-1); ; 

        //calculate the time taken by quicksort()
        times[5][i] = q(array6, 0, N[i]-1); ; 
    }
    printf("\t\t");
    for (int i = 0; i < 5; i++) printf("N=%d    ", N[i]); 
    printf("\n"); 
    for (int i = 0; i < 6; i++)
    {
        printf("%s\t", sorts[i]); 
        for (int j = 0; j < 5; j++)
        {
            printf("%f ", times[i][j]); 
        }
        printf("\n") ; 
    }
    
    return 0;
}
