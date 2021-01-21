/*
 * Implementation of Kruskal's algorithm in c. 
 * By Shaik Sameer, Jan 13 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void kruskal(int n, int graph[n][n]){
	int p[n],min, sum = 0, i, j,ne = 0,a ,b, u, v;

    // initially make the parent of every node as 0 
	for(i = 0; i < n; i++)
		p[i] = 0;
    
    // we iterate over n-1  as mst contains n-1 edges. 
	while(ne < n-1){
		min = INT_MAX;
        // finds minimum cost edge 
		for(i = 0;i < n; i++){
			for(j = 0; j < n; j++){
				if(graph[i][j] < min){
					min = graph[i][j];
					u = a = i;
					v = b = j;
				}
			}
		}
            // find the parent of u 
			while(p[u])
				u = p[u];
            // find the parent of v
			while(p[v])
				v = p[v];
            
            // if both parents of u, v are not same (it is not a cycle)
			if(u != v){
				sum += min;
				printf("edge %d --> %d----%d\n",a,b,min);
				ne++;
				p[v] = u;
			}
            // already visited so break the edge of the graph so not to consider it again
			graph[a][b] = graph[b][a] = INT_MAX;
	}
	printf("\nThe cost of minimum spanning tree is: %d",sum);
}
int main(void){
	int n,i,j;
	printf("\nEnter the number of vertices: ");
	scanf("%d",&n);
	int graph[n][n];
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d",&graph[i][j]);
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(graph[i][j] == 0)
				graph[i][j] = INT_MAX;
		}
	}
	kruskal(n,graph);
}