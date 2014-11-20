#include "o_objet.h"
#include "t_geometrie.h"

#include <math.h>

typedef struct
{
	Booleen affiche; //permet l'affichage ou non des  points de controle de la courbe
	int nbPointAffiche; // le nombre de points affichés de la courbe
	Table_quadruplet pt; // les points de controle
	Triplet* tabPointAffiche; //les points de la courbe
	int degre; //le degré de la BSpline
	Table_flottant V;	//le vecteur nodal de la BSpline
} bSpline ; 

/* calcul du vecteur nodal de la BSpline*/
void calcul_vecteur_nodal(bSpline * b);

/*Calcul de la courbe*/
void calcul_bSpline(bSpline* b);
