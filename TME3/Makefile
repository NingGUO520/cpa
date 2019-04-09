
all: exo2 exo4 exo5 exo7 exo8 exo9 clean

exo2: graphe.o exercice2.c
	gcc -Wall -o exo2 graphe.o exercice2.c

exo4: graphe.o exercice4.c
	gcc -Wall -o exo4 graphe.o exercice4.c
	
exo5: graphe.o exercice5.c
	gcc -Wall -o exo5  graphe.o exercice5.c

exo7: graphe.o exercice7.c
	gcc -Wall -o exo7  graphe.o exercice7.c

exo8: file.o graphe.o exercice8.c 
	gcc -Wall -o exo8 file.o graphe.o exercice8.c

exo9: file.o graphe.o exercice9.c 
	gcc -Wall -o exo9 file.o graphe.o exercice9.c


file.o : file.c file.h
	gcc  -Wall -c file.c -o file.o

graphe.o: graphe.c graphe.h
	gcc  -Wall -c graphe.c -o graphe.o

clean:
	rm -f *.o