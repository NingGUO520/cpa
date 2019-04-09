#include<stdlib.h>
#include <stdio.h>
#include "graphe.h"

#define TAILLE 256

int* get_table_out_degree(const char* filename,int size, int* tab_renommage){
  int* tabOutDegree = malloc(size*sizeof(int));
  

  FILE* file = fopen(filename,"r");

  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#'){
      int a,b;
      sscanf(buf,"%d %d\n",&a,&b);
      int i_a = tab_renommage[a];
      tabOutDegree[i_a]++;
      
    }
  }

  return tabOutDegree;

}

void remplirTab(const char* filename,int* tab){

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
}

int get_number_node(int * tab,int n){
  int nb=0;
  for (int i = 0; i < n; ++i)
  {
   if(tab[i]==1){
    nb++;
   }
  }
  return nb;
}


float* generate_P(const char* filename, float* p0,int *tabOutDegree,int nb_nodes , int* tab_renommage,double alpha ){

  float * p = malloc(nb_nodes*sizeof(float));
  //initialiser p[i]=0 pour tout i
  for (int i = 0; i < nb_nodes; ++i)
  {
    p[i]=0;
  }

  //lire tous les liens
  FILE* file = fopen(filename,"r");
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
     if(buf[0]!='#'){
      int a,b;
      sscanf(buf,"%d %d\n",&a,&b);
      int i_a = tab_renommage[a];
      int i_b = tab_renommage[b];
      p[i_b]= p[i_b]+p0[i_a]/tabOutDegree[i_a];
   
   }
  }

  for (int i = 0; i < nb_nodes; ++i)
  {
    p[i] = (1-alpha)*p[i] + alpha/nb_nodes;

  }

  // normalizer P
  float somme = 0;
  for (int i = 0; i < nb_nodes; ++i)
  {
    somme+=p[i];
  }

  for (int i = 0; i < nb_nodes; ++i)
  {
     p[i] = p[i]+ (1-somme)/nb_nodes;
  }

  return p;
}
float* pageRank(const char* filename,int nb_nodes,int *tabOutDegree ,int* tab_renommage, float alpha){
  // Initialiser P0
  float* p = malloc(nb_nodes*sizeof(float));
  for (int i = 0; i < nb_nodes; ++i)
  {
    p[i]=(float)1/nb_nodes;
  }

  for (int i = 0; i < 1; ++i)
  {
    p = generate_P(filename,p,tabOutDegree,nb_nodes,tab_renommage,alpha);
  }

  return p;
}



int main(){


  // static const char filename[] = "data/exemple.txt";
  static const char filename[] = "data/alr21--dirLinks--enwiki-20071018.txt";
  int size = get_max_node(filename)+1;


  
  int* tab_renommage = get_tab_renommage(filename,size);
 
  
  // int *tabOutDegree = get_table_out_degree(filename,nb_nodes,tab_renommage);
  // float* p = pageRank(filename,nb_nodes,tabOutDegree ,tab_renommage, 0.15);
  
  
  
  return 0;


}