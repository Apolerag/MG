#include "o_objet.h"
#include "t_geometrie.h"
#include <math.h>

typedef struct
{
	Grille_quadruplet G;
	int u; // le nombre de points affichés 
	int v;
	Grille_triplet surface;
	int affiche;

} surface_bezier ; 

void calcul_surface_bezier(surface_bezier *sb);

void Casteljau(Triplet * courbe, Quadruplet *poly, const int nbPoly, const int nbAffiche);