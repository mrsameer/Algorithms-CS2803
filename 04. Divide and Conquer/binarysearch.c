/*
 * Implementation of Binary Search algorithm in C 
 * By Shaik Sameer, Jan 13 2021
 */
#include <stdio.h>
#include <stdlib.h>

int binarysearch(int array[], int key, int low, int high)
{
    // base case
    if (high < low) return -1; // Not found

    int mid = low + (high - low)/2; 

    if (array[mid] == key) return mid; 
    else if (array[mid] > key) return binarysearch(array, key, low, mid-1);
    else return binarysearch(array, key, mid+1, high); 
}

int main(int argc, char const *argv[])
{
    int N, key, result; 
    printf("Enter the number of elements: "); 
    scanf("%d", &N); 
    
    // create an array of size n
    int array[N]; 

    // prompt to enter the elements and store it in the array
    printf("Enter the elements in non-decreasing order: "); 
    for (int i = 0; i < N; i++) scanf("%d", &array[i]); 

    int op; 
    while (1)
    {
        printf("1.Search\n2.Exit\n"); 
        scanf("%d", &op); 
        switch (op)
        {
        case 1:
            printf("Enter the element: "); 
            scanf("%d", &key); 

            result = binarysearch(array, key, 0, N); 
            if (result == -1)
            {
                printf("\nNot Found\n"); 
            }
            else
            {
                printf("\nFound at index: %d\n",result);
            }
            break;
        
        case 2:
            goto A;

        default:
            break;
        }
    }
    
    A:
    return 0;
}
