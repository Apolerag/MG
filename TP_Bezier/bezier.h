#include "o_objet.h"
#include "t_geometrie.h"
#include <math.h>

typedef struct
{
	Booleen affiche; //permet l'affichage ou non des  points de controle de la courbe
	int nbPointAffiche; // le nombre de points affichés de la courbe
	Table_quadruplet pt; // les points de controle
	Triplet* tabPointAffiche; //les points de la courbe

	double borneInf, borneSup; //l'intervalle de reparametrage de la courbe
	Quadruplet* ptReparametre;	//les points de controle de la courbe reparamétrée
	Triplet* tabPointReparametre;	//la courbe reparamétrée
	int nbPointReparametre;	// le nombre de points de la courbe reparamétrée
	Booleen afficheReparametre;
} bezier ; 


void calcul_bezier(bezier* b);

void calcul_bezier_reparametre(bezier* b);
