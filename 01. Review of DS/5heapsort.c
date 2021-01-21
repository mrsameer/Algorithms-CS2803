#include <stdio.h>
#include <stdlib.h>

void swap(int array[], int largest, int i)
{
    int temp = array[largest]; 
    array[largest] = array[i]; 
    array[i] = temp; 
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

void print(int array[], int N)
{
    for (int i = 1; i <= N; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    int N; 
    printf("Enter the number of elements: "); 
    scanf("%d", &N); 

    int *array = malloc(sizeof(int)*(N+1));
    printf("Enter the elements into the array: "); 
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &array[i]);
    }
    
    heapsort(array, N); 
    printf("Sorted array is: "); 
    print(array, N); 
    return 0;
}
