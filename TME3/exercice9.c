#include <stdlib.h>
#include <stdio.h>
#include "file.h"
#include "graphe.h"

#define TAILLE 256

void multiply(int size,int A[size][size], int B[size][size], int C[size][size]){


	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			C[i][j]=0;

			for (int k = 0; k < size; ++k)
			{

				C[i][j]+=A[i][k]*B[k][j];
			}

		}
	}
}

int getNbTriangle(int n, int graph[n][n]){


	printf("size = %d\n", n);

	// pour stocker graph^2
	int aux2[n][n];

	printf("size = %d\n", n);
	// pour stocker graph^3
	int aux3[n][n];
	printf("size = %d\n", n);
	// printf("size = %d\n", n);

	/*for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			printf(" %d ", graph[i][j] );
		}
	}*/
	// multiply(size,graph,graph,aux2);

	// multiply(size,graph,aux2,aux3);

	int sum = 0;

	// for (int i = 0; i < size; ++i)
	// {
	// 	sum+=aux3[i][i];
	// }


	return sum/6;
}
int main()
{
	static const char filename[] = "graphs_cleaned/email-Eu-core.txt";
	int nbNodes = getNbNodes(filename);
	int matrix_adjacent[nbNodes][nbNodes]; 
	//initialiser matrix adjacent
	for (int i = 0; i < nbNodes; ++i){
	    for (int j = 0; j < nbNodes; ++j){
	     	 matrix_adjacent[i][j] = 0;    
	    }
  	}
	generate_matrix(filename,nbNodes, matrix_adjacent);

	printf("nbNodes = %d\n", nbNodes);

	
	int n_triangle = getNbTriangle(nbNodes,matrix_adjacent);
	printf("the number of triangle = %d\n", n_triangle);

	return 0;
}