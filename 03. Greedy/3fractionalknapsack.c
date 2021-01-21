/*
 Implementation of Fractional Knapsack using Greedy approach
 By Shaik Sameer, 10th Jan 2021.
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    float profit; 
    float weight; 
    int id; 
}typedef Node; 

void swap(Node obj[], int a, int b)
{
    Node temp = obj[a]; 
    obj[a] = obj[b]; 
    obj[b] = temp; 
}

void sort(Node obj[], int N)
{
    for (int i = 0; i < N-1; i++)
    {
        for (int j = 0; j < N-i-1; j++)
        {
            if (obj[j].profit/obj[j].weight < obj[j+1].profit/obj[j+1].weight)
            {
               swap(obj, j, j+1); 
            }
            
        }
        
    }
    
}

void knapsack(Node obj[], int N, int W)
{
    sort(obj, N);  // sort obj based on the profit by weight in descending order

    float profit = 0;  // total profit
    int i; 
    for (i = 0; i < N; i++)
    {
        // if knapsack have capacity to hold objects and the chosen object should be completely place into the knapsack
        if (W > 0 && obj[i].weight <= W)
        {
            // decrease the weight W
            W -= obj[i].weight; 

            // increase the profit 
            profit += obj[i].profit; 

            printf("\nObj:%d is Completely added and profit is %f", obj[i].id, obj[i].profit); 
        }
        
        // if complete object cannot be added
        else 
            break; 
        
    }
    // if still space remaining remaining in knapsack
    if (W > 0)
    {
        profit += obj[i].profit * (W/obj[i].weight); 
        printf("\n %d/%f of Obj:%d is added and profit is %f", W, obj[i].weight, obj[i].id, obj[i].profit * (W/obj[i].weight));
    }
    
    printf("\nTotal profit is: %f", profit);
}

int main(int argc, char const *argv[])
{
    int N, W; // to store number of objects and max weight of knapsack
    printf("Enter the number of objects: "); 
    scanf("%d", &N); 
    printf("Enter the maximum weight of the knapsack: "); 
    scanf("%d",&W ); 

    // to store both profits and weights of the objects
    Node obj[N]; 

    // prompt user to enter profits and weights and store them in obj
    for (int i = 0; i < N; i++)
    {
        obj[i].id = i; 
        printf("\nEnter the profit and weight of obj:%d ", i); 
        scanf("%f%f", &obj[i].profit, &obj[i].weight); 
    }
    
    knapsack(obj, N, W); 
    return 0;
}
