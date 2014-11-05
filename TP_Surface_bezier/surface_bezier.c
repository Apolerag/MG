#include "surface_bezier.h"

void calcul_surface_bezier(surface_bezier *sb)
{
	int i,j;
	Grille_quadruplet Ginv;

	sb->courbeU.nb_lignes = sb->G.nb_lignes;
	sb->courbeU.nb_colonnes = sb->u;
	sb->courbeV.nb_lignes = sb->u;
	sb->courbeV.nb_colonnes = sb->v;
	printf("u %d, v %d \n", sb->u, sb->v);

	Ginv.nb_lignes = sb->courbeU.nb_colonnes;
	Ginv.nb_colonnes = sb->courbeU.nb_lignes;

	ALLOUER(sb->courbeU.grille, sb->courbeU.nb_lignes);
	for (i = 0; i < sb->courbeU.nb_lignes; i++)
		ALLOUER(sb->courbeU.grille[i], sb->courbeU.nb_colonnes);

	ALLOUER(Ginv.grille, Ginv.nb_lignes);
	for (i = 0; i < Ginv.nb_lignes; i++)
		ALLOUER(Ginv.grille[i], Ginv.nb_colonnes);

	ALLOUER(sb->courbeV.grille, sb->courbeV.nb_lignes);
	for (i = 0; i < sb->courbeV.nb_lignes; i++)
		ALLOUER(sb->courbeV.grille[i], sb->courbeV.nb_colonnes);

	for (i = 0; i < sb->courbeU.nb_lignes; i++)
	{
		Casteljau(sb->courbeU.grille[i] ,sb->G.grille[i],
			sb->G.nb_colonnes, sb->courbeU.nb_colonnes);
	}

	for (i = 0; i < Ginv.nb_colonnes; i++)
	{
		for (j = 0; j < Ginv.nb_lignes; j++)
		{
			Ginv.grille[j][i].x = sb->courbeU.grille[i][j].x;
			Ginv.grille[j][i].y = sb->courbeU.grille[i][j].y;
			Ginv.grille[j][i].z = sb->courbeU.grille[i][j].z;
			Ginv.grille[j][i].h = 1;
		}
	}


	for (i = 0; i < sb->courbeV.nb_lignes; i++)
	{
		Casteljau(sb->courbeV.grille[i] ,Ginv.grille[i],
			Ginv.nb_colonnes, sb->courbeV.nb_colonnes);
	}

	for (i = 0; i < Ginv.nb_lignes; i++)
		free(Ginv.grille[i]);
	free(Ginv.grille);
}

void Casteljau(Triplet * courbe, Quadruplet *poly, const int nbPoly, const int nbAffiche)
{          
	int i,j,k;

	double u = (double)1/(nbAffiche + 1);

	Quadruplet* Quad;                       

	ALLOUER(Quad, nbPoly);//Allocation du tableau de Quad

	for(k = 0; k < nbAffiche; ++k)
	{
		for (j = 0; j < nbPoly; j++)
		{
			Quad[j] = poly[j];
		}

		for(j = nbPoly -1; j > 0 ; --j)
		{
			for(i = 0; i < j ; i++)
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