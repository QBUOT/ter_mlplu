#include "Vecteurs.h"
#include "LRI.h"

Vecteur init_vecteur(int k)
{
	Vecteur v;
	int i;
	double val = 1.0/k;
	
	v.taille = k;
	v.vec = calloc(k,sizeof(double));
	
	for (i = 0; i < k; i++)
	{
		v.vec[i] = val;
	}
	return v;
}

Vecteur modif_vecteur(Vecteur v, int nmcompo, double util, double B)
{
	for (int i = 0; i < v.taille; i++)
	{
		if (i == nmcompo)
		{
			v.vec[i] += LRI_proba(B,v.vec[i],util);
		}
		else
		{
			v.vec[i] -= util*B*v.vec[i];
		}
	}
	
	
	return v;
}

