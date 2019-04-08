#include<stdlib.h>
#include <stdio.h>
#include<string.h>
#include <time.h>
#include "graphe.h"
#define TAILLE 256
#define EMAIL "data/email-Eu-core.txt"
#define AMAZON "data/com-amazon.ungraph.txt"
#define LJ "data/com-lj.ungraph.txt"
#define ORKUT "com-orkut.ungraph.txt"



void exercice2(const char* filename){

	float temps;
    clock_t t1, t2;
 
    t1 = clock();
 
	int nb_nodes = getNbNodes(filename);
	int nb_liens = getNbEdges(filename);

	printf("the number of node is %d\n",nb_nodes);
	printf("the number of edges is %d\n",nb_liens);
	 t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);
}
int main(){
 
  exercice2(AMAZON);
 
  return 0;


}
