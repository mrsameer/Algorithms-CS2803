/*
 * All pairs shortest problem 
 * by Shaik Sameer, jan 31 2021
 */

#include <stdio.h>
int min(int a, int b)
{
    return a<b?a:b; 
}

void solve(int V, int w[][V])
{
    int d[V][V]; 
    for (int k = 1; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                d[i][j] = min(w[i][j], w[i][k] + w[k][j]); 
            }
            
        }
        w = d; 
    } 
    printf("\nAdjacency matrix of shortest pairs is:\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            printf("%d ", d[i][j]); 
        }
        printf("\n");
    }
    
}

int main(int argc, char const *argv[])
{
    int V; 
    printf("Enter the number of vertices: ");
    scanf("%d", &V); 

    int w[V][V]; 
    printf("Enter the adjaceny matrix\n"); 
    for (int i = 0; i < V; i++) 
        for (int j = 0; j < V; j++)
            scanf("%d", &w[i][j]); 

    solve(V, w); 
    return 0;
}
