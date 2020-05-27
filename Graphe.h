#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define DIST_MAX 10000 //Distance maximale et minimale entre deux noeuds
#define TAILLE_PLAN 1000 //Défini la largeur/hauteur du plan pour la génération avec distances euclidiennes

//Graphe complet pondere represente par une matrice d'adjacence
struct graphe 
{
	int N; //Nombre de sommets du graphe
	int** Dist; //Matrice contenant les distances entre deux sommets
};

typedef struct graphe Graphe;

//Initialise un graphe de taille "T"
Graphe init_Graphe(int T);

//Remplit la matrice "Dist" de valeurs aleatoires
void ponderer_Graphe(Graphe* G);

void ponderer_Graphe_Euclide(Graphe* G);

//Stocke le graphe G dans un fichier (Format dans la documentation)
void ecrire_Graphe(Graphe* G, char* fichier);

//Stocke dans G le graphe contenu dans le fichier
Graphe lire_Graphe(char* fichier);

//Desalloue un graphe
void free_graphe(Graphe* G);
