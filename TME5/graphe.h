
#ifndef H_GRAPHE
#define H_GRAPHE

typedef enum { false, true } bool;


typedef struct
{
	int p1;
	int p2;
}Edge;

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
int* get_tab_renommage(const char* filename,int max_node);
int* get_tab_renomme(const char* filename, int nbNodes);
int* get_tab_degree(const char* filename, int taille);
int get_somme_degree(int *tab_degree, int size);
int* get_tab_degree_renomme(int * tab_degrees, int nbNodes, int size);
Adjarray get_tab_adjacent(int max_node,const char* filename, int nbNodes, int nb_edges,int *tab_degree, int* tab_renommage,int* tab_renomme);
void generate_matrix(const char* filename,int n, int matrix[n][n]);
Edge* getListEdges(const char* filename, int n);
#endif
