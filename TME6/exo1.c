#include<stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "graphe.h"
#define TAILLE 256



int get_minimumNode(int *tab_degree_copy, int size){
  int min = tab_degree_copy[0];
  int min_node = 0;

  for(int i = 0; i<size;i++){
    if( tab_degree_copy[i]<min){
      min = tab_degree_copy[i];
      min_node = i;
    }
  }

  return min_node;
}



int get_max_core(int * core_tab,int size){
  int max = core_tab[0];
  int i;
  for(i=0;i<size;i++){
    if(core_tab[i]>max){
      max = core_tab[i];
    }
  }

  return max;

}
bool existe_lien(Adjarray adjarray, int * tab_degree_renomme,int node1, int node2,int* tab_renommage){
  
  int i_node1 = tab_renommage[node1];
  int index = adjarray.cd[i_node1];
  int d = tab_degree_renomme[i_node1];
  bool existe = false;
    int i;
    for(i=index;i<index+d;i++){
      if(adjarray.adj[i]==node2){
        existe = true;
      }

    }  

    return existe;

}
int get_size_densest_prefix(int *tab_degree_renomme,Adjarray adjarray,int *tab_order, int nb_nodes, int* tab_renommage){

 
  double* tab_density = malloc(nb_nodes*sizeof(double));
  double* tab_edges_density = malloc(nb_nodes*sizeof(double));
  //quand sub-graph contient seulement un noeud (le premier noeud)
  int nbNodes =1;
  int nbliens = 0;
  tab_density[0]=(double)nbliens/nbNodes;//nbNodes==1
  tab_edges_density[0]=0;//nbNodes==1

  for(nbNodes=2; nbNodes<nb_nodes+1;nbNodes++){

    //node1: le noeud a ajouter
    int node1 = tab_order[nbNodes-1];
    int i;
    for(i=0;i<nbNodes-1;i++){

      //node2: les noeuds existe deja dans sub-graphe
      int node2 = tab_order[i];
      if(existe_lien(adjarray,tab_degree_renomme,node1,node2,tab_renommage)){
        nbliens++;
      }
    }

    //calculer density 
    double density = (double)nbliens/ nbNodes;
    tab_density[nbNodes-1]=density;

    // int nb_edges_max = nbNodes*(nbNodes-1)/2; 
    // tab_edges_density[nbNodes-1]=(double) nbliens/nb_edges_max;

  }

 

  //calculer max_density et la taille de sub-graphe correspondant
  double max_density = 0;
  int max_size = 1;
  for (int i = 0; i < nb_nodes; i++)
  {
    if(tab_density[i]>max_density){
      max_density = tab_density[i];
      max_size = i+1;
    }
  }



  printf("max_density = %f\n", max_density);

  // printf("edges_density = %f\n",max_edge_density );
  return max_size;


}

void core_decomposition(int *tab_degree_renomme ,int nb_nodes, Adjarray adjarray,int*tab_renommage, int* tab_renomme){


  int nbNodes = adjarray.n;
  //copy a tab_degree
  int *tab_degree_copy = malloc(nbNodes*sizeof(int));
  for (int i = 0; i < nbNodes; ++i)
  {
    tab_degree_copy[i] = tab_degree_renomme[i];
  }


 
 
  int *core_tab = malloc(nbNodes*sizeof(int));
  int *tab_order = malloc(nbNodes*sizeof(int));
  int c =0;
  while(nbNodes>0){
   
    
   
    // Let v be a node with minimum degree in G
    int i_v = get_minimumNode(tab_degree_copy,nb_nodes);
     // printf("i_v = %d\n",i_v );
    int v = tab_renomme[i_v];

    // printf("v = %d\n",v );
    if(tab_degree_copy[i_v]>c){
      c = tab_degree_copy[i_v];
    }

    // printf("c = %d\n",c );
    core_tab[i_v]=c;

    //on supprime le node minimum dans le graphe
    int index = adjarray.cd[i_v];
    int d = tab_degree_renomme[i_v];

    int i;
    
    for(i=index;i<index+d;i++){
      int r_i = tab_renommage[adjarray.adj[i]];
      tab_degree_copy[r_i]--;

    }  
    tab_degree_copy[i_v]=INT_MAX;
    tab_order[nbNodes-1]=v;
    nbNodes--;
   
  }

  int max_core = get_max_core(core_tab,nb_nodes);
  printf("max core = %d\n",max_core );

  int size_densest_prefix = get_size_densest_prefix(tab_degree_renomme,adjarray,tab_order,nb_nodes,tab_renommage);

  printf("size_densest_prefix = %d\n",size_densest_prefix );

}
int main(){
  // static const char filename[] = "data/exemple.txt";
  static const char filename[] = "graphs_cleaned/com-amazon.ungraph.txt";
  // static const char filename[] = "graphs_cleaned/email-Eu-core.txt";
  int max_node  = get_max_node(filename);
  int nbNodes = getNbNodes(filename);
  
  int* tab_renommage = get_tab_renommage(filename, max_node);
  int* tab_renomme = get_tab_renomme(filename,  nbNodes);

  printf("nbNodes = %d\n",nbNodes );
  int nb_edges = getNbEdges(filename);

  int *tab_degree = get_tab_degree(filename,max_node+1);


  int * tab_degree_renomme =get_tab_degree_renomme( tab_degree,  nbNodes,  max_node,tab_renomme);


  free(tab_degree);
  
  printf("fin de lire tab_degree\n");
  Adjarray adjarray = get_tab_adjacent(filename,  nbNodes,nb_edges,tab_degree_renomme,tab_renommage);
  printf("fin de lire tab_adjarray\n");


 
  core_decomposition(tab_degree_renomme,nbNodes,adjarray, tab_renommage,tab_renomme);
 


}
