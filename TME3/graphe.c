#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"
#define TAILLE 256

int getNbNodes(const char* filename){

  int max = get_max_node(filename);
  char* tab = malloc((max+1)*sizeof(int));

  FILE* file = fopen(filename,"r");
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#'){
      int a,b;
      sscanf(buf,"%d %d\n",&a,&b);
      tab[a]=1;
      tab[b]=1;  
    }
  }

  int nbNodes = 0;
  for (int i = 0; i < max+1; ++i)
  {
    if(tab[i]==1){
      nbNodes++;
    }
  }
  return nbNodes;
}


int get_max_node(const char* filename){
  FILE* file = fopen(filename,"r");

  int max = 0;
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#'){
    int a,b;
    sscanf(buf,"%d %d\n",&a,&b);
    if(a>max) max = a;
    if(b>max) max = b;
    }
  }
 
  return max;
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
    if(buf[0]!='#'){
    int a,b;
    sscanf(buf,"%d %d\n",&a,&b);
    tab_degrees[a]++;
    tab_degrees[b]++;  
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

Adjarray get_tab_adjacent(const char* filename, int nbNodes, int nb_edges,int *tab_degree){
  int somme_degree = get_somme_degree(tab_degree,nbNodes);
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
  
  int acc = 0;
  for(i = 0 ;i < nbNodes;i++){
    acc = acc + tab_degree[i];
    cd[i+1] = acc;
  }

  FILE* file = fopen(filename,"r");
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#'){
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
  }
  adjarray.cd  = cd;
  adjarray.adj = adj;

  return adjarray;
}

void generate_matrix(const char* filename,int n, int matrix[n][n]){

  FILE* file = fopen(filename,"r");

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