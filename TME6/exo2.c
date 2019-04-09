#include<stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "graphe.h"
#define TAILLE 256



int get_minimumNode(int *tab_degree, int size){
  int min = tab_degree[0];
  int min_node = 0;
  int i;
  for(i = 0; i<size;i++){
    if(tab_degree[i]<min){
      min = tab_degree[i];
      min_node = i;
    }
  }

  return min_node;
}


bool existe_lien(Adjarray adjarray, int * tab_degree,int node1, int node2){
  
  int index = adjarray.cd[node1];
  int d = tab_degree[node1];
  bool existe = false;
    int i;
    for(i=index;i<index+d;i++){
      if(adjarray.adj[i]==node2){
        existe = true;
      }

    }  

    return existe;

}

void writeFilePlot(int *tab_degree,int* tab_core,int size){
  /*write degree distribution in a file*/

 
  FILE * fichier = NULL;
  fichier = fopen("exo2.plot","w");
  if(fichier!=NULL){
    fprintf(fichier,"# degree   core\n");
    for(int i=0;i<size;i++){

        fprintf(fichier,"%d     %d\n",tab_degree[i],tab_core[i]);
      
    }

  }
}
void core_decomposition(int *tab_degree,Adjarray adjarray, int max_node, int* tab_renommage){

  int size = max_node+1;
  //copy a tab_degree
  int *tab_degree_copy = malloc(size*sizeof(int));
  for (int i = 0; i < size; ++i)
  {
    tab_degree_copy[i] = tab_degree[i];
  }


 
  int nbNodes = adjarray.n;
  int *core_tab = malloc(nbNodes*sizeof(int));
  int *tab_order = malloc(nbNodes*sizeof(int));
  int c =0;
  while(nbNodes>0){
   
    
    int v = get_minimumNode(tab_degree_copy,size);
    int i_v = tab_renommage[v];

    if(tab_degree_copy[v]>c){
      c = tab_degree_copy[v];
    }

    
    core_tab[i_v]=c;

    //on supprime le node minimum dans le graphe
    int index = adjarray.cd[i_v];
    int d = tab_degree[v];
    

    int i;
    for(i=index;i<index+d;i++){
      tab_degree_copy[adjarray.adj[i]]--;

    }  
    tab_degree_copy[v]=INT_MAX;
    tab_order[nbNodes-1]=v;
    nbNodes--;
   
  }

  writeFilePlot(tab_degree,core_tab,size);

  
}
int main(){
  // static const char filename[] = "data/exemple.txt";

  static const char filename[] = "scholar/net.txt";
  
  int max_node  = get_max_node(filename);
  int nbNodes = getNbNodes(filename);
  
  int* tab_renommage = get_tab_renommage(filename, max_node);
  int* tab_renomme = get_tab_renomme(filename,  nbNodes);

  printf("nbNodes = %d\n",nbNodes );
  int nb_edges = getNbEdges(filename);

  int *tab_degree = get_tab_degree(filename,max_node+1);

  printf("fin de lire tab_degree\n");
  Adjarray adjarray = get_tab_adjacent(max_node,filename,nbNodes,nb_edges,
    tab_degree, tab_renommage,tab_renomme);
  printf("fin de lire tab_adjarray\n");
  core_decomposition(tab_degree,adjarray,max_node, tab_renommage);
 

}