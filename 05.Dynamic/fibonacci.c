/*
 * Program to find the nth fibonacci number using Dynamic programming paradigm 
 * By Shaik Sameer, jan 20 2021
 */

#include <stdio.h>

long long fibonacci(int N) {
    long long table[N+1]; // create a table of size N+1
    table[0] = 0;   // 0th fibonacci number
    table[1] = 1;   // 1st fibonacci number
    for (int i = 2; i <= N; i++) table[i] = table[i-1] + table[i-2]; // sum of previous fibonacci numbers
    return table[N]; 
}

int main(int argc, char const *argv[])
{
    int N; 
    printf("Enter the value of N: "); 
    scanf("%d", &N); 
    printf("%llu", fibonacci(N)); 
    return 0;
}
