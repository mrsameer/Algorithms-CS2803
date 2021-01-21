/*
    Implementation of bfsShortestPath using adjacency matrix
    By shaik sameer, Jan 10 2021. 
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>

struct queue {
    int ele; 
    struct queue *next; 
}typedef q; 

// utility function to insert at the end in the single linked list
q* addIntoQueue(q *head, int ele)
{
    // create a new q temp
    q *temp = (q*)malloc(sizeof(q)); 
    temp->ele = ele; 
    temp->next = NULL;

    // if head points to NULL, then return temp; 
    if (head == NULL)
    {
        return temp; 
    }
    
    // if head is not null, insert a new q at the end and return head
    q *temp2 = head; // define a temp2 variable 
    while (temp2->next != NULL) temp2 = temp2->next; // move towards the end of the linked list. 
    temp2->next = temp;   // insert temp node at the end
    return head;   
}

// utility function to delete from the begining of the linked list. 
q* deleteFromQueue(q* head)
{
    // if head is NULL then return NULL
    if (head == NULL) return NULL;  

    // else make the head as whatever the node head is pointing to prior
    head = head->next; 
    return head; // return head
    
}

void bfs(int **graph, int N, int s)
{
    int v; 

    // create and initialize predecessor array to -1
    int pred[N];
    for(int i = 0; i < N; i++) pred[i] = -1
    ; 
    // Initialize distance(vertices) = 0 if vertex = source else INT_MAX
    int distance[N]; 
    for (int i = 0; i < N; i++) distance[i] = INT_MAX; 
    distance[s] = 0; 
    

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

    // let Q be  queue initialized with s (Q implemented with single linked list)
    q *head = NULL; 
    head = addIntoQueue(head, s);

    // while Queue is not empty search through the graph 
    while (head != NULL)
    {
       // remove the first node Queue,and store it in v 
       v = head->ele;  // store element in v 
       head = deleteFromQueue(head);  // remove front element from Queue

       // explore every node connected to node v. 
       for (int i = 0; i < N; i++)
       {
            // if graph[v][i] unexplored then mark it as explored and add it to Queue
            if (graph[v][i] && !visited[i])  // v is adjacent to i and not visitied
            {
                visited[i] = 1; 
                head = addIntoQueue(head, i); 
 
                pred[i] = v; 
                //set distance[i] = distance[v] + 1 (one more than the vertex responsible for its discovery)
                distance[i] = distance[v] + 1; 
            }
            
       }
       
    }
    
    printf("\nThe shortest path distance is: %d", distance[N-1]);
    printf("\nThe path is: "); 
    int stack[N]; 
    int top = -1; 
    int crawl = N-1;  // destination node
    stack[++top] = crawl;  //push crawl on to the stack
    // backtrack pred array to push to the path stack 
    while (pred[crawl] != -1) {
    	stack[++top] = pred[crawl]; 
        crawl = pred[crawl];
    }

   	for (int i = top; i >= 0; i--) printf("%d, ", stack[i]); 
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
    printf("Enter the adjacency matrix of the graph: \n"); 
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
    
    // breadth first search 
    bfs(graph, N, s); 
    return 0;
}
