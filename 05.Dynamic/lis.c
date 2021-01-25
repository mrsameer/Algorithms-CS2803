/*
 * Longest increasing sequence algorithm implmentation in C
 * by Shaik Sameer
 */

#include <stdio.h>

void lis(int nums[], int N)
{
    int table[N]; 
    for (int i = 0; i < N; i++)
    {
        table[i] = 1; 
        for (int j = 0; j < i; j++)
        {
            if (nums[i] > nums[j] && table[j] + 1 > table[i])
            {
                table[i]++;
            }
            
        }
        
    }
    printf("Length of the lis: %d", table[N-1]); 

    int tmp = table[N-1]; 
    int stack[tmp]; 
    int top = -1; 
    for (int i = N-1; i >= 0; i--) if (table[i] == tmp) {stack[++top] = nums[i]; --tmp;}
    printf("\nThe lis is: "); 
    for (int i = top; i >= 0; i--)   printf("%d ", stack[i]); 
}

int main(int argc, char const *argv[])
{
    int N; 
    printf("Enter N: "); 
    scanf("%d", &N); 

    int nums[N]; 
    printf("Enter the elements: "); 
    for (int i = 0; i < N; i++) scanf("%d", &nums[i]); 

    lis(nums, N); 
    return 0;
}
