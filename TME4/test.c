#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#define TAILLE 256
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

int main(){
	char filename1[] = "data/com-youtube.ungraph.txt";
		char filename2[] = "graphs_cleaned/com-youtube.ungraph.txt";

	int nb_liens = getNbEdges(filename1);
		int nb_liens2 = getNbEdges(filename2);

	printf("nb_liens = %d\n",nb_liens );
	printf("nb_liens2 = %d\n",nb_liens2 );
}