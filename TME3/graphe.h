
#ifndef H_GRAPHE
#define H_GRAPHE

typedef enum { false, true } bool;

typedef struct 
{ 
  unsigned n; // number of nodes
  unsigned m; //number of edges
  unsigned *cd;
  unsigned *adj;
  
}Adjarray;

int getNbNodes(const char* filename);
int getNbEdges(const char* filename);
int get_max_node(const char* filename);
int* get_tab_degree(const char* filename, int taille);
int get_somme_degree(int *tab_degree, int size);
Adjarray get_tab_adjacent(const char* filename, int nbNodes, int nb_edges,int *tab_degree);
void generate_matrix(const char* filename,int n, int matrix[n][n]);
#endif
