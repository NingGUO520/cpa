#include <stdlib.h>
#include <stdio.h>
#include "file.h"


File* file_init(){
	File * file = malloc(sizeof(*file));
	file->premier = NULL;
	return file;
}
void enfiler(File*file, int node){
	Element* nouveau = malloc(sizeof(*nouveau));
	nouveau->node = node;
	nouveau->suivant = NULL;

	/*la file n'est pas vide*/
	if(file->premier != NULL){
		Element* ele = file->premier;
		while(ele->suivant !=NULL){
			ele = ele->suivant;
		}
		ele->suivant = nouveau;

	}else{ /*la file est vide*/
		
		file->premier = nouveau;
	}

}



int defiler(File*file ){

	// pre-condition: la file n'est pas vide

	if(file->premier == NULL){
		exit(-1);
	}

	Element* ele = file->premier;
	int res = ele->node;

	file->premier = ele->suivant;
	free(ele);
	return res;
}