/*
 Input: n and k 
 output: nCk

 By Shaik Sameer, jan 31 2021
 */

#include <stdio.h>

int solve(int N, int K)
{
    int table[N+1][K+1]; 
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= K; j++)
        {
            if (j == 0 || i == j)
            {
                table[i][j] = 1; 
            }
            else table[i][j] = table[i-1][j-1] + table[i-1][j]; 
        }
        
    }
    return table[N][K]; 
}
int main(int argc, char const *argv[])
{
    int N, K; 
    printf("Enter the N and K: "); 
    scanf("%d%d", &N, &K); 

    printf("nCk = %d", solve(N, K)); 
    return 0;
}
