#include "stdlib.h"
#include <stdio.h>

typedef struct Vecteur Vecteur;
struct Vecteur
{
	int taille;
	double* vec;
};

//Initialise un vecteur de taille k avec toutes ses composantes à 1/k
Vecteur init_vecteur(int k);

Vecteur modif_vecteur(Vecteur v, int nmcompo, double modif, double B);

//Normalise un vecteur 
Vecteur norme(Vecteur V);// TODO
