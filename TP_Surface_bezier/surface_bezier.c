#include "surface_bezier.h"

void calcul_surface_bezier(surface_bezier *sb)
{
	int i,j;
	Quadruplet *q;

	sb->courbeU.nb_lignes = sb->G.nb_lignes;
	sb->courbeU.nb_colonnes = sb->u;

	ALLOUER(sb->courbeU.grille, sb->courbeU.nb_lignes);
	for (i = 0; i < sb->courbeU.nb_lignes; ++i)
	{
		ALLOUER(sb->courbeU.grille[i], sb->courbeU.nb_colonnes);
	}

	sb->courbeV.nb_lignes = sb->G.nb_colonnes;
	sb->courbeV.nb_colonnes = sb->v;

	ALLOUER(sb->courbeV.grille, sb->courbeV.nb_lignes);
	for (i = 0; i < sb->courbeV.nb_lignes; ++i)
	{
		ALLOUER(sb->courbeV.grille[i], sb->courbeV.nb_colonnes);
	}

	fprintf(stderr, "sb->courbeU.nb_colonnes %d\n", sb->courbeU.nb_colonnes);
	fprintf(stderr, "sb->courbeU.nb_lignes %d\n", sb->courbeU.nb_lignes);
	for (i = 0; i < sb->courbeU.nb_lignes; ++i)
	{
		Casteljau(sb->courbeU.grille[i] ,sb->G.grille[i], 
			sb->G.nb_colonnes, sb->courbeU.nb_colonnes);
	}

	/*for (i = 0; i < sb->courbeV.nb_lignes; ++i)
	{
		ALLOUER(q, sb->G.nb_colonnes);
		for (j = 0; j < sb->G.nb_colonnes; ++j)
		{
			q[j] = sb->G.grille[j][i];
		}
*/
		/*Casteljau(sb->courbeV.grille[i] ,q, 
			sb->G.nb_colonnes, sb->courbeV.nb_colonnes);*/
		/*free(q);
	}*/
}

void Casteljau(Triplet * courbe, Quadruplet *poly, const int nbPoly, const int nbAffiche)
{          
	int i,j,k;

	double u = (double)1/(nbAffiche + 1);

	Quadruplet* Quad;                       

	ALLOUER(Quad, nbPoly);//Allocation du tableau de Quad

	for(k = 0; k < nbAffiche; ++k)
	{
		for (j = 0; j < nbPoly; ++j)
		{
			Quad[j] = poly[j];
		}

		for(j = nbPoly -1; j > 0 ; --j)
		{
			for(i = 0; i < j ; ++i)
			{
				//Calcul
				Quad[i].x = (u * Quad[i+1].x) + (1-u) * Quad[i].x;	
				Quad[i].y = (u * Quad[i+1].y) + (1-u) * Quad[i].y;
				Quad[i].z = (u * Quad[i+1].z) + (1-u) * Quad[i].z;
				Quad[i].h = (u * Quad[i+1].h) + (1-u) * Quad[i].h;
			}
		}
		if(Quad[0].h == 0) Quad[0].h = 1;
	    courbe[k].x = Quad[0].x /Quad[0].h;
	    courbe[k].y = Quad[0].y /Quad[0].h;
		courbe[k].z = Quad[0].z /Quad[0].h;

		u +=  (double)1/(nbAffiche + 1);
	}
	free(Quad);
}