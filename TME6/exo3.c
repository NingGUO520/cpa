#include<stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "graphe.h"
#define TAILLE 256

int* tri_insertion(float* tab , int size){

  int* tab_order = malloc(size*sizeof(int));
  for (int i = 0; i < size; ++i)
  {
    tab_order[i]=i;
  }

  int i,j;
  double elem ;
  for (int i = 1; i < size; ++i)
  {
   
      elem = tab[i];
      for (j = i; j>0 && tab[j-1]<elem ;j--)
      {
        tab[j] = tab[j-1];
        tab_order[j]=tab_order[j-1];


      }
      tab[j]=elem;
      tab_order[j]=i;
  }


  return tab_order;
}
float* mkscore(Edge* list_edges,int size, int nb_edges, int t){
  float* r = malloc(size*sizeof(int));
  for (int i = 0; i < size; ++i)
  {
    r[i]=0;
  }
  // iterate t times
  // int t = 10;
  for (int i = 0; i < t; ++i)
  {
    for (int j = 0; j < nb_edges; ++j)
    {
      int a = list_edges[j].p1;
      int b = list_edges[j].p2;
      if(r[a]<=r[b]){
        r[a]++;
      }else{
        r[b]++;
      }

    }
  }


  for (int i = 0; i < size; ++i)
  {
    r[i]=(double)r[i]/t;
  }
  return r;
}

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


  int max_core = get_max_core(core_tab,adjarray.n);
  printf("max core = %d\n",max_core );

 

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
int main(){
  // static const char filename[] = "data/exemple2.txt";

  static const char filename[] = "graphs_cleaned/email-Eu-core.txt";

  int max_node  = get_max_node(filename);
  int nbNodes = getNbNodes(filename);
  
  int* tab_renommage = get_tab_renommage(filename, max_node);
  int* tab_renomme = get_tab_renomme(filename,  nbNodes);


  int nb_edges = getNbEdges(filename);

  // printf("the number of edges is %d\n",nb_edges );
  Edge* list_edges = getListEdges(filename, nb_edges);


  int *tab_degree = get_tab_degree(filename,max_node+1);


  int * tab_degree_renomme =get_tab_degree_renomme( tab_degree,  nbNodes,  max_node,tab_renomme);


  free(tab_degree);
  
  printf("fin de lire tab_degree\n");
  Adjarray adjarray = get_tab_adjacent(filename,  nbNodes,nb_edges,tab_degree_renomme,tab_renommage);
  printf("fin de lire tab_adjarray\n");


 
  core_decomposition(tab_degree_renomme,nbNodes,adjarray, tab_renommage,tab_renomme);
 


  int t =100;
  float* tab_score = mkscore(list_edges,nbNodes,nb_edges, t);

  int* tab_ordonnee = tri_insertion(tab_score,nbNodes);
  
  int res = get_size_densest_prefix(tab_degree,adjarray,tab_ordonnee,nbNodes);
  printf("size = %d\n", res);
 


}
