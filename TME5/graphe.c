#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"
#define TAILLE 256

int getNbNodes(const char* filename, int max_node){
  int* tab = malloc((max_node+1)*sizeof(int));
  FILE* file = fopen(filename,"r");
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#' && buf[0]!='\n'){
      int a,b;
      sscanf(buf,"%d %d\n",&a,&b);
      tab[a]=1;
      tab[b]=1;  
    }
  }

  int nbNodes = 0;
  for (int i = 0; i < max_node+1; ++i)
  {
    if(tab[i]==1){
      nbNodes++;
    }
  }
  return nbNodes;

}

int* get_tab_renomme(const char* filename, int nbNodes){

  int max = get_max_node(filename);
  int* tab = malloc((max+1)*sizeof(int));

  FILE* file = fopen(filename,"r");
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#' && buf[0]!='\n'){
      int a,b;
      sscanf(buf,"%d %d\n",&a,&b);
      tab[a]=1;
      tab[b]=1;  
    }
  }

  int* tab_renomme = malloc(nbNodes*sizeof(int));
  int j=0;
  for (int i = 0; i < max+1; ++i)
  {
    if(tab[i]==1){
      tab_renomme[j]=i;
      j++;
    }
  }

  return tab_renomme;

}

int get_max_node(const char* filename){
  FILE* file = fopen(filename,"r");

  int max = 0;
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#' && buf[0]!='\n'){
    int a,b;
    sscanf(buf,"%d %d\n",&a,&b);
    if(a>max) max = a;
    if(b>max) max = b;
    }
  }
 
  return max;
}

int* get_tab_renommage(const char* filename,int max_node){

  int* tab = malloc((max_node+1)*sizeof(int));

  FILE* file = fopen(filename,"r");
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#' && buf[0]!='\n'){
      int a,b;
      sscanf(buf,"%d %d\n",&a,&b);
      tab[a]=1;
      tab[b]=1;  
    }
  }


  int * tab_renommage = malloc((max_node+1)*sizeof(int));
  int j = 0;
  for (int i = 0; i < max_node+1; ++i)
  {
    if(tab[i]==1){
      tab_renommage[i]=j;
      j++;
   
    }
  }

  return tab_renommage;
}


int getNbEdges(const char* filename){
	FILE* file = fopen(filename,"r");

	  int nbLiens = 0;
	  char buf[TAILLE];
	  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#' && buf[0]!='\n'){
	    int a,b;
	    sscanf(buf,"%d %d\n",&a,&b);	 
	    nbLiens++;
	    }
	  }

  return nbLiens;
}
int* get_tab_degree_renomme(int * tab_degrees, int nbNodes, int max_node, int* tab_renomme){
  int* tab_degree_renomme = malloc(nbNodes*sizeof(int));
 

  for (int i = 0; i < nbNodes; ++i)
  {
    int node = tab_renomme[i];
    tab_degree_renomme[i] = tab_degrees[node];
  }
  return tab_degree_renomme;
}

int* get_tab_degree(const char* filename, int size){

  FILE* file = fopen(filename,"r");
  int * tab_degrees = malloc(size * sizeof(int));

  for (int i = 0; i < size; ++i)
  {
    tab_degrees[i]=0;
  }
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#' && buf[0]!='\n'){
      int a,b;
      sscanf(buf,"%d %d\n",&a,&b);
      if(a!=b){
        tab_degrees[a]++;
        tab_degrees[b]++;
      }  
    }  
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

Adjarray get_tab_adjacent(const char* filename, int nbNodes, int nb_edges,int *tab_degree_renomme, int* tab_renommage){
  int somme_degree = get_somme_degree(tab_degree_renomme,nbNodes);
  Adjarray adjarray;
  adjarray.n = nbNodes;
  adjarray.m = nb_edges;
  unsigned * adj = malloc(somme_degree * sizeof(int));
  unsigned * cd = malloc((nbNodes+1)* sizeof(int));
  int i;

  for(i=0;i<somme_degree;i++){
    adj[i]=-1;
  }


  cd[0] = 0;
  
  // remplir le tableau cd
  int acc = 0;
  for(i = 0 ;i < nbNodes;i++){
   
    acc = acc + tab_degree_renomme[i];
    cd[i+1] = acc;
  }


  //remplir le tableau adj
  FILE* file = fopen(filename,"r");
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#' && buf[0]!='\n'){
      int a,b;
      sscanf(buf,"%d %d\n",&a,&b);
     
      if(a!=b){
        int offset = 0;
        int i_a = tab_renommage[a];
        int index = cd[i_a];
        while(adj[index+offset]!=-1){
          
          offset++;
        }
       
        adj[index+offset] = b;
        offset = 0;
        int i_b = tab_renommage[b];
        index = cd[i_b];
        while(adj[index+offset]!=-1){
          offset++;
        }
       
        adj[index+offset] = a;
      }
    }
  }
  adjarray.cd  = cd;
  adjarray.adj = adj;

  return adjarray;
}

void generate_matrix(const char* filename,int n, int matrix[n][n]){

  FILE* file = fopen(filename,"r");

    char buf[TAILLE];
    while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#' && buf[0]!='\n'){

        int a,b;
        sscanf(buf,"%d %d\n",&a,&b);
        matrix[a][b]=1;
        matrix[b][a]=1; 
      }
    }

}
Edge* getListEdges(const char* filename, int n){
  Edge* list_edges = malloc(n*sizeof(Edge)) ;
  FILE* file = fopen(filename,"r");

    int i = 0;
    char buf[TAILLE];
    while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#' && buf[0]!='\n'){

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