/*
 * Implementation of binary knapsack algorithm in c 
 * by Shaik Sameer, jan 25 2021
 */

#include <stdio.h>

void knapsack(int w[], int p[], int N, int C)
{
    // create a N+1 X C+1 table 
    int table[N+1][C+1];

    // fill first row with zeros 
    for (int i = 0; i <= C; i++)    table[0][i] = 0; 

    // fill first column with zeros 
    for (int i = 0; i <= N; i++) table[i][0] = 0; 

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= C; j++)
            if (w[i] <= j && table[i-1][j-w[i]] + p[i] > table[i-1][j]) table[i][j] = table[i-1][j-w[i]] + p[i]; 
            else table[i][j] = table[i-1][j]; 
    
    int profit = table[N][C]; 
    printf("The profit of the knapsack is: %d\n", profit); 

    printf("Weights in the knapsack are: ");
    for (int i = N; i > 0 && profit > 0; i--)
    {
        if (profit == table[i-1][C]) continue; 
        else
        {
            printf("%d ", w[i]); 
            profit -= p[i]; 
        }
        
    }
    
}

int main(int argc, char const *argv[])
{
    int N; 
    printf("Enter the number of items: "); 
    scanf("%d", &N);

    printf("Enter the weights and profits of the items\n"); 
    int w[N+1], p[N+1]; 
    for (int i = 1; i <= N; i++) scanf("%d%d", &w[i], &p[i]); 

    int C; 
    printf("Enter the capcity of the knapsack: "); 
    scanf("%d", &C); 

    knapsack(w, p, N, C); 
    return 0;
}
