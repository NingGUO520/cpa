#include<stdlib.h>
#include <stdio.h>
#include "graphe.h"

#define TAILLE 256
void tri_insertion2(double tableau[],int longueur)
     {

     	 printf("before :\n");
  for (int i = 0; i < longueur; ++i)
  {
    printf("%f ",tableau[i] );
  }
     int i, memory, compt, marqueur;

     for(i=1;i<longueur;i++)
        {
        memory=tableau[i];
        compt=i-1;

        do
            {
            marqueur=false;
            if (tableau[compt]>memory)
                {
                tableau[compt+1]=tableau[compt];
                compt--;
                marqueur=true;
                }
            if (compt<0) marqueur=false;
            }
        while(marqueur);
        tableau[compt+1]=memory;
        }



  printf("after :\n");
  for (int i = 0; i < longueur; ++i)
  {
    printf("%f ",tableau[i] );
  }
     }

int* tri_insertion(double* tab , int size){


  for (int i = 0; i < size; ++i)
  {
    printf("%f ",tab[i] );
  }

  int* tab_order = malloc(size*sizeof(int));
  for (int i = 0; i < size; ++i)
  {
    tab_order[i]=i;
  }

  int i,j;
  double elem ;
  for (int i = 1; i < size; ++i)
  {
   
      elem = tab[i];
      for (j = i; j>0 && tab[j-1]>elem ;j--)
      {
        tab[j] = tab[j-1];
        // tab_order[j]=tab_order[j-1];


      }
      tab[j]=elem;
      // tab_order[j]=i;
  }


  printf("after :\n");
  for (int i = 0; i < size; ++i)
  {
    printf("%f ",tab[i] );
  }

  return tab_order;
}

int main(int argc, char const *argv[])
{
	

	double t[5]= {1,1,1,0.5,0.5};
	tri_insertion(t,5);

	return 0;
}