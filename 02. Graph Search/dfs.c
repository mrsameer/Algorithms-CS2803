/*
    Implementation of dfs using adjacency matrix
    By shaik sameer, Jan 9 2021. 
 */
#include <stdio.h> 
#include <stdlib.h> 

struct stack {
    int ele; 
    struct stack *next; 
}typedef stack; 

// utility function to insert at the end in the single linked list
stack* addIntoStack(stack *head, int ele)
{
    // create a new stack temp
    stack *temp = (stack*)malloc(sizeof(stack)); 
    temp->ele = ele; 
    temp->next = head;  // insert at the begining of the linked list 

    return temp; 
}

// utility function to delete from the begining of the linked list. 
stack* deleteFromStack(stack* head)
{
    // if head is NULL then return NULL
    if (head == NULL) return NULL;  

    // else make the head as whatever the node head is pointing to prior
    head = head->next; 
    return head; // return head
    
}

void dfs(int **graph, int N, int s)
{
    int v; 

    // define visited array of int data type
    int *visited = (int*)malloc(sizeof(int) * N); 
    
    /*
     * Initialize all nodes in visited array to 0 
     * as initially all nodes are unexplored. 
     */
    for (int i = 0; i < N; i++)
    {
        visited[i] = 0; 
    }

    // mark node s as explored 
    visited[s] = 1; 

    // let S be  stack initialized with s (S implemented with single linked list)
    stack *head = NULL; 
    head = addIntoStack(head, s);

    // explore graph until stack becomes empty 
    while (head != NULL)
    {
        // pick the top element and store it in v
        v = head->ele; 
        head = deleteFromStack(head); 

        // mark v as visited and print it
        if (!visited[v])      // very important to avoid repitition as it prints twice if cycle exists. 
        {
            printf("->%d", v);  
        }
        visited[v] = 1; 
        

        // push adjacent unvisited nodes of i on to the stack 
        for (int i = 0; i < N; i++)
        {
            if (!visited[i] && graph[v][i]) 
            {
                head = addIntoStack(head, i); 
            }
            
        }
        
    }
    
    
}


int main(int argc, char const *argv[])
{
    // variable N of integer data type to store number of vertices, s to store source node
    int N, s; 

    printf("Enter the number of vertices: ");
    scanf("%d", &N); 

    /* defining 2D array graph of int data type to store graph */
    int **graph = (int **)malloc(sizeof(int *)*N);  // allocation for rows
    for (int i = 0; i < N; i++)  // allocation for columns
    {
        graph[i] = (int *)malloc(N * sizeof(int)); 
    }
    
    
    
    /* Prompt user to enter adjacency matrix and store it in graph */
    printf("Enter the adjacency matrix of the graph: "); 
    for (int i = 0; i < N; i++)
    {
       for (int j = 0; j < N; j++)
       {
           scanf("%d", &graph[i][j]); 
       }
    }
    
    // prompt user for the starting vertex 
    printf("Enter the starting vertex: "); 
    scanf("%d", &s); 
    
    // depth first search 
    printf("The nodes reachable from source vertex are: %d", s); 
    dfs(graph, N, s); 
    return 0;
}