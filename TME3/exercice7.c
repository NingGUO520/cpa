
#include <stdlib.h>
#include <stdio.h>
#include "Edge.h"
#define TAILLE 256
typedef struct 
{ 
  unsigned n; // number of nodes
  unsigned m; //number of edges
  unsigned *cd;
  unsigned *adj;
  
}Adjarray;

int getNbNodes(const char* filename){
  FILE* file = fopen(filename,"r");

  int max = 0;
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    int a,b;
    sscanf(buf,"%d %d\n",&a,&b);
    if(a>max) max = a;
    if(b>max) max = b;
  }
  int nbNodes = max + 1;
  printf("the number of node is %d\n",nbNodes);
  return nbNodes;
}



int getNbEdges(const char* filename){
	FILE* file = fopen(filename,"r");

	  int nbLiens = 0;
	  char buf[TAILLE];
	  while(fgets(buf,TAILLE,file)!=NULL){
	   if(buf[0]!='#'){
	    int a,b;
	    sscanf(buf,"%d %d\n",&a,&b);
	 
	    nbLiens++;
	    }
	  }

  return nbLiens;
}
int* get_tab_degree(const char* filename, int taille){

  FILE* file = fopen(filename,"r");
  int * tab_degrees = malloc(taille * sizeof(int));

  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    int a,b;
    sscanf(buf,"%d %d\n",&a,&b);
    tab_degrees[a]++;
    tab_degrees[b]++;    
  }
  
  return tab_degrees;
}
int get_somme_degree(int *tab_degree, int size){
  int somme = 0;
  int i;
  for(i=0;i<size;i++){
    somme = somme + tab_degree[i];
  }
  return somme;
}

Adjarray get_tab_adjacent(const char* filename, int nbNodes, int nb_edges,int *tab_degree){

  
  int somme_degree = get_somme_degree(tab_degree,nbNodes);
  Adjarray adjarray;
  adjarray.n = nbNodes;
  adjarray.m = nb_edges;
  int * adj = malloc(somme_degree * sizeof(int));
  int * cd = malloc((nbNodes+1)* sizeof(int));
  int i;

  for(i=0;i<somme_degree;i++){
    adj[i]=-1;
  }


  cd[0] = 0;
  
  int acc = 0;
  for(i = 0 ;i < nbNodes;i++){
    acc = acc + tab_degree[i];
    cd[i+1] = acc;
  }

  FILE* file = fopen(filename,"r");
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    int a,b;
    sscanf(buf,"%d %d\n",&a,&b);
   
    int offset = 0;
    int index = cd[a];
    while(adj[index+offset]!=-1){
      
   
      offset++;
    }
   
    adj[index+offset] = b;


    offset = 0;
    index = cd[b];
    while(adj[index+offset]!=-1){
      
   
      offset++;
    }
   
    adj[index+offset] = a;
  }
  adjarray.cd  = cd;
  adjarray.adj = adj;

  return adjarray;

}
Edge* getListEdges(const char* filename, int n){
  

  Edge* list_edges = malloc(n*sizeof(Edge)) ;
	FILE* file = fopen(filename,"r");

	  int i = 0;
	  char buf[TAILLE];
	  while(fgets(buf,TAILLE,file)!=NULL){
	  	if(buf[0]!='#'){

	  		Edge edge; 
		    int a,b;
		    sscanf(buf,"%d %d\n",&a,&b);
		    edge.p1 = a;
		    edge.p2 = b;
		    list_edges[i]=edge;
		    i++;
		}
  	}
  return list_edges;

}

void generate_matrix(const char* filename,int n, int matrix[n][n]){

  FILE* file = fopen(filename,"r");

    int i = 0;
    char buf[TAILLE];
    while(fgets(buf,TAILLE,file)!=NULL){
      if(buf[0]!='#'){

        
        int a,b;
        sscanf(buf,"%d %d\n",&a,&b);
        matrix[a][b]=1;
        matrix[b][a]=1; 
      }
    }

}
int main(){
  static const char filename[] = "graphs_cleaned/email-Eu-core.txt";
  /*As a list of edges*/
  int nbLiens = getNbEdges(filename);
  printf("nbLiens = %d\n", nbLiens);
  Edge *list_edges = getListEdges(filename,nbLiens);
  
  int i;
 
   /*As an adjacency array*/
  int nbNodes = getNbNodes(filename);
  int *tab_degree = get_tab_degree(filename,nbNodes);

  Adjarray adjarray = get_tab_adjacent(filename,nbNodes,nbLiens,tab_degree);

  printf("%d\n",adjarray.n );
  printf("%d\n",adjarray.m );

  // for(i=0;i<nbNodes;i++){
  //   printf("%d\n", adjarray.cd[i] );
  // }
  // int somme_degree = get_somme_degree(tab_degree,nbNodes);
 //  for (i = 0; i < somme_degree; ++i)
 //  {
 // printf("%d\n", adjarray.adj[i] );  }
 

  /* As a adjacency matrix */
  int matrix_adjacent[nbNodes][nbNodes]; 
  printf("before :\n");
  for (int i = 0; i < nbNodes; ++i)
  {
    for (int j = 0; j < nbNodes; ++j)
    {
      matrix_adjacent[i][j] = 0;
      
    }
  }
  int nb = 0;
  generate_matrix(filename,nbNodes, matrix_adjacent);
  for (int i = 0; i < nbNodes; ++i)
  {
    for (int j = 0; j < nbNodes; ++j)
    {
      // printf("%d ",matrix_adjacent[i][j] );
      if(matrix_adjacent[i][j]==1){
        nb++;
      }
    }
  }

  printf("nb = %d\n", nb );


 
 return 0;
}