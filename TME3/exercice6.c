#include<stdlib.h>
#include <stdio.h>
#define TAILLE 256

int getMaxDegree(const char* filename){

  FILE* file = fopen(filename,"r");
  char buf[TAILLE];
  int degree_max = 0;
  while(fgets(buf,TAILLE,file)!=NULL){
    int node,degree;
    sscanf(buf,"%d %d\n",&node,&degree);
    if(degree > degree_max){
      degree_max = degree;
    }

  }
return degree_max;
}

int main(){

  static const char filename[] = "result_exo4.txt";
 
  int degree_max = getMaxDegree(filename);

  printf("the max degree is %d\n",degree_max);

  int * tab_degree = malloc( (degree_max+1) * sizeof(int));

  FILE* file = fopen(filename,"r");
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    int node,degree;
    if(buf[0]!='#'){
      sscanf(buf,"%d %d\n",&node,&degree);

      tab_degree[degree]++;
    }
   
  }
 

  /*write degree distribution in a file*/

  int i;
  FILE * fichier = NULL;
  fichier = fopen("result_exo6.txt","w");
  if(fichier!=NULL){

    fprintf(fichier,"# d   n\n");
    for(i=0;i<degree_max+1;i++){


      if(tab_degree[i]!=0){

        fprintf(fichier,"%d    %d\n",i,tab_degree[i]);

      }
    }

  }


  free(tab_degree);
  return 0;


 
}
