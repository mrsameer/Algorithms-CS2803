#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int search(int array[], int N, int key)
{
    for (int i = 0; i < N; i++)
    {
        if (array[i] == key)
        {
            return i; 
        }
        
    }
    return -1; 
}
int main(int argc, char const *argv[])
{
    int N, ele;
    printf("Enter the number of elements: ");
    scanf("%d", &N);

    int *array = malloc(sizeof(int)*N);
    printf("Enter the elements: "); 
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &array[i]);
    }
    
    bool quit = false; 
    int selection; 
    while (!quit)
    {
        printf("\nSelect\n1.Search\n2.Quit\n");
        scanf("%d", &selection);

        switch (selection)
        {
        case 1:
            printf("Enter the element you wanna search: ");
            scanf("%d", &ele);
            int result = search(array, N, ele);
            if (result == -1)
            {
                printf("Not found :/");
            }
            else
            {
                printf("Found at index:%d", result);
            }
            break;
        case 2:
            quit = true; 
            break;
        default:
            break;
        }
    }
    
    return 0;
}
