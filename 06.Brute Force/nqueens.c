#include <stdio.h>
#include <stdlib.h>

int count = 0; 

void print(int board[], int n){
	int i,j;
	printf("\n\nSolution %d\n",++count);
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			if(board[i] == j)
				printf("Q\t");
			else
				printf("-\t");
		}
		printf("\n");
	}
}

int valid(int board[], int pos)
{
    for (int i = 1; i < pos; i++)
    {
        // if this particular is in horizontal with any previous queen or 
        // diagonal with any previous queen then this will return 0 
        // as it is not a valid position 
        if ((board[pos] == board[i]) || (abs(board[i] - board[pos]) == abs(i-pos)))
        {
            return 0; 
        }
        
    }
    return 1; 
}

void queen(int N)
{
    int board[N+1]; // stores column number of queen i from chess board in board array 

    int row = 1;  // column number of queen

    board[row] = 0;   // initially queen 1 is at column 0 (it is nowhere)  in chess board

    // row varies from 1 to N (and it is nothing but position of queen columnwise in a row)
    // as we dedicate each row for each qeen 
    while (row != 0)
    {
        // first fix the position of the queen 1st queen 
        do
        {
            board[row]++; 
        } while (board[row] <= N && !valid(board, row)); // column number of queen belongs to row row must <= N and if it is not a valid position 
        // fix a column number for remaining queens
        if (board[row] <= N)
        {
           // if valid positions are there are for all N queens then print the chess board 
           if (row == N)
           {
               print(board, N); 
           }
           else
           {
               board[++row] = 0;
           }
        }
        else 
            row--; // backtrack 
    }
    

}

int main(int argc, char const *argv[])
{
    int N; 
    printf("\nEnter the number of queens: "); 
    scanf("%d", &N); 
    queen(N); 
    return 0;
}
