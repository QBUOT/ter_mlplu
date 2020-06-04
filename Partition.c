#include "Partition.h"

Partition* init_partition()
{
	Partition *p = malloc(sizeof(Partition));
	
	Sommet *s = malloc(sizeof(Sommet));
	
	if (p == NULL || s == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    s->suiv = NULL;
    s->numS = 0;
    s->marq = 0;
    
    p->taille = 1;
    p->Lsommet =s;
	
	return p;
}

Tournee* init_tournee()
{
	Tournee *t = malloc(sizeof(Tournee));
	
	Sommet *s = malloc(sizeof(Sommet));
	
	if (t == NULL || s == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    s->suiv = NULL;
    s->numS = 0;
    s->marq = 0;
    
    t->valeur = 0;
    t->taille = 1;
    t->Lsommet =s;
	
	return t;
}

void insertion_partition(Partition *part, int nvSommet)
{
	Sommet *s = malloc(sizeof(Sommet));
	
	if (part == NULL || s == NULL)
    {
        exit(EXIT_FAILURE);
    }
    s->numS = nvSommet;
    s->marq = 0;
    s->suiv = part->Lsommet;
    part->Lsommet = s;
    part->taille++;
}

void insertion_tournee(Tournee *tourn, int nvSommet)
{
	Sommet *s = malloc(sizeof(Sommet));
	
	if (tourn == NULL || s == NULL)
    {
        exit(EXIT_FAILURE);
    }
    s->numS = nvSommet;
    s->marq = 0;
    s->suiv = tourn->Lsommet;
    tourn->Lsommet = s;
    tourn->taille++;
}

void detruire_partition(Partition *part)
{
	Sommet *tmp = part->Lsommet;
	while(part->Lsommet)
	{
		part->Lsommet = part->Lsommet->suiv;
		free(tmp);
		tmp = part->Lsommet;
	}
}

void detruire_tournee(Tournee *tourn)
{
	Sommet *tmp = tourn->Lsommet;
	while(tourn->Lsommet)
	{
		tourn->Lsommet = tourn->Lsommet->suiv;
		free(tmp);
		tmp = tourn->Lsommet;
	}
}

void partitionner(Partition **parttab, Vecteur* vecttab ,int N, int k)
{
	int i,j;
	float tmp; //Stocke le résultat du rand
	float cumul = 0;
	
	//Pour chaque sommet autre que le dépot on l'assigne à une partition
	for (i = 1; i < N; i++)
	{
		tmp = (float)rand() / (float)RAND_MAX;;
		
		for (j = 0; j < k; j++)
		{
			//Pour empecher de ne pas assigner un sommet on insère dans la dernière partition par défaut
			if (tmp < vecttab[i].vec[j] + cumul || j == k-1)
			{
				insertion_partition(parttab[j], i);
				cumul = 0;
				break;
			}
			else
			{
				cumul += vecttab[i].vec[j];
			}
		}		
	}
}

void afficher_tournee(Tournee *tourn, FILE *sortie)
{
	
	Sommet *tmp = tourn->Lsommet;
	fprintf(sortie,"0");
	while (tmp != NULL)
	{
		fprintf(sortie," -> %d",tmp->numS);
		tmp = tmp->suiv;
	}
	fprintf(sortie,"\n");
	
}
