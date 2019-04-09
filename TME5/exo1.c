#include<stdlib.h>
#include <stdio.h>
#include "graphe.h"

#define TAILLE 256


int  get_highest_PageRank(float* p,int nbNodes){

  float max = p[0];
  int max_i = 0;
  for (int i = 1; i < nbNodes; ++i)
  {
    if(p[i]>max){
      max = p[i];
      max_i = i;
    }
  }

  return max_i;
}
int* get_table_out_degree_renommee(const char* filename,int nb_nodes, int* tab_renommage){

  int* tabOutDegree = malloc(nb_nodes*sizeof(int));
  FILE* file = fopen(filename,"r");

  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#' && buf[0]!='\n'){
      int a,b;
      sscanf(buf,"%d %d\n",&a,&b);
      int i_a = tab_renommage[a];
      tabOutDegree[i_a]++;
      
    }
  }

  return tabOutDegree;

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
    if(buf[0]!='#' && buf[0]!='\n'){
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

  printf("fin de generer P0\n");

  for (int i = 0; i < 1; ++i)
  {
    p = generate_P(filename,p,tabOutDegree,nb_nodes,tab_renommage,alpha);
  }

  return p;
}



int main(){


  // static const char filename[] = "data/exemple.txt";
  static const char filename[] = "data/alr21--dirLinks--enwiki-20071018.txt";
  int max_node = get_max_node(filename); 
  printf("max_node = %d\n",max_node );


  // get le nombre de nodes 
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
  printf("nbNodes = %d\n",nbNodes );

  //get the table renommee
  int* tab_renomme = get_tab_renomme(filename,nbNodes);

  //get the table de rennommage
  int * tab_renommage = malloc((max_node+1)*sizeof(int));
  int j = 0;
  for (int i = 0; i < max_node+1; ++i)
  {
    if(tab[i]==1){
      tab_renommage[i]=j;
      j++;
   
    }
  }

  printf("fin de charger tab_renommage\n");
  
  int *tabOutDegree = get_table_out_degree_renommee(filename,nbNodes,tab_renommage);

  printf("fin de charger tabOutDegree\n");
  float* p = pageRank(filename,nbNodes,tabOutDegree ,tab_renommage, 0.15);

  for (int i = 0; i < 10; ++i)
  {
    printf("%f ",p[i] );
  }
  printf("\n");
  
  int highest_id =   get_highest_PageRank(p,nbNodes);
  int id = tab_renomme[highest_id];
  printf("id = %d\n",id );


  
  return 0;


}