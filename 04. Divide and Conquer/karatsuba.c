/*
 * Implementation of large integer multiplication algorithm in c
 * By Shaik Sameer, Jan 13 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max(int a, int b)
{
    return a>b?a:b; 
}

int mul(int num1, int num2){
	int ans = 0,count = 0;

    // binary multiplication
	while(num2){
		if(num2%2 == 1)
			ans += num1 << count;
		count++;
		num2 /= 2;
	}
	return ans;
}

int karatsuba(int x, int y)
{
    /*
     * Let the first and second half parts of x be a, b respectively. 
     * lly c, d of y
     * x.y = 10^n a.c + 10^n/2 (ad + bc) + bd
     * Recursively compute ac --(1), bd --(2), ((a+b),(c+d)) -- (3)
     * ad + bc = (3) - (1) - (2) // guass's trick
     * Upshot: only 3 recursive multiplications(and some additions)
     * Time complexity = O(n ^ (base 2 log3))
     */

    // if x or y == 0 then return 0
    if (x == 0 || y == 0) return 0; //for safety as log10(0) = infinity

    // calculate the n (largest length among both x and y)
    int n = max(floor(log10(x)) + 1, floor(log10(x)) + 1); 

    // if n == 1 just multiply x and y and return (base case)
    if (n == 1) return x *  y; 

    int nby2 = n/2; 
 
    // parition x into a, b and y into c, d
    int a = x / (int)pow(10, nby2); 
    int b = x % (int)pow(10, nby2); 
    int c = y / (int)pow(10, nby2);
    int d = y % (int)pow(10, nby2); 

    int ac = karatsuba(a, c); 
    int bd = karatsuba(b, d); 
    int ab_cd = karatsuba((a+b), (c+d));
    int ad_bc = ab_cd - ac - bd; 

    return mul((int)pow(10, nby2 * 2), ac) + mul((int)pow(10, nby2), ad_bc) + bd;
}

int main(int argc, char const *argv[])
{
    int x, y; 
    printf("Enter the two large integers: "); 
    scanf("%d%d", &x, &y); 
    printf("%dx%d=%d\n", x, y, karatsuba(x,y));
    return 0;
}
