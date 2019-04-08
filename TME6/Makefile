all: exo3 exo2 exo1 clean


exo3:graphe.o  exo3.c
	gcc -o exo3 graphe.o  exo3.c

exo2:graphe.o  exo2.c
	gcc -o exo2 graphe.o  exo2.c

exo1:graphe.o  exo1.c
	gcc -o exo1 graphe.o  exo1.c

graphe.o: graphe.c graphe.h
	gcc  -Wall -c graphe.c -o graphe.o

clean:
	rm -f *.o
