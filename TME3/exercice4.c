#include<stdlib.h>
#include <stdio.h>
#include "graphe.h"

#define TAILLE 256
#define EMAIL "graphs_cleaned/email-Eu-core.txt"
#define AMAZON "graphs_cleaned/com-amazon.ungraph.txt"
#define LJ "graphs_cleaned/com-lj.ungraph.txt"



void write_tab_degree(int* tab_degree, int size,const char* filename){

  /*Write the node-degree dans un fichier*/
  FILE * fichier = NULL;
  fichier = fopen("result_exo4_amazon.txt","w");
  if(fichier!=NULL){
    int i;
    fprintf(fichier,"#node    degree\n");
    for(i=0;i<size;i++){

      if(tab_degree[i]>0){
      fprintf(fichier, "%d    %d\n",i,tab_degree[i]);
      }
    }
  }
}

void exercice4(const char* filename){
  int size = get_max_node(filename)+1;
  int *tab_degree = get_tab_degree(filename,size);

  write_tab_degree(tab_degree,size,filename);
 
  
}


int main(){

 
  exercice4(AMAZON);

  return 0;


}
