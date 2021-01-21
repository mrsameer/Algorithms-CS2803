/* 
 * Implementation of prims algorithm using min heap 
 * by Shaik Sameer, jan 13 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct Node {
    int vertex; 
    int key; 
    int parent; 
}typedef Node; 

void swap(Node array[], int smallest, int i)
{
    Node temp = array[smallest]; 
    array[smallest] = array[i]; 
    array[i] = temp; 
}

void minHeapify(Node array[], int i, int N)
{
    int l = 2 * i; 
    int r = 2 * i + 1; 
    int smallest = i; 
    if (l <= N && array[l].key < array[smallest].key) smallest = l;
    if (r <= N && array[r].key < array[smallest].key) smallest = r; 
    if (smallest != i)
    {
        swap(array, smallest, i); 
        minHeapify(array, smallest, N); 
    }
}

void buildMinHeap(Node array[], int N)
{
    // heapify non-leaf nodes only (after N/2 + 1 leaf nodes start)
    for (int i = N/2; i >= 1; i--)
    {
        minHeapify(array, i, N); 
    }
    
}

Node ExtractMin(Node chfreqs[], int heapsize)
{
    Node min = chfreqs[1]; 
    chfreqs[1] = chfreqs[heapsize--]; 
    minHeapify(chfreqs, 1, heapsize); 

    return min; 
}

void DecreaseKey(Node vertices[],int vertex, int distance, int parent, int heapsize)
{
    int index; 
    for (int i = 1; i <= heapsize; i++)
    {
        if (vertex == vertices[i].vertex)
        {
            index = i; 
            break;
        }
        
    }

    //decrease key 
    vertices[index].key = distance; 
    vertices[index].parent = parent; 

    // adjust heap as we decreased one element's key 
    while (index > 1 && vertices[index/2].key > vertices[index].key)
    {
        swap(vertices, index, index/2); 
        index /= 2; 
    }
    
    
}
void prims(int V, int graph[V+1][V+1])
{
    int minCost = 0; 

    // keep track of vertices present in the mst 
    int visited[V+1]; 
    for (int i = 1; i <= V; i++)
    {
       visited[i] = 0; 
    }
    // separate array to keep track of distances from min heap 
    int distance[V+1]; 
    
    // for each vertex initialize the vertex key as inifinity and parent as -1
    // create an array of vertices of data type Node
    Node vertices[V+1]; 
    for (int i = 1; i <= V; i++)
    {
        vertices[i].vertex = i; 
        vertices[i].key = INT_MAX; 
        vertices[i].parent = -1; 
        distance[i] = INT_MAX; 
    }
    
    // start from the first vertex (we can also start from any random vertex)
    vertices[1].key = 0;  // least distance from among all the nodes which are in the mst 
    distance[1] = 0; 

    // build min heap with the vertices using key property 
    int heapsize = V; 
    buildMinHeap(vertices, heapsize);

    // while min heap is not empty 
    Node u; 
    while (heapsize)
    {
       u = ExtractMin(vertices, heapsize); // extract vertex with minimum distance to the vertices already present in the mst
       heapsize--; // decrease the heapsize as we extracted one element from it 
       printf("\n%d", u.vertex); 
       minCost += u.key; 
        visited[u.vertex] = 1; 
       // for each vertex 'v' adjacent to u, update it's cost  and parent 
       for (int v = 1; v <= V; v++)
       {
           if (!visited[v] && graph[u.vertex][v] < distance[v])
           {
               // updates the distance of the node and it's parent 
               DecreaseKey(vertices, v, graph[u.vertex][v], u.vertex, heapsize); 
               distance[v] = graph[u.vertex][v]; 
           } 
       }
    }
     printf("\nMin cost is:%d", minCost);
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
