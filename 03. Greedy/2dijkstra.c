/*
 * Implementation of Dijkstra's single source shortest path algorithm in c
 * By Shaik Sameer, Jan 10 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// structure to store path
struct node {
    int ele; 
    int dist; 
    struct node *next; 
}typedef S; 

// util function to add node to the path 
S* Union(S *path, int ele, int dist)
{
    S* temp = malloc(sizeof(S));
    temp->ele = ele; 
    temp->dist = dist; 
    temp->next = NULL; 

    if (path == NULL)
    {
        return temp; 
    }

    // else go to the last and insert temp 
    S* temp2 = path; 
    while (temp2->next) temp2 = temp2->next; 
    temp2->next = temp;
    return path; 
    
}

int ExtractMin(int distance[], int V, int visited[])
{
    int min = INT_MAX, min_index; 
    // look for all nodes and grab the minimum distance one
    for (int i = 0; i < V; i++)
    {
        // if not in shortest path and distance <= min then it is eligible to be min
        if (!visited[i] && distance[i] <= min)
        {
            min = distance[i]; 
            min_index = i; 
        }
        
    }
    
    return min_index; 
}

void dijkstra(int **Graph, int source, int V)
{
    // Create visited array to keep track of nodes in path 
    int visited[V]; 
    // initially initialize them to 0
    for (int i = 0; i < V; i++) visited[i] = 0; 
    
    // create distance array of size V and initally intialize all to infinity and source to 0
    int distance[V]; 
    for (int i = 0; i < V; i++) distance[i] = INT_MAX;
    distance[source] = 0;  // source distance is 0

    // Initialize shortest path to NULL
    S *path = NULL; 

    int u; 
    // Find shortest path for all vertices 
    for (int i = 0; i < V; i++)
    {
        // extract node which is in the Queue with minimum known distance
        u = ExtractMin(distance, V, visited); 
        
        // add this  u to the path. 
        path = Union(path, u, distance[u]); 
		
		// add this to visited 
		visited[u] = 1; 
		
        // relax each vertex v belongs to G.Adjacent[u] & not in the path
        for (int v = 0; v < V; v++)
        {
            if (visited[v] == 0 && Graph[u][v] != 0 && distance[v] > distance[u] + Graph[u][v])
            {
                distance[v] = distance[u] + Graph[u][v]; 
            }
        }
        
    }

    // printing path and as well as adding distance
    int distsum = 0; 
    printf("The shortest path is: ");
    while (path)
    {
        printf("%d->%d", source, path->ele); 
        printf(" and distance is: %d\n", path->dist);
        distsum += path->dist; 
        path = path->next;
    }
    printf("\nTotal distance is: %d", distsum); 
}



int main(int argc, char const *argv[])
{
    /*
     * Prompt user for number of vertices and store them in V
     */
    int V;  // Number of vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &V); 

    // define 2d matrix and allocate memory 
    int **Graph = (int**)malloc(sizeof(int*)*V); 
    for (int i = 0; i < V; i++) Graph[i] = (int*)malloc(sizeof(int)*V);

    // Prompt user for adjacent matrix and store it in Graph
    printf("Enter the adjacent matrix\n"); 
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            scanf("%d", &Graph[i][j]); 
        }
        
    }
    
    // prompt user for source vertex and store it in s
    int source; 
    printf("Enter the source: "); 
    scanf("%d", &source); 

    dijkstra(Graph, source, V);  
    return 0;
}
