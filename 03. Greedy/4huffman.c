/*
 * C program to implement Hufman coding 
 * By Shaik Sameer, 12th Jan 2021
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    char ch; 
    int freq; 
    struct Node *left; 
    struct Node *right; 
}typedef Node; 

void swap(Node* array[], int smallest, int i)
{
    Node* temp = array[smallest]; 
    array[smallest] = array[i]; 
    array[i] = temp; 
}

void minHeapify(Node* array[], int i, int N)
{
    int l = 2 * i; 
    int r = 2 * i + 1; 
    int smallest = i; 
    if (l <= N && array[l]->freq < array[smallest]->freq) smallest = l;
    if (r <= N && array[r]->freq < array[smallest]->freq) smallest = r; 
    if (smallest != i)
    {
        swap(array, smallest, i); 
        minHeapify(array, smallest, N); 
    }
}

void buildMinHeap(Node* array[], int N)
{
    // heapify non-leaf nodes only (after N/2 + 1 leaf nodes start)
    for (int i = N/2; i >= 1; i--)
    {
        minHeapify(array, i, N); 
    }
    
}

Node* ExtractMin(Node* chfreqs[], int heapsize)
{
    Node* min = chfreqs[1]; 
    chfreqs[1] = chfreqs[heapsize--]; 
    minHeapify(chfreqs, 1, heapsize); 

    return min; 
}

void Insert(Node* chfreqs[], Node* key, int heapsize)
{
    chfreqs[++heapsize] = key; 
    // check if new node's parent/grandparents satisfies minheap property it not fix it
    while (heapsize > 1 && chfreqs[heapsize/2]->freq > chfreqs[heapsize]->freq)
    {
        swap(chfreqs, heapsize, heapsize/2); 
        heapsize /= 2; 
    }
    
}

// A utility function to print an array of size n 
void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        printf("%d", arr[i]); 
  
    printf("\n"); 
} 

void printCodes(Node *result, int arr[], int top)
{
    // Assign 0 to left edge and recur 
    if (result->left)
    {
        arr[top] = 0; 
        printCodes(result->left, arr, top+1); 
    }
    
    // Assign 1 to right edge and recur 
    if (result->right)
    {
        arr[top] = 1; 
        printCodes(result->right, arr, top+1); 
    }

    // If this is a leaf node, then 
    // it contains one of the input 
    // characters, print the character 
    // and its code from arr[] 
    if (!(result->left) && !(result->right)) { 
  
        printf("%c: ", result->ch); 
        printArr(arr, top); 
    } 
}

void print(Node* result, int N)
{
    int arr[100], top = 0;  // stack (assumed max tree hit < 100)
    printCodes(result, arr, top); 
}

Node* huffman(Node* chfreqs[], int N)
{
    // build a minheap
    int heapsize = N; // initially the size of the heap = N 
    buildMinHeap(chfreqs, heapsize); 

    // iterate from 1 to N-1 to build a binary huffman pre-fix free tree
    for (int i = 1; i <= N-1; i++)
    {
        // create a new node and initialize it's character to '$'
        Node *temp = malloc(sizeof(Node)); 
        temp->ch = '$'; 

        // extract a minimum from the heap and make temp.left to point it
        temp->left = ExtractMin(chfreqs, heapsize); 
        heapsize--; 

        // extract a minimum from the heap and make temp.right to point it 
        temp->right = ExtractMin(chfreqs, heapsize); 
        heapsize--; 

        // Insert node temp in the heap in which temp->freq = temp's left + temp's right
        temp->freq = temp->left->freq + temp->right->freq; 
        Insert(chfreqs, temp, heapsize); 
        heapsize++; 
    }

    // finally return the min node from the heap
    return ExtractMin(chfreqs, heapsize); 
}

int main(int argc, char const *argv[])
{
    int N; 
    printf("Enter the number of characters: "); 
    scanf("%d", &N); 

    // create an array of Node data type to store N characters and their frequencies 
    Node* chfreqs[N+1]; 

    // prompt user to enter character and their frequencies and store them 
    for (int i = 1; i <= N; i++)
    {
        // create a Node pointer at location i
        chfreqs[i] = malloc(sizeof(Node)); 

        printf("\nEnter the character and frequency of char: %d = ", i); 
        scanf(" %c%d", &chfreqs[i]->ch,&chfreqs[i]->freq);  // whitespace before %c will get rid of any number of buffer character present before actual input 
        chfreqs[i]->left = chfreqs[i]->right = NULL;  // initially they point to NULL
    }
    
    Node *result = huffman(chfreqs, N); 
    // print table of chars and freqs
    print(result, N); 
    return 0;
}
