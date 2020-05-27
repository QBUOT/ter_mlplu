#include "Graphe.h"
#include "Vecteurs.h"
#include <stdlib.h>
#include <stdio.h>

//Structures et fonctions pour la gestion des partitions et des tournées

//Une partition est le résultat pour un véhicule donné de la sélection d'un véhicule par chaque joueur
//Un chemin est le résultat du TSP sur une partition donnée

//Définition d'un élement d'une liste de sommets
typedef struct Sommet Sommet;
struct Sommet
{
	int numS; //Numéro de sommet
	int marq; //Marquage
	Sommet *suiv;
};

//Définition d'une partition
typedef struct Partition Partition;
struct Partition
{
	Sommet *Lsommet; //Liste de sommets
	int taille; //Taille de la partition
};

//Définition d'une tournée
typedef struct Tournee Tournee;
struct Tournee
{
	Sommet *Lsommet; //Liste de sommets
	int taille; //Taille de la tournée
	int valeur; //Résultat du TSP
};

//Initialisation d'une partition vide
Partition* init_partition();

//Initialisation d'une tournée vide
Tournee* init_tournee();

//Insertion dans une partition
void insertion_partition(Partition *part, int nvSommet);

//Insertion dans une tournée
void insertion_tournee(Tournee *tourn, int nvSommet);

//Détruire une partition
void detruire_partition(Partition *part);

//Détruire une tournée
void detruire_tournee(Tournee *tourn);

//Remplir un tableau de k partition à partir d'un tableau de vecteurs de taille N*k
void partitionner(Partition **parttab, Vecteur* vecttab,  int N, int k);

void afficher_tournee(Tournee *tourn, FILE *sortie);




