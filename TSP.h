#include "Partition.h"


//Renvoie l'indice du sommet non marqué le plus proche du sommet courant dans min et la partition marquée

void plus_proche_voisin(int v , Graphe G, Partition *P, int *min,  Sommet * Smin);

//Renvoie la tournée TSP crée par l'algorithme du plus proche voisin

Tournee *TSP_PPV(Partition *P, Graphe G);

//TODO Ajouter nouvelle heuristique
