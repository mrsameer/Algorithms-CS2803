/*
 * Multistage graph algorithm implementation in C 
 * by Shaik Sameer, jan 28 2021
 */

#include <stdio.h>

void solve(int N, int graph[][N+1], int stages)
{
    int cost[N+1]; // cost array to store the optimal cost of every vertex to the sink
    int d[N+1]; // destination array to store the optimal destination of every vertex 

    int source = 1; 
    int sink = N; 

    cost[sink] = 0;  // cost to reach from sink to sink = 0
    d[sink] = sink;  // destination of sink is sink itself. 

    // first stage contains only one source vertex 
    // last stage contains only one sink vertex 
    // go from previous stage of sink to first stage and figure out optimal costs and destinations 
    for (int i = N-1; i >= 1; i--)
    {
       // Now figure out minimum cost edge to this stage (i) to i+1 th stage 
       int min = 32767; 
       // since it is a directed graph and there are no backward edges 
       // so move forward only 
       for (int j = i+1; j <= N; j++)
            // if edge exists from i to j and edge cost + optimal cost of next stage vertex connected to it < min 
            // then update the min, cost, d.
            if (graph[i][j] != 0 && graph[i][j] + cost[j] < min)
            {
                min = graph[i][j] + cost[j]; 
                d[i] = j; 
            }
        cost[i] = min; 
    }
    printf("Minimum cost is %d\n", cost[source]); 
    printf("The path is: "); 
    int path[stages+1]; 
    path[source] = 1; 
    path[stages] = sink; 
    for (int i = 2; i < stages; i++)
        path[i] = d[path[i-1]]; 
    for (int i = 1; i <= stages; i++)
        printf("%d->", path[i]); 
}

int main(int argc, char const *argv[])
{
    int N; 
    printf("Enter the number of nodes: "); 
    scanf("%d", &N); 

    int stages; 
    printf("Enter the number of stages: "); 
    scanf("%d", &stages); 

    int graph[N+1][N+1]; 
    printf("Enter the adjacency matrix\n"); 
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            scanf("%d", &graph[i][j]); 
    
    solve(N, graph, stages); 
    return 0;
}