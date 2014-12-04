#include <math.h>

#include "bezier.h"
#include "o_objet.h"
#include "sys_lin.h"
#include "t_geometrie.h"

typedef struct
{
	Bezier b;
	Table_triplet points;
	int parametrage;
} Interpolation ; 


Table_flottant parametrage(Table_triplet *points, int parametrage) ;

Grille_flottant matrice(Interpolation *inter);