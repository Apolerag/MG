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

static int coefficient_binomial(const int n, const int i) {
	if(i < 0 || i > n) return 0;

	return factorielle(n)/(factorielle(i)*factorielle(n-i));
}

static double bernstein(const int n, const int i, const double u)
{
	return coefficient_binomial(n,i) * pow(u,i)*pow(1-u,n-i);
}

Table_flottant parametrage(Interpolation *inter) 
{
	Table_flottant f;
	ALLOUER(f.table, inter->degre);
	f.nb = inter->degre;
	int i;
	double distTotal, d;

	if(inter->parametrage == 0) //parametrage uniforme
	{
		for (i = 0; i < f.nb; ++i) {
			f.table[i] = (double) i/(f.nb-1);
		}
	}
	else {
		distTotal = 0.0;
		for (i = 1; i < f.nb; ++i) {
			distTotal += dist(&inter->points.table[i-1], &inter->points.table[i]);
		}
		d = 0.0;
		f.table[0] = 0;
		for (i = 1; i < f.nb; ++i) {
			d += dist(&inter->points.table[i-1], &inter->points.table[i]);
			f.table[i] = (double) d/distTotal;
		}
	}
	return f;
}

Grille_flottant matrice(Interpolation *inter)
{
	int i,j;  
	Grille_flottant matrice;
	Table_flottant param = parametrage(inter);

	ALLOUER(matrice.grille,inter->degre);
	matrice.nb_lignes = inter->degre;
	matrice.nb_colonnes = inter->points.nb;

	for (i=0 ; i<matrice.nb_lignes ; ++i) {
		ALLOUER(matrice.grille[i],matrice.nb_colonnes);
		for (j = 0; j < matrice.nb_colonnes; ++j) {
			matrice.grille[i][j] = bernstein(matrice.nb_colonnes-1, j, param.table[i]);
		}
	}

	return matrice;
}

void interpolation(Interpolation *inter)
{
	int i;
	Grille_flottant b = matrice(inter);
	Grille_flottant bt = grille_flottant_transposee(&b);

	ALLOUER(inter->pt.table, inter->degre);
	inter->pt.nb = inter->degre;

	Grille_flottant A = produit_matrice(&b, &bt);

	Table_flottant val;

	Table_flottant q;
	q.nb = inter->points.nb;
	ALLOUER(q.table, q.nb );

	for (i = 0; i < q.nb; ++i)
	{
		q.table[i] = inter->points.table[i].x;
	}

	Table_flottant B = produit_matrice_vecteur(&b,&q);

	if(resolution_systeme_lineaire(&A, &B, &val) == 0) {
		for (i = 0; i < q.nb; ++i) {
			inter->pt.table[i].x = val.table[i];
		}
	}

	for (i = 0; i < q.nb; ++i)
	{
		q.table[i] = inter->points.table[i].y;
	}
	free(B.table);
	B = produit_matrice_vecteur(&b,&q);

	if(resolution_systeme_lineaire(&A, &B, &val) == 0) {
		for (i = 0; i < q.nb; ++i) {
			inter->pt.table[i].y = val.table[i];
		}
	}

	for (i = 0; i < q.nb; ++i)
	{
		q.table[i] = inter->points.table[i].z;
	}
	free(B.table);
	B = produit_matrice_vecteur(&b,&q);

	if(resolution_systeme_lineaire(&A, &B, &val) == 0) {
		for (i = 0; i < q.nb; ++i) {
			inter->pt.table[i].z = val.table[i];
		}
	}
	free(B.table);

}

void calcul_Bezier(Interpolation *inter)
{          
	int i,j,k;

	double u = (double)1/(inter->nbPointAffiche + 1);

	Triplet* Quad;                       

	ALLOUER(inter->tabPointAffiche, inter->nbPointAffiche);//Allocation du tableau de res
	ALLOUER(Quad, inter->pt.nb);//Allocation du tableau de Quad

	for(k = 0; k < inter->nbPointAffiche; ++k)
	{
		for (j = 0; j < inter->pt.nb; ++j)
		{
			Quad[j] = inter->pt.table[j];
		}

		for(j = inter->pt.nb-1; j > 0 ; --j)
		{
			for(i = 0; i < j ; ++i)
			{
				//Calcul
				Quad[i].x = (u * Quad[i+1].x) + (1-u) * Quad[i].x;	
				Quad[i].y = (u * Quad[i+1].y) + (1-u) * Quad[i].y;
				Quad[i].z = (u * Quad[i+1].z) + (1-u) * Quad[i].z;
			}
		}
	    inter->tabPointAffiche[k].x = Quad[0].x ;
	    inter->tabPointAffiche[k].y = Quad[0].y ;
		inter->tabPointAffiche[k].z = Quad[0].z ;

		u +=  (double)1/(inter->nbPointAffiche + 1);
	}
	free(Quad);
}
