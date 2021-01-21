/*
 * Implementation of Prims Minimum Spanning Tree.
 * By Shaik Sameer, 12th Jan 2021. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int findMinCost(int V, int graph[][V+1], int T[V+1][3])
{
    int min = INT_MAX;
    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
           if (graph[i][j] < min)
           {
               min = graph[i][j]; 

               // adding first min edge into T
               T[1][1] = i; 
               T[1][2] = j; 
           }
           
        }
        
    }
    return min; 
}

int findMinNear(int V, int near[], int graph[][V+1])
{
    int j = -1, min = INT_MAX; 
    for (int i = 1; i <= V; i++)
    {
        if (near[i] != 0 && graph[i][near[i]] < min)
        {
            j = i; 
            min = graph[i][near[i]]; 
        }
        
    }
    return j; 
}

void prims(int V, int graph[][V+1])
{
    // MST is computed and stored in array t[1:V-1, 1:2] as there will be V-1 edges
    int T[V+1][3]; 
    int minCost = findMinCost(V,graph,T);  //To find initial minimum cost edge and it takes O(E)

    printf("\nThe minimum spanning tree is\n%d->%d and cost:%d", T[1][1], T[1][2], minCost); 

    // create an utility array named near which keeps track of near vertices for every iteration of minimum cost
    int near[V+1]; 

    // initially set near vertices to all vertices with respect to first min edge vertices
    for (int i = 1; i <= V; i++) {
        if (graph[i][T[1][1]] < graph[i][T[1][2]]) near[i] = T[1][1]; 
        else near[i] = T[1][2]; 
    }

    // initialize first min cost edge near vertices to 0
    near[T[1][1]] = 0; 
    near[T[1][2]] = 0; 
    
    // for remaing V-1 edges figure out tree
    int j; 
    for (int i = 2; i <= V-1; i++)
    {
        // j is an index such that near[j] != 0 amd graph[j,near[j]] is minimum
        j = findMinNear(V, near, graph);
        T[i][1] = j; 
        T[i][2] = near[j]; 
        minCost += graph[j][near[j]]; 

        printf("\n%d->%d and cost is:%d", j, near[j], graph[j][near[j]]);
        near[j] = 0; // make it 0 so that we do not visit it again
        // update the near array with new mincost edge's near vertices
        for (int k = 1; k <= V; k++)
        {
            if (near[k] != 0 && (graph[k][near[k]] > graph[k][j]))
            {
                near[k] = j; 
            }
            
        }
    }
    printf("\nThe total cost is: %d\n", minCost);
}

int main(int argc, char const *argv[])
{
    int V; 
    printf("Enter the number of Vertices: "); 
    scanf("%d", &V); 

    int graph[V+1][V+1]; 
    printf("Enter the adjacency matrix of the graph\n");
    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            scanf("%d", &graph[i][j]); 
            if (graph[i][j] == 0)
            {
                graph[i][j] = INT_MAX; 
            }
            
        }
        
    }
    prims(V, graph); 
    return 0;
}
