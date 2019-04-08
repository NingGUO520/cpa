
#ifndef H_FILE
#define H_FILE

typedef struct Element Element;
struct Element
{
	int node;
	Element *suivant;
};

typedef struct File File;
struct File
{
	Element* premier;
	
};

File * file_init();
void enfiler(File* file, int node);
int defiler(File*file);


#endif