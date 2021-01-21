/*
    Implementation of bfs using adjacency matrix
    By shaik sameer, Jan 9 2021. 
 */
#include <stdio.h> 
#include <stdlib.h> 

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
                printf("%d->", i); 
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
    
    // breadth first search 
    printf("The nodes reachable from source vertex are: %d->", s); 
    bfs(graph, N, s); 
    return 0;
}
