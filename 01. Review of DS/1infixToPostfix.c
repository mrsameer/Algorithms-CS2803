#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>


bool isOperand(char c)
{
   return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); 
}

int prec(char c) 
{
    switch (c)
    {
    case '+':
    case '-':
        return 1; 
    
    case '*':
    case '/':
        return 2; 

    case '^':
        return 3;
    default:
        return -1;
    }
}
void infixToPost(char str[], int N)
{
    int top = -1; 
    char *stack = malloc(sizeof(char)*N); 

    printf("The Postfix expression is: "); 
    for (int i = 0; i < N; i++)
    {
        if (isOperand(str[i]))
        {
            printf("%c", str[i]);
        }
        else if (str[i] == '(')
        {
            stack[++top] = str[i];
        }
        else if (str[i] == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                printf("%c", stack[top--]);
            }
            top--; 
        }
        else
        {
            while (top != -1 && prec(str[i]) <= prec(stack[top]))
            {
                printf("%c", stack[top--]);
            }
            stack[++top] = str[i];
        }
        
    }

    while (top != -1)
    {
        printf("%c", stack[top--]); 
    }
    printf("\n");
    
}
int main(int argc, char const *argv[])
{
    printf("Enter the length of the string: "); 
    int N; 
    scanf("%d", &N); 

    char *str = malloc(sizeof(char) * N);
    printf("Enter the string: "); 
    scanf("%s", str); 

    infixToPost(str, N); 
    return 0;
}
