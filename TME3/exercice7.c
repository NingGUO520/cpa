
#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"
#define TAILLE 256





int main(){
  static const char filename[] = "graphs_cleaned/com-amazon.ungraph.txt";
  // static const char filename[] = "graphs_cleaned/email-Eu-core.txt";
  // static const char filename[] = "data/exemple.txt";
  /*As a list of edges*/
  int nbLiens = getNbEdges(filename);
  printf("nbLiens = %d\n", nbLiens);
  Edge *list_edges = getListEdges(filename,nbLiens);
  
  int max_node = get_max_node(filename);

   /*As an adjacency array*/
  int nbNodes = getNbNodes(filename);
  int *tab_degree = get_tab_degree(filename,max_node+1);

  int *tab_renommage = get_tab_renommage(filename,max_node);
  int* tab_renomme = get_tab_renomme(filename,nbNodes);
  int* tab_degree_renomme = get_tab_degree_renomme(tab_degree,  nbNodes,  max_node, tab_renomme);

  // printf("tab_degree\n"  );
  // for (int i = 0; i < max_node+1; ++i)
  // {
  //   printf("%d ",tab_degree[i] );
  // }

  Adjarray adjarray = get_tab_adjacent(filename,nbNodes,nbLiens,tab_degree_renomme,tab_renommage);


  printf("n = %d\n",adjarray.n );
  printf("m = %d\n",adjarray.m );

 
  //   printf("cd : \n");

  // for(int i=0;i<nbNodes;i++){
  //   printf("%d ", adjarray.cd[i] );
  // }
  // printf("adj : \n");
  // int somme_degree = get_somme_degree(tab_degree,max_node+1);
  // for (int i = 0; i < somme_degree; ++i)
  // {
  // printf("%d ", adjarray.adj[i] );  
  // }
 

  /* As a adjacency matrix */
  // int matrix_adjacent[nbNodes][nbNodes]; 
  // for (int i = 0; i < nbNodes; ++i)
  // {
  //   for (int j = 0; j < nbNodes; ++j)
  //   {
  //     matrix_adjacent[i][j] = 0;
      
  //   }
  // }
  // int nb = 0;
  // generate_matrix(filename,nbNodes, matrix_adjacent);
  // for (int i = 0; i < nbNodes; ++i)
  // {
  //   for (int j = 0; j < nbNodes; ++j)
  //   {
  //     // printf("%d ",matrix_adjacent[i][j] );
  //     if(matrix_adjacent[i][j]==1){
  //       nb++;
  //     }
  //   }
  // }

  // printf("nb = %d\n", nb );


 
 return 0;
}