#include "TSP.h"
#include "LRI.h"

#define T 20 //Nombre de sommets
#define k 3 //Nombre de véhicules
#define NBITERATION 200000//Nombre d'itérations à faire
#define B 0.01 //Paramètre de ralentissement

int main(int argc, char **argv)
{
	//Pour min et max global
	int eco_min = 0;
	int eco_max = 0;
	
	//Pour min et max individuel
	int eco_min_S[T];
	int eco_max_S[T];
	int affectation_S[T];
	
	for (int i = 0; i < T; i++)
	{
		eco_min_S[i] = 0;
		eco_max_S[i] = 0;
		affectation_S[i] = 0;
	}
	
	
	FILE *sortieR = fopen("sortieR.data","w");

	//srand(getpid()+time(NULL));
	srand(50254645);
	
	//Graphe G = init_Graphe(T);
	//ponderer_Graphe_Euclide(&G);
	Graphe G = lire_Graphe("graphegen");
	Vecteur vecttab[T];
	//ecrire_Graphe(&G,"graphegen");
	
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
		}
		
		//#############################################
		//Pour calcul de l'utilité sur le système
		
		//~ //Modification des min et max de la fonction economique
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
		
		//~ //Modification des vecteurs pour les mins et maxs globaux
		
		for (int j = 0; j < k; j++)
		{
			Sommet* tmp = NULL;
			tmp = tour[j]->Lsommet; //pointeur vers tête de liste

			for (int i = 0; i < tour[j]->taille; i++)
			{
				vecttab[tmp->numS] = modif_vecteur(vecttab[(tmp->numS)],j,LRI_util(eco,eco_min,eco_max),B);
				tmp = tmp->suiv;
			}
			
			free(tmp);			
		}
		
		//Debut A commenter si on utilise l'utilité globale
		//######################################################
				
		//~ //On stocke l'affectation de chaque sommet à un véhicule pour chaque tournée
		//~ for (int i = 0; i < k ; i++)
		//~ {
			//~ Sommet* tmp = NULL;
			//~ tmp = tour[i]->Lsommet;
			//~ while (tmp != NULL)
			//~ {
				//~ affectation_S[tmp->numS] = i;
				//~ tmp = tmp->suiv;
			//~ }
		//~ }
		
		//~ //Modification des mins et max de chaque sommet
			//~ for (int i = 0; i < T; i++)
			//~ {
				//~ if (eco_min_S[i] == 0)
				//~ {
				//~ if (eco_max_S[i] < tour[affectation_S[i]]->valeur)
				//~ {
					//~ eco_min_S[i] = eco_max_S[i];
					//~ eco_max_S[i] = tour[affectation_S[i]]->valeur;
				//~ }
				//~ if (eco_max_S[i] > tour[affectation_S[i]]->valeur)
				//~ {
					//~ eco_min_S[i] = tour[affectation_S[i]]->valeur;
				//~ }
				//~ }
				//~ else
				//~ {
					//~ if (eco > eco_max_S[i])
					//~ {
						//~ eco_max_S[i] = tour[affectation_S[i]]->valeur;
					//~ }
					//~ if (eco < eco_min_S[i])
					//~ {
						//~ eco_min_S[i] = tour[affectation_S[i]]->valeur;
					//~ }	
				//~ }
			//~ }
		
		//~ //Modification des probas pour le calcul individuel
		//~ if (i > 10000) //On attend un certain nombre d'itération pour que les mins et max soit fixés sur tout les sommets
		//~ {
			//~ for (int j = 1; j < T; j++)
			//~ {
			//~ vecttab[j] = modif_vecteur(vecttab[j],affectation_S[j],LRI_util(tour[affectation_S[j]]->valeur,eco_min_S[j],eco_max_S[j]),B);
			//~ }
		//~ }
		
		//######################################################
		//Fin a commenter si on utilise l'utilité globale
		
		if ( i%500 == 0)
		{
			fprintf(sortieR,"%d	%d\n",i,eco);
		}
		
				
		
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

