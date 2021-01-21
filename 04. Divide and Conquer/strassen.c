/*
 * Shaik Sameer, Jan 17 2021
 * Implementation of strassen's algorithm in c
 */

#include <stdio.h>
#include <math.h>

void Madd(int* A, int* B, int* C, int n, int x){
    int i,j, m=x>0?n/2:n;
    for (i=0;i<m;i++)
        for (j=0;j<m;j++)
            *(C+i*m+j) = *(A+i*n+j) + *(B+i*n+j);
}

void Msub(int* A, int* B, int* C, int n, int x){
    int i,j, m=x>0?n/2:n;
    for (i=0;i<m;i++)
        for (j=0;j<m;j++)
            *(C+i*m+j) = *(A+i*n+j) - *(B+i*n+j);
}

void strassen(int *a, int *b, int *res, int n)
{
    /*
                            a00 a01   b00 b01
                            a10 a11 x b10 b11

            p = (a00 + a11) * (b00 + b11)        res00 = p + s - t + v
            q = (a10 + a11) * b00                res01 = r + t
            r = (a00) * (b01 - b11)              res10 = q + s
            s = a11 * (b10 - b00)                res11 = p + r - q + u
            t = (a00 + a01) * b11
            u = (a10 - a00) * (b00 + b01)
            v = (a01 - a11) * (b10 + b11)

            Recurrence relation = 7T(N/2) + O(N^2) = O(N ^ 2.8) < O(N^3)
     */
    if (n == 2)
    {
        int p = (*a + *(a + n + 1)) * (*b + *(b + n + 1));                      //(a00 + a11) * (b00 + b11)
        int q = (*(a + n) + *(a + n + 1)) * (*b);                               //(a10 + a11) * b00
        int r = (*(a)) * (*(b + 1) - *(b + n + 1));                             //(a00) * (b01 - b11) 
        int s = (*(a + n + 1)) * (*(b + n) - *(b));                             //a11 * (b10 - b00)
        int t = (*a + *(a + 1)) * (*(b + n + 1));                               //(a00 + a01) * b11
        int u = (*(a + n) - *a) * (*b + *(b+1));                                //(a10 - a00) * (b00 + b01)
        int v = (*(a + 1) - *(a+ n + 1)) * (*(b + n) + *(b + n + 1));           //(a01 - a11) * (b10 + b11)

        *(res) = p + s - t + v; 
        *(res + 1) = r + t; 
        *(res + n) = q + s; 
        *(res + n + 1) = p + r - q + u; 
    }

    else
    {
        int m = n/2, x[m][m], y[m][m], o[n][n]; 
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
               o[i][j] = 0; 

        // p
        int p[m][m]; 
        /*  In case of 2x2 matrices: 
                * (a00 + a11)
                * a00 = *(a + 0 * n + 0)
                * a11 = *(a + n * 1 + 1)
            In General for NxN matrices:
            a00 = base address of first quadrant i.e., a
            a11 = base address of fourth quadrant i.e., a + (N * N/2) + N/2 * 1
         */
        Madd(a, a+m*(n+1), x, n, 1); // (a00 + a11)
        Madd(b, b+m*(n+1), y, n, 1); // (b00 + b11)
        strassen(x, y, p, m); 

        // q = (a10 + a11) * b00 
        int q[m][m]; 
        Madd(a+m*n, a+m*(n+1), x, n, 1); //(a10 + a11)
        Madd(b, o, y, n, 1); // b00 + dummy matrix
        strassen(x, y, q, m); 

        // r = (a00) * (b01 - b11)
        int r[m][m]; 
        Madd(a, o, x, n, 1); // a00 + dummy array 
        Msub(b + m, b + m*(n+1), y, n, 1); // (b01 - b11) 
        strassen(x, y, r, m); 

        // s = a11 * (b10 - b00)
        int s[m][m]; 
        Madd(a+m*(n+1), o,x, n, 1);  // a11 + dummy array 
        Msub(b+m*n, b, y, n, 1); // b10-b00
        strassen(x, y, s, m); 

        // t = (a00 + a01) * b11
        int t[m][m]; 
        Madd(a, a + m, x, n, 1); // a00+a01
        Madd(b+m*(n+1), o, y, n, 1); // b11 + dummy array
        strassen(x, y, t, m); 

        // u = (a10 - a00) * (b00 + b01)
        int u[m][m]; 
        Msub(a+m*n, a, x, n, 1);  // a10-a00
        Madd(b, b+m, y, n, 1); // boo + b01
        strassen(x, y, u, m); 

        // v = (a01 - a11) * (b10 + b11)
        int v[m][m]; 
        Msub(a+m, a+m*(n+1), x, n, 1); // a01-a11
        Madd(b+m*n, b+m*(n+1), y, n, 1); //b10+b11
        strassen(x, y, v, m); 

        /*Calculating the 4 parts for the result matrix*/
        int W[m][m], X[m][m], Y[m][m], Z[m][m];
        Msub(v,t,x,m,0);
        Madd(s,x,y,m,0);
        Madd(p,y,W,m,0); // W=P+S-T+V
        Madd(r,t,X,m,0); // X==R+T
        Madd(q,s,Y,m,0); // Y=Q+S
        Msub(u,q,x,m,0);
        Madd(r,x,y,m,0);
        Madd(p,y,Z,m,0); // Z=P+R-Q+U

        /*Conquering 4 parts in the result matrix*/
        for (int i=0;i<m;i++)
            for (int j=0;j<m;j++){
                *(res+i*n+j) = W[i][j]; //res[0][0]=W
                *(res+i*n+j+m) = X[i][j]; //res[0][1]=X
                *(res+(i+m)*n+j) = Y[i][j]; //res[1][0]=Y
                *(res+(i+m)*n+j+m) = Z[i][j]; //res[1][1]=Z
            }
        
    }
}

int main(int argc, char const *argv[])
{
    int N; 
    printf("Enter the order of the square matrix: ");
    scanf("%d", &N); 

    int a[N][N]; 
    printf("Enter the elements into the matrix a\n"); 
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
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
    
    strassen(a, b, res, N); 
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
