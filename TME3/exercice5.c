#include<stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include "graphe.h"
#define TAILLE 256
#define EMAIL "graphs_cleaned/email-Eu-core.txt"
#define AMAZON "graphs_cleaned/com-amazon.ungraph.txt"
#define LJ "graphs_cleaned/com-lj.ungraph.txt"


void calculQuantity(const char* filename, int size){

  int* tab_degrees = get_tab_degree(filename,size);
  FILE* file = fopen(filename,"r");

  uint64_t quantity = 0;
  char buf[TAILLE];
  while(fgets(buf,TAILLE,file)!=NULL){
    if(buf[0]!='#'){
    int a,b;
    sscanf(buf,"%d %d\n",&a,&b);
    quantity+=tab_degrees[a]*tab_degrees[b];
    }
  }

  printf("the quantity is = %ld \n",quantity);


}

void exercice5(const char* filename){

  float temps;
  clock_t t1, t2;
 
  int size = get_max_node(filename)+1;
  t1 = clock();
  calculQuantity(filename,size);
  t2 = clock();

  temps = (float)(t2-t1)/CLOCKS_PER_SEC*1000;
  printf("temps = %f ms \n", temps);
}
int main(){

 
  exercice5(AMAZON);
  
  return 0;


}
