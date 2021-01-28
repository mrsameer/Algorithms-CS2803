/*
 Minimum edit distance of two strings implementation in C 
 by Shaik Sameer, jan 28 2021
*/
#include <stdio.h>

int min(int a, int b, int c)
{
    int smallest = a; 
    if (smallest > b) smallest = b; 
    if (smallest > c) smallest = c; 
    return smallest; 
}

void solve(char a[], char b[], int M, int N)
{
    int table[M+1][N+1]; 

    for (int i = 0; i <= M; i++) table[i][0] = i; 
    for (int i = 0; i <= N; i++) table[0][i] = i; 

    for (int i = 1; i <= M; i++) 
        for (int j = 1; j <= N; j++) 
            if (a[i-1] == b[j-1]) table[i][j] = table[i-1][j-1]; 
            else table[i][j] = 1 + min(table[i-1][j-1], table[i-1][j], table[i][j-1]); 
    
    printf("The minimum edit distance is: %d\n", table[M][N]); 
    printf("Steps are: \n");
    int i = M; 
    int j = N; 
  
    // check till the end 
    while (i && j) 
    { 
        // if characters are same 
        if (a[i - 1] == b[j - 1]) 
        { 
            i--; 
            j--; 
        } 
  
        // Replace 
        else if (table[i][j] == table[i - 1][j - 1] + 1) 
        { 
            printf("change %c to %c\n", a[i - 1], b[j - 1]); 
            i--; 
            j--; 
        } 
  
        // Delete the character 
        else if (table[i][j] == table[i - 1][j] + 1) 
        { 
            printf("Delete %c\n", a[i - 1]); 
            i--; 
        } 
  
        // Add the character 
        else if (table[i][j] == table[i][j - 1] + 1) 
        { 
            printf("Add %c\n",b[j - 1]); 
            j--; 
        } 
    } 
}

int main(int argc, char const *argv[])
{
    int N, M; 
    printf("Enter the length of the first string: "); 
    scanf("%d", &M); 
    char a[M]; 
    printf("Enter the first string: "); 
    scanf("%s", a); 

    printf("Enter the length of the second string: "); 
    scanf("%d", &N); 
    char b[N]; 
    printf("Enter the second string: "); 
    scanf("%s", b); 

    solve(a, b, M, N); 
    return 0;
}
