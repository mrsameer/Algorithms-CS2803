/*
 * Implementation of Longest common sequence algorithm in C
 * By Shaik Sameer, jan 24 2021
 */

#include <stdio.h> 

int max(int a, int b) { return a>b?a:b; }
 
void lcs(char x[], char y[], int M, int N)
{
    // create table of dimension M+1 x N+1
    int table[M+1][N+1]; 

    // fill first row with zeros 
    for (int i = 0; i <= N; i++) table[0][i] = 0; 

    // fill first column with zeros 
    for (int i = 0;i <= M; i++) table[i][0] = 0; 

    // iterate over rows and fill the table 
    for (int i = 1; i <= M; i++)
    {
       for (int j = 1; j <= N; j++)
       {
           if (x[i-1] == y[j-1]) table[i][j] = table[i-1][j-1] + 1; 
           else table[i][j] = max(table[i-1][j], table[i][j-1]); 
       }
       
    }

    printf("The length of the longest common subsequence is: %d", table[M][N]);
    
     // Following code is used to print LCS 
    int index = table[M][N]; 
  
    // Create a character array to store the lcs string 
    char lcs[index+1]; 
    lcs[index] = '\0'; // Set the terminating character 
  
    // Start from the right-most-bottom-most corner and 
    // one by one store characters in lcs[] 
    int i = M, j = N; 
    while (i > 0 && j > 0) 
    { 
      // If current character in X[] and Y are same, then 
      // current character is part of LCS 
      if (x[i-1] == y[j-1]) 
      { 
          lcs[index-1] = x[i-1]; // Put current character in result 
          i--; j--; index--;     // reduce values of i, j and index 
      } 
  
      // If not same, then find the larger of two and 
      // go in the direction of larger value 
      else if (table[i-1][j] > table[i][j-1]) 
         i--; 
      else
         j--; 
   } 
   printf("\nThe lcs is: %s\n", lcs); 
  
}

int main(int argc, char const *argv[])
{
    int M, N; 
    printf("Enter the length of the first string: "); 
    scanf("%d", &M); 
    char x[M];
    printf("Enter the first string: "); 
    scanf("%s", x);

    printf("Enter the length of the second string: "); 
    scanf("%d", &N); 
    char y[N]; 
    printf("Enter the second string: "); 
    scanf("%s", y); 
    
    lcs(x, y, M, N);
    return 0;
}
