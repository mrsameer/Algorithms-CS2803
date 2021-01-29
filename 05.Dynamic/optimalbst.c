#include <stdio.h>

int w(int freq[], int i, int j)
{
    int sum = 0;
    for (i = i+1; i <= j; i++)
        sum += freq[i]; 
    
    return sum;
}

void solve(int keys[], int freq[], int N)
{
     /* cost[i][j] = Optimal cost of binary search tree  
    that can be formed from keys[i] to keys[j].  
    cost[0][N] will store the resultant cost */
    int table[N+1][N+1]; 

    // fill diagonal of table with zeros 
    for (int i = 0; i <= N; i++) table[i][i] = 0; 
    // cost of length = 1 (single) = frequency of that key 
    for (int i = 0; i < N; i++) table[i][i+1] = freq[i+1]; 

    // figure out cost of chain length 2 to N. 
    for (int length = 2; length <= N; length++)
    {
        for (int i = 0; i <= N-length+1; i++)
        {
            int j = i + length; 
            table[i][j] = 32767; 

            // Try making all keys in interval keys[i..j] as root  
            for (int k = i+1; k <= j; k++)  
            {  
            // c = cost when keys[k] becomes root of this subtree  
            int c = table[i][k-1] + table[k][j] + w(freq, i, j);
            if (c < table[i][j]) 
            { 
                table[i][j] = c;   
            }
            }  
        } 
    }
    
    printf("The cost of optimal bst is %d\n", table[0][N]); 
}
int main(int argc, char const *argv[])
{
    int N; 
    printf("Enter the number of keys: "); 
    scanf("%d", &N); 

    int keys[N+1], freq[N+1]; 
    printf("Enter the keys and their frequencies\n"); 
    for (int i = 1; i <= N; i++) scanf("%d%d", &keys[i], &freq[i]); 

    solve(keys, freq, N); 
    return 0;
}
