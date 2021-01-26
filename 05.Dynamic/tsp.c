/* 
 * Travelling salesmam problem using dynamic programming 
 * by Shaik Sameer
 */

#include <stdio.h>
#include <limits.h>
#define N 4


int min(int a,int b){return a<b?a:b; }
// Adj matrix which defines graph 
int dist[10][10] = {
    {0, 20, 42, 25},
    {20, 0, 30, 34}, 
    {42, 30, 0, 10}, 
    {25, 34, 10, 0}
}; 

int dp[16][4];  // mask can take  2^N values and pos can take N values so matrix must be of size 2^N * N 
// if all cities have been visited 
int VISITED_ALL  = (1<<N) - 1; 

int tsp(int mask, int pos)
{
    // mask denotes the set of cities which we have been visited so far 
    // if all visited then return the distance of going back to origin from current city
    if (mask == VISITED_ALL)
    {
        return dist[pos][0]; 
    }
    
    // lookup case
    if (dp[mask][pos] != -1)
        return dp[mask][pos]; 

    int ans = INT_MAX; 
    // else try to go to cities which have not been visited 
    // iterate over all cities
    // there are N cities 
    for (int city = 0; city < N; city++)
    {
       if ((mask&(1<<city))==0)
       {
           int newAns = dist[pos][city] + tsp(mask|(1<<city), city); 
           ans = min(ans, newAns); 
       }
       
    }
    return dp[mask][pos] = ans; 
}

int main(int argc, char const *argv[])
{
    // fill dp table with -1 
    for (int i = 0; i < (1 << N); i++)
        for (int j = 0; j < N; j++)
            dp[i][j] = -1; 

    printf("Tsp(1,0) = Minimum weight hamiltonian path cost = %d\n", tsp(1, 0)); 
    return 0;
}
