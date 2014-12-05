#include <math.h>

#include "o_objet.h"
#include "sys_lin.h"
#include "t_geometrie.h"

typedef struct
{
	Table_triplet points; //les points qui interpole la courbe
	int parametrage;
	int degre;

	Booleen affiche; //permet l'affichage ou non des  points de controle de la courbe
	int nbPointAffiche; // le nombre de points affichés de la courbe
	Table_triplet pt; // les points de controle
	Triplet* tabPointAffiche; //les points de la courbe

} Interpolation ; 


Table_flottant parametrage(Interpolation *inter) ;

Grille_flottant matrice(Interpolation *inter);

void interpolation(Interpolation *inter);

void calcul_Bezier(Interpolation *inter);