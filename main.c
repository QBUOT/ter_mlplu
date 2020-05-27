#include "TSP.h"
#include "LRI.h"

#define T 500 //Nombre de sommets
#define k 20 //Nombre de véhicules
#define NBITERATION 200000 //Nombre d'itérations à faire
#define B 0.01 

int main(int argc, char **argv)
{

	int eco_min = 0;
	int eco_max = 0;
	
	FILE *sortieR = fopen("sortieR.data","w");

	srand(getpid()+time(NULL));
	
	Graphe G = init_Graphe(T);
	ponderer_Graphe_Euclide(&G);
	//Graphe G = lire_Graphe("graphegen");
	Vecteur vecttab[T];
	ecrire_Graphe(&G,"graphegen");
	
	for (int i = 0; i < T; i++)
	{
		vecttab[i] = init_vecteur(k);
	}
	
	for (int i = 0; i < NBITERATION; i++)
	{
		Partition **P = malloc(k*sizeof(Partition));
		for (int j = 0; j < k; j++) 
		{
			P[j] = init_partition();
		}
		partitionner(P,vecttab,T,k);
		
		Tournee **tour = malloc(k*sizeof(Tournee));

		int eco = 0;
		for (int j = 0; j < k; j++)
		{
			tour[j] = init_tournee();
			tour[j] = TSP_PPV(P[j],G);
			
			//La fonction economique est la somme de la taille de toute les tournées
			eco += tour[j]->valeur;
			//printf("Itération %d  : Tournée %d Taille %d : %d \n",i+1,j+1,tour[j]->taille,tour[j]->valeur);
		}
		
		//Modification des min et max de la fonction economique
		if (eco_min == 0)
		{
			if (eco_max < eco)
			{
				eco_min = eco_max;
				eco_max = eco;
			}
			if (eco_max > eco)
			{
				eco_min = eco;
			}
		
		}
		else
		{
			if (eco > eco_max)
			{
				eco_max = eco;
			}
			if (eco < eco_min)
			{
				eco_min = eco;
				FILE * meilleure = fopen("meilleure_tournée","w");
				fprintf(meilleure,"La meilleure valeur de tournée est : %d \n",eco);
				for (int i = 0; i < k; i++)
				{
					afficher_tournee(tour[i],meilleure);
				
				}
				fclose(meilleure);
			}
			
		}
		
		for (int j = 0; j < k; j++)
		{
			Sommet* tmp = NULL;
			tmp = tour[j]->Lsommet; //pointeur vers tête de liste

			for (int i = 0; i < tour[j]->taille; i++)
			{
				vecttab[tmp->numS] = modif_vecteur(vecttab[(tmp->numS)],j,LRI_util(eco,eco_min,eco_max),B);
				//printf("Test = %lf \n",vecttab[tmp->numS].vec[j]);
				tmp = tmp->suiv;
			}
			
			free(tmp);			
		}
		
		//printf("min = %d max = %d courant = %d \n",eco_min,eco_max,eco);
		fprintf(sortieR,"%d	%d\n",i,eco);		
		
		if (i == NBITERATION -1)
		{
			FILE * derniere = fopen("derniere_tournée","w");
			fprintf(derniere,"La derniere valeur de tournée est : %d \n",eco);
			for (int i = 0; i < k; i++)
			{
				afficher_tournee(tour[i],derniere);
				
			}
			fclose(derniere);
		}
		
		
		
		//Destruction des partitions et tournées
		for (int j = 0; j < k; j++)
		{
			detruire_partition(P[j]);
			detruire_tournee(tour[j]);
		}
		for (int j = 0; j < k; j++)
		{
			free(P[j]);
			free(tour[j]);
		}
		free(P);
		free(tour);
		

		
	}
		
	//Destruction des vecteurs et du graphe
	for (int j = 0; j < T; j++)
	{
		free(vecttab[j].vec);
	}	
	free_graphe(&G);
	
	fclose(sortieR);
	
	return 0;
}

