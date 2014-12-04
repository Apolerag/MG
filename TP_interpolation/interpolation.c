#include <math.h>

#include "interpolation.h"
#include "o_objet.h"
#include "t_geometrie.h"

static double dist(Triplet *a, Triplet *b)
{
	return  sqrt(pow(a->x - b->x,2) + pow(a->y - b->y,2) + pow(a->z - b->z,2));
}

static int factorielle(const int n)
{
	int i;
	int f = 1;

	for (i = 1; i <= n; ++i)
	{
		f *= i;
	}
	return f;
}

static int coefficient_binomial(const int n, const int k) {
	if(k < 0 || k > n) return 0;

	return factorielle(n)/(factorielle(k)*factorielle(n-k));
}

Table_flottant parametrage(Table_triplet *	points, int parametrage) 
{
	Table_flottant f;
	ALLOUER(f.table, points->nb);
	f.nb = points->nb;
	int i;
	double distTotal, d;

	if(parametrage == 0) //parametrage uniforme
	{
		for (i = 0; i < f.nb; ++i) {
			f.table[i] = (double) i/(f.nb-1);
		}
	}
	else {
		distTotal = 0.0;
		for (i = 1; i < f.nb; ++i) {
			distTotal += dist(&points->table[i-1], &points->table[i]);
		}
		d = 0.0;
		f.table[0] = 0;
		for (i = 1; i < f.nb; ++i) {
			d += dist(&points->table[i-1], &points->table[i]);
			f.table[i] = (double) d/distTotal;
		}
	}
	return f;
}

Grille_flottant matrice(Interpolation *inter)
{
	int i,j;  
	Grille_flottant matrice;

	ALLOUER(matrice.grille,inter->points.nb);
	matrice.nb_lignes = inter->points.nb;
	matrice.nb_colonnes = inter->points.nb;

	for (i=0 ; i<matrice.nb_lignes ; i++)
	{
		ALLOUER(matrice.grille[i],matrice.nb_colonnes);
	}

	return matrice;
}