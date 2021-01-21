/*
 * Shaik Sameer, Jan 17 2021
 * Simple Divide and Conquer two square matrix multiplication algorithm implementation
 */

#include <stdio.h>

void mul(int N, int a[][N], int b[][N], int res[][N], int arow, int acol, int brow, int bcol, int n)
{
    // base case 
    if (n == 1) res[arow][bcol] += a[arow][acol] * b[brow][bcol]; 
    else 
    {
        /*
            a00 a01     b00 b01     a00 * b00 + a01 * b10   a00 * b01 + a01 * b11
            a10 a11  x  b10 b11 =   a10 * b00 + a11 * b10   a10 * b01 + a11 * b11

            8 recursive multiplications, so recursive relation = 8T(N/2)
            4 additions, so O(N^2)
            Therefore Time complexity = 8T(N/2) + O(N^2) = O(N^3)
        */

       mul(N, a, b, res, arow + 0,   acol + 0,   brow + 0,   bcol + 0, n/2); // a00 * b00
       mul(N, a, b, res, arow + 0,   acol + n/2, brow + n/2, bcol + 0, n/2); // a01 * b10
       mul(N, a, b, res, arow + 0,   acol + 0,   brow + 0,   bcol + n/2, n/2); // a00 * b01
       mul(N, a, b, res, arow + 0,   acol + n/2, brow + n/2, bcol + n/2, n/2); // a01 * b11
       mul(N, a, b, res, arow + n/2, acol + 0,   brow + 0,   bcol + 0, n/2); // a10 * b00
       mul(N, a, b, res, arow + n/2, acol + n/2, brow + n/2, bcol + 0, n/2); // a11 * b10
       mul(N, a, b, res, arow + n/2, acol + 0,   brow + 0,   bcol + n/2, n/2); // a10 * b01
       mul(N, a, b, res, arow + n/2, acol + n/2, brow + n/2, bcol + n/2, n/2); // a11 * b11
    }
}

int main(int argc, char const *argv[])
{
    int N; 
    printf("Enter the order of the square matrix: ");
    scanf("%d", &N); 

    int a[N][N]; 
    printf("Enter the elements into the matrix a\n"); 
    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++)
            scanf("%d", &a[i][j]); 

    
    int b[N][N]; 
    printf("Enter the elements into matrix b\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &b[i][j]); 

    int res[N][N];  // resultant matrix
    // fill resultant matrix with zeros 
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            res[i][j] = 0; 
    mul(N, a, b, res, 0, 0, 0, 0, N); // call mul function

    printf("The resultant matrix is\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
           printf("%d ", res[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
