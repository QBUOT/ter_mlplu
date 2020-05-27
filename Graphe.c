#include "Graphe.h"

Graphe init_Graphe(int T)
{
	int i;
	Graphe G;
	G.N = T;
	
	G.Dist = calloc(T , sizeof(int*));
	
	for (i = 0; i < T ; i++)
	{
		//Matrice triangulaire
		//G.Dist[i] = calloc(T-i , sizeof(int));
		
		//Matrice pleine
		G.Dist[i] = calloc(T , sizeof(int));
	}
	return G;
}

void ponderer_Graphe(Graphe* G)
{
	//Initialisation de la seed pour la ponderation
	unsigned int seed = getpid() + time(NULL);
	srandom(seed);
	int i,j;
	
	for (i = 0; i < (G->N)-1; i++)
	{
		for (j = i; j < G->N; j++)
		{
			if (i != j)
			{
				G->Dist[i][j] = (((int)random()%DIST_MAX+1) + DIST_MAX);
				//Matrice Pleine
				G->Dist[j][i] = G->Dist[i][j];
			}
			

		}
	}
}

void ponderer_Graphe_Euclide(Graphe* G)
{
	unsigned int seed = getpid() + time(NULL);
	srand(seed);
	int i,j;
	int p1,p2;
	int index[G->N][2];
	int plan[TAILLE_PLAN][TAILLE_PLAN];
	
	for (i = 0; i < TAILLE_PLAN; i++)
	{
		for (j = 0; j < TAILLE_PLAN; j++)
		{
			plan[i][j] = 0;
		}
		
	}
	
	for (i = 0; i < G->N; i++)
	{
		do
		{
			p1 = (int)(rand()%TAILLE_PLAN);
			p2 = (int)(rand()%TAILLE_PLAN);
		} while (plan[p1][p2] != 0);
		plan[p1][p2] = 1;
		index[i][0] = p1;
		index[i][1] = p2;
	}
	

	for (i = 0; i < (G->N); i++)
	{
		for (j = 0; j < G->N; j++)
		{
			if (i != j)
			{
				//Calcul distance euclidienne
				G->Dist[i][j] = (int)(sqrt((double)(pow(index[i][0] - index[j][0],2) + pow(index[i][1] - index[j][2],2))));
				G->Dist[j][i] = G->Dist[i][j];
			}
			

		}
	}
	
	
	
	
	
	
	
}

void ecrire_Graphe(Graphe* G, char* fichier)
{
	int i,j;
	FILE* file = NULL;
	file = fopen(fichier, "w");
	
	fprintf(file,"%d\n",G->N);
	
	for (i = 0; i < G->N; i++)
	{
		for (j = 0; j < G->N; j++)
		{
			fprintf(file,"%d	",G->Dist[i][j]);
		}
		fprintf(file,"\n");
	}
	fclose(file);
}

Graphe lire_Graphe(char* fichier)
{
	int i,j,taille;
	FILE* file = NULL;
	file = fopen(fichier, "r");
	fscanf(file,"%d\n",&taille);
	Graphe G = init_Graphe(taille);
	for (i = 0; i < taille; i++)
	{
		for (j = 0; j < taille; j++)
		{
			fscanf(file, "%d	",&G.Dist[i][j]);
		}
		fscanf(file,"\n");
	}
	return G;
}

void free_graphe(Graphe* G)
{
	int i;
	for (i = 0; i < G->N; i++)
	{
		free(G->Dist[i]);
	}
	free(G->Dist);
}
