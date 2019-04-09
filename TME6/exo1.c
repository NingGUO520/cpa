#include<stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "graphe.h"
#define TAILLE 256

int* read_tab_degree(int size){
  int* tab_degrees = malloc(size* sizeof(int));

  printf("size  = %d\n",size );

  FILE* file = fopen("tab_degrees/tab_degree_amazon.txt","r");

  printf("lire le fichier \n");
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#'){
      int n,d;
      sscanf(buf,"%d %d\n",&n,&d);
      tab_degrees[n]=d;
           


    }
  }
  return tab_degrees;

}

int get_minimumNode(int *tab_degree, int size){
  int min = tab_degree[0];
  int min_node = 0;
  int i;
  for(i = 0; i<size;i++){
    if( tab_degree[i]<min){
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
int get_size_densest_prefix(int *tab_degree_renomme,Adjarray adjarray,int *tab_order, int size, int* tab_renommage){

 
  double* tab_density = malloc(size*sizeof(double));
  double* tab_edges_density = malloc(size*sizeof(double));
  //quand sub-graph contient seulement un noeud (le premier noeud)
  int nbNodes =1;
  int nbliens = 0;
  tab_density[0]=(double)nbliens/nbNodes;//nbNodes==1
  tab_edges_density[0]=0;//nbNodes==1

  for(nbNodes=2; nbNodes<size+1;nbNodes++){

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
  for (int i = 0; i < size; i++)
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
   
    
    int i_v = get_minimumNode(tab_degree_copy,nbNodes);
    int v = tab_renomme[i_v];

    if(tab_degree_copy[i_v]>c){
      c = tab_degree_copy[i_v];
    }

    
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

  int size_densest_prefix = get_size_densest_prefix(tab_degree_copy,adjarray,tab_order,nb_nodes,tab_renommage);

  printf("size_densest_prefix = %d\n",size_densest_prefix );

}
int main(){
  // static const char filename[] = "data/exemple.txt";
  // static const char filename[] = "graphs_cleaned/com-amazon.ungraph.txt";
  static const char filename[] = "graphs_cleaned/email-Eu-core.txt";
  int max_node  = get_max_node(filename);
  int nbNodes = getNbNodes(filename);
  
  int* tab_renommage = get_tab_renommage(filename, max_node);
  int* tab_renomme = get_tab_renomme(filename,  nbNodes);

  printf("nbNodes = %d\n",nbNodes );
  int nb_edges = getNbEdges(filename);

  int *tab_degree = get_tab_degree(filename,max_node+1);
  int * tab_degree_renomme =get_tab_degree_renomme(tab_degree,nbNodes,max_node );

  for (int i = 0; i < 100; ++i)
  {
    printf("%d  ",tab_degree_renomme[i] );
  }
  printf("fin de lire tab_degree\n");
  Adjarray adjarray = get_tab_adjacent(max_node,filename,nbNodes,nb_edges,
    tab_degree, tab_renommage,tab_renomme);
  printf("fin de lire tab_adjarray\n");
  core_decomposition(tab_degree_renomme,nbNodes,adjarray, tab_renommage,tab_renomme);
 


}
