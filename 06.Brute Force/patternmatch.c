/*
  Brute Force program to search for a pattern in a string 
  by Shaik Sameer
 */

#include <stdio.h>

int search(char str[], char pat[], int N, int M)
{
    int i, j; 
    for (i = 0; i <= N-M; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (str[i+j] != pat[j]) break; 
        }
        if (j == M) return i; 
    }
    return -1; 
}

int main(int argc, char const *argv[])
{
    int N, M; 
    
    printf("Enter the length of the string: "); 
    scanf("%d", &N);

    char str[N]; 
    printf("Enter the string: "); 
    scanf("%s", str); 

    printf("Enter the length of the pattern: "); 
    scanf("%d", &M); 

    char pat[M]; 
    printf("Enter the pattern: "); 
    scanf("%s", pat); 

    int result = search(str, pat, N, M); 
    if (result == -1) printf("Pattern is not found in the string\n"); 
    else printf("Pattern is found in the string at index %d\n", result); 
    return 0;
}
