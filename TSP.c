#include "TSP.h"


Tournee *TSP_PPV(Partition *P, Graphe G)
{
	Tournee *tour = init_tournee();
	
	Sommet *tmp = P->Lsommet; //Pointeur vers la tête de liste
	Sommet *Smin = P->Lsommet; //Pointeur vers le sommet du min
	
	int somme = 0; //Stocke la somme des distances entre chaque sommet de la tournée
	int j;
	int lastsom = 0; //Dernier sommet inséré
	int min = 0;
	
	for (j = 1; j < P->taille; j++)
	{
		
		//Recherche du Plus Proche Voisin
		while(tmp != NULL)
		{
			//Marquage du dernier sommet inséré
			if (tmp->numS == lastsom)
			{
				tmp->marq = 1;
			}
			
			//Recherche de la plus faible distance entre le dernier sommet inséré et un sommet non marqué
			if ((G.Dist[lastsom][tmp->numS] != 0) && (tmp->marq == 0) && tmp->numS != 0)
			{
				if (min == 0 || G.Dist[lastsom][tmp->numS] < min)
				{
					min = G.Dist[lastsom][tmp->numS];
					Smin = tmp;
				}
			
			}
			tmp = tmp->suiv;
		}
		
		//Insertion du PPV dans la tournée
		tmp = P->Lsommet;
		somme = somme + min;
		lastsom = Smin->numS;
		insertion_tournee(tour,Smin->numS);
		min = 0;
		
	}
	//Maj de la valeur de la tournée Cad somme des distances entre chaque sommet de la tournée
	tour->valeur = somme;
	return tour;
}
