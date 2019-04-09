#include<stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include "graphe.h"
#define TAILLE 256
#define EMAIL "graphs_cleaned/email-Eu-core.txt"
#define AMAZON "graphs_cleaned/com-amazon.ungraph.txt"
#define LJ "graphs_cleaned/com-lj.ungraph.txt"
#define EXEM "data/exemple.txt"


void calculQuantity(const char* filename,int nbNodes, int max_node, int* tab_renommage,int* tab_renomme){
  int* tab_degrees =  get_tab_degree(filename,max_node+1);
  int* tab_degrees_renomme = get_tab_degree_renomme(tab_degrees,nbNodes,max_node, tab_renomme);

  //  printf("tab_degrees:\n");
  // for (int i = 0; i < max_node+1; ++i)
  // {
  //   printf("%d ", tab_degrees[i]);
  // }

  // printf("tab_degrees_renomme:\n");
  // for (int i = 0; i < nbNodes; ++i)
  // {
  //     printf("%d ", tab_degrees_renomme[i]);
  // }
  int s = get_somme_degree(tab_degrees,max_node+1);
  printf("somme 1= %d\n",s );


   int s2 = get_somme_degree(tab_degrees_renomme,nbNodes);
  printf("somme 2= %d\n",s2 );
  // int* tab_degrees = read_tab_degree(size);
  FILE* file = fopen(filename,"r");

  uint64_t quantity = 0;
    uint64_t quantity2 = 0;

  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#'){
    int a,b;
    sscanf(buf,"%d %d\n",&a,&b);
    quantity+=tab_degrees[a]*tab_degrees[b];

      int i_a = tab_renommage[a];
      int i_b = tab_renommage[b];
        quantity2+=tab_degrees_renomme[i_a]*tab_degrees_renomme[i_b];

    }
  }

  printf("the quantity is = %ld \n",quantity);
  printf("the quantity 2 is = %ld \n",quantity2);


}

void exercice5(const char* filename){

  float temps;
  clock_t t1, t2;
 
   int nbNodes = getNbNodes(filename);
  int max_node = get_max_node(filename);
  int * tab_renommage = get_tab_renommage(filename,max_node);
  int* tab_renomme =  get_tab_renomme(filename,nbNodes);
  int nblien = getNbEdges(filename);
  printf("nblien = %d\n",nblien );
  int size = get_max_node(filename)+1;
  t1 = clock();
  calculQuantity(filename, nbNodes,max_node,tab_renommage,tab_renomme);
  t2 = clock();

  temps = (float)(t2-t1)/CLOCKS_PER_SEC*1000;
  printf("temps = %f ms \n", temps);
}
int main(){

 
  exercice5(AMAZON);
  // exercice5(EXEM);
  return 0;


}
