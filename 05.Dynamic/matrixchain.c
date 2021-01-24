/*
 * Matrix chain multiplication 
 * By Shaik Sameer, Jan 24 2021
 */

#include <stdio.h>
#include <limits.h>

void printParenthesis(int i, int j, int n, int s[][n+1],char* name)
{
    // If only one matrix left in current segment
    if (i == j) {
        printf("%c", (*name)++); 
        return;
    }
 
    printf("("); 
 
    // Recursively put brackets around subexpression
    // from i to s[i][j].
    printParenthesis(i, s[i][j], n, s, name);
 
    // Recursively put brackets around subexpression
    // from s[i][j] + 1 to j.
    printParenthesis(s[i][j] + 1, j, n,s, name);
    printf(")"); 
}

void matrix_chain(int p[], int plength)
{
    int n = plength - 1; 
    int m[n+1][n+1], s[n+1][n+1]; 

    // fill diagonals of m with zeros (matrices with chain size 1 cost = 0)
    for (int i = 1; i <= n; i++) m[i][i] = 0; 

    // compute cost of the matrices of chain length 2 to n
    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n-l+1; i++)
        {
            int j = i+l-1; 
            m[i][j] =  INT_MAX; 
            for (int k = i; k <= j-1; k++) // j-i splits possible so examine all those possibilities
            {
                int q = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j]; 
                if (q < m[i][j])
                {
                    m[i][j] = q; 
                    s[i][j] = k;  // to remember the split
                }
            }
        }
        
    }
    // The first matrix is printed as 'A', next as 'B',
    // and so on
    char name = 'A';
 
    printf("Optimal Parenthesization is : ");
    printParenthesis(1, n, n,s, &name);
    printf("\nOptimal Cost is : %d", m[1][n]);
}

int main(int argc, char const *argv[])
{
    int N; 
    printf("Enter the number of matrices: "); 
    scanf("%d", &N); 

    int plength = N+1; 
    int p[plength]; 
    printf("Enter the the dimensions: "); 
    for (int i = 0; i < plength; i++) scanf("%d", &p[i]); 

    matrix_chain(p, plength); 
    return 0;
}
