
all: ter

ter: main.c Graphe.o TSP.o Partition.o Vecteur.o LRI.o
	gcc -g -o ter main.c Graphe.o TSP.o LRI.o Partition.o Vecteur.o -lm

Graphe.o: Graphe.c
	gcc -o Graphe.o -c Graphe.c -W -Wall 

TSP.o: TSP.c
	gcc -o TSP.o -c TSP.c -W -Wall

Partition.o: Partition.c
	gcc -o Partition.o -c Partition.c -W -Wall

Vecteur.o : Vecteur.c 
	gcc -o Vecteur.o -c Vecteur.c -W -Wall
	
LRI.o : LRI.c
	gcc -o LRI.o -c LRI.c -W -Wall
	
Draw :
	R CMD BATCH "Draw.R"

clean:
	rm -rf *.o
	
mrproper: clean
	rm -rf ter
	rm -rf .RData
	rm -rf *.Rout
	rm -rf *.data
