/*
 * Program to add two polynomials using linked lists
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    int coeff; 
    int power; 
    struct node *next; 
}typedef Node; 


Node* insert(Node *poly, int c, int p)
{
    if (poly == NULL)
    {
        poly = (Node*)malloc(sizeof(Node)); 
        poly->coeff = c; 
        poly->power = p; 
        poly->next = NULL; 
    }
    else
    {
        Node *temp = (Node*)malloc(sizeof(Node)); 
        temp->coeff = c; 
        temp->power = p; 
        Node *temp2 = poly; 
        while (temp2->next != NULL)
        {
            temp2 = temp2->next; 
        }
        temp2->next = temp; 
    }
    return poly; 
    
}

Node* add(Node *p1, Node *p2)
{
    Node *p3 = NULL;
    while (p1 && p2)
    {
        if (p1->power > p2->power)
        {
            p3 = insert(p3, p1->coeff, p1->power);
            p1 = p1->next; 
        }
        else if (p1->power < p2->power)
        {
            p3 = insert(p3, p2->coeff, p2->power);
            p2 = p2->next; 
        }
        else
        {
            p3 = insert(p3, p1->coeff + p2->coeff, p1->power);
            p1 = p1->next; 
            p2 = p2->next; 
        }    
    }
    while (p1 || p2)
    {
        if (p1)
        {
            p3 = insert(p3, p1->coeff, p1->coeff);
            p1 = p1->next; 
        }
        if (p2)
        {
            p3 = insert(p3, p2->coeff, p2->coeff);
            p2 = p2->next; 
        }
        
    }
    
    return p3; 
}

void printPoly(Node *poly)
{
    while (poly != NULL)
    {
        printf("%dx^%d", poly->coeff, poly->power); 
        poly = poly->next; 
        if (poly != NULL)
        {
            printf("+");
        }
        
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    
    printf("Enter the degree of the polynomial 1: "); 
    int N1;
    scanf("%d", &N1); 

    Node *p1 = NULL; 
    int p, c; 
    for (int i = 0; i < N1; i++)
    {
        printf("Enter the term:%d's(left to right) coefficient: ",i+1); 
        scanf("%d", &c);
        printf("Enter the term:%d's power: ", i+1); 
        scanf("%d", &p); 

        p1 = insert(p1, c, p); 
    }

    printf("Enter the degree of the polynomial 2: "); 
    int N2;
    scanf("%d", &N2); 

    Node *p2 = NULL; 
    for (int i = 0; i < N2; i++)
    {
        printf("Enter the term:%d's(left to right) coefficient: ",i+1); 
        scanf("%d", &c);
        printf("Enter the term:%d's power: ", i+1); 
        scanf("%d", &p); 

        p2 = insert(p2, c, p); 
    }

    printf("Polynomial p1: ");
    printPoly(p1); 
    printf("Polynomial p2: ");
    printPoly(p2); 
    Node *p3 = add(p1, p2); 
    printf("p1+p2=");
    printPoly(p3); 
    return 0;
}
