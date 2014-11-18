#include <GL/gl.h>
#include <math.h>

#include "bSpline.h"
#include "o_objet.h"
#include "t_geometrie.h"
#include "u_table.h"

static void changement(bSpline* b)
{
	if ( ! (UN_CHAMP_CHANGE(b)||CREATION(b)) )
		return ;  

	if ( CREATION(b)
		|| CHAMP_CHANGE(b, nbPointAffiche) 
		|| CHAMP_CHANGE(b, pt)
		|| CHAMP_CHANGE(b, affiche)
		|| CHAMP_CHANGE(b, degre)
		|| CHAMP_CHANGE(b, V))
	{
		if(b->tabPointAffiche != NULL)		
			free(b->tabPointAffiche);

		if(b->nbPointAffiche < 0)
			b->nbPointAffiche = 10;

		if(b->degre > b->pt.nb || b->degre < 0)
			b->degre = b->pt.nb/2;

		if(b->affiche != 0 && b->affiche != 1)
			b->affiche = 1;

		if(CHAMP_CHANGE(b, degre))
		{
			free(b->V.table);
			b->V.nb = 0;
		}
		if(CREATION(b) || CHAMP_CHANGE(b, degre))
		{
			calcul_vecteur_nodal(b);
		}
		

		calcul_bSpline(b);
	}
}


static void affiche_bSpline(bSpline* b)
{
	int j;
	if(b->nbPointAffiche != 0)
	{
		glBegin(GL_LINE_STRIP) ;
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(b->pt.table[0].x, b->pt.table[0].y, b->pt.table[0].z);
		for(j = 0; j < b->nbPointAffiche ; ++j)
			glVertex3f(b->tabPointAffiche[j].x, b->tabPointAffiche[j].y, b->tabPointAffiche[j].z); 

		glVertex3f(b->pt.table[b->pt.nb-1].x, b->pt.table[b->pt.nb-1].y, b->pt.table[b->pt.nb-1].z);

		glEnd();
	}

	if(b->affiche)
	{
		glBegin(GL_LINE_STRIP) ;

		glColor3f(1.0, 0.0, 1.0);

		for(j = 0; j < b->pt.nb ; ++j)
			glVertex3f(b->pt.table[j].x, b->pt.table[j].y, b->pt.table[j].z);
		glEnd();
	}

	
}

CLASSE(bSpline, bSpline,      
	CHAMP(nbPointAffiche, LABEL("Nombre de points à afficher: ") L_entier Affiche Edite Sauve DEFAUT("10"))
	CHAMP(affiche,LABEL("Afficher les points de controle") L_booleen Edite DEFAUT("1"))
	CHAMP(degre,LABEL("degre de la B-spline") L_entier Edite DEFAUT("1"))
	CHAMP(pt, LABEL("Points ") L_table_point P_table_quadruplet Obligatoire Extrait)
	CHAMP(V, L_table_flottant P_table_flottant  Edite) 
	
	CHANGEMENT(changement)
	CHAMP_VIRTUEL(L_affiche_gl(affiche_bSpline))

	MENU("TP_bSpline/bSpline")
	EVENEMENT("Ctrl+BS")
	)
