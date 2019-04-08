#include <stdlib.h>
#include <stdio.h>
#include "file.h"
#include "graphe.h"

#define TAILLE 256


int getMaxDepth(int* mark,int u,Adjarray adjarray,int *tab_degree,int depth){

	mark[u]=1;
	int index = adjarray.cd[u];
	int d = tab_degree[u];
	int max = depth;
	for (int i = index; i < index+d; ++i)
	{

		int v = adjarray.adj[i];
		if(mark[v]==0){
			int depth_v = getMaxDepth(mark,v,adjarray,tab_degree,depth+1);
			if(depth_v>max){
				max = depth_v;
			}
		}
	}
	
	return max;
	

}
int get_component_size(int racine,int size,Adjarray adjarray,int *tab_degree){

	int * mark = malloc(size * sizeof(int));
	int component_size = 0;
	mark[racine]=1;

	File *file = file_init();
	enfiler(file,racine);
	component_size++;

	while(file->premier != NULL){
		int u = defiler(file);
		int index = adjarray.cd[u];
		int d = tab_degree[u];
		
		for (int i = index; i < index+d; ++i){
			int v = adjarray.adj[i];
			if(mark[v]==0){
				mark[v]=1;
				enfiler(file,v);
				component_size++;
			}
		}

	}
	
	return component_size;


}

int main(){
	static const char filename[] = "graphs_cleaned/email-Eu-core.txt";

	int nbNodes = getNbNodes(filename);
	printf("the number of nodes = %d\n",nbNodes );

	int nbLiens = getNbEdges(filename);
	int *tab_degree = get_tab_degree(filename,nbNodes);

 	Adjarray adjarray = get_tab_adjacent(filename,nbNodes,nbLiens,tab_degree);


 	int * mark = malloc(nbNodes * sizeof(int));
	int diameter = getMaxDepth(mark,0,adjarray,tab_degree,0);
	printf("diameter = %d\n",diameter);

	int component_size = get_component_size(0,nbNodes, adjarray,tab_degree);
	printf("component_size = %d\n", component_size);



	return 0;
}