#include "LRI.h"

double LRI_proba(double b,double proba,double util)
{
	return util*b*(1-proba);
}

double LRI_util(int courant,int min,int max)
{
	return (double)(max - courant) / (double)(max - min);
}
