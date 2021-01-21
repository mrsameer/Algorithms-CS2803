#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int key; 
    struct node *left, *right; 
}typedef Node; 

Node* insert(Node *root, int key)
{
    if (root == NULL)
    {
        Node *temp = malloc(sizeof(Node));
        temp->key = key; 
        temp->left = temp->right = NULL; 
        return temp; 
    }
    if (key < root->key)
    {
        root->left = insert(root->left, key);
    }
    else
    {
        root->right = insert(root->right, key);
    }
    return root; 
    
}

Node *minValNode(Node *node)
{
    Node *temp = node; 
    while (temp && temp->left != NULL)
    {
        temp = temp->left; 
    }
    return temp; 
    
}

Node *delete(Node* root, int key)
{
    if (root == NULL)
    {
        return root;
    }
    if (key < root->key)
    {
        root->left = delete(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = delete(root->right, key);
    }
    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right; 
            return temp; 
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left; 
            return temp; 
        }
       Node *temp = minValNode(root->right);
       root->key = temp->key; 
       root->right = delete(root->right, temp->key); 
    }
    return root;
}

void inorder(Node* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void preorder(Node* root)
{
    if (root != NULL) {
         printf("%d ", root->key);
        inorder(root->left);
        inorder(root->right);
    }
}

void postorder(Node* root)
{
    if (root != NULL) {
        inorder(root->left);
        inorder(root->right);
        printf("%d ", root->key);
    }
}

int main(int argc, char const *argv[])
{
    Node *root = NULL; 
    int selection, ele; 
    bool quit = false; 
    while (!quit)
    {
        printf("Select\n1.Insert\n2.Delete\n3.Inorder Traversal\n4.PostOrder Traversal\n5.PreOrderTraversal\n6.Quit\n"); 
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            printf("Enter the element: ");
            scanf("%d", &ele);
            root = insert(root, ele); 
            break;
        case 2:
            printf("Enter the element: "); 
            scanf("%d", &ele);
            root = delete(root, ele); 
            break; 
        case 3:
            inorder(root);
            break; 
        case 4:
            postorder(root);
            break;
        case 5:
            preorder(root);
            break;
        case 6:
            quit = true; 
            break;
        default:
            break;
        }
    }
    
    return 0;
}
