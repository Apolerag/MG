#include <GL/gl.h>
#include <math.h>

#include "o_objet.h"
#include "interpolation.h"
#include "sys_lin.h"
#include "t_geometrie.h"
#include "u_table.h"

static void changement(Interpolation* inter)
{
	if ( ! (UN_CHAMP_CHANGE(inter)||CREATION(inter)) )
		return ;  

	if ( CREATION(inter)
		|| CHAMP_CHANGE(inter, points)
		|| CHAMP_CHANGE(inter, parametrage)
		|| CHAMP_CHANGE(inter, degre)
		|| CHAMP_CHANGE(inter, nbPointAffiche) 
		|| CHAMP_CHANGE(inter,affiche))
	{
		if(inter->tabPointAffiche != NULL)		
			free(inter->tabPointAffiche);

		if(inter->pt.table != NULL)		
			free(inter->pt.table);

		if(inter->nbPointAffiche < 0)
			inter->nbPointAffiche = 10;

		if(inter->affiche != 0 && inter->affiche != 1)
			inter->affiche = 1;
		interpolation(inter);
		calcul_Bezier(inter);
	}
}

static void affiche_interpolation(Interpolation* inter)
{
	int j;
	if(inter->nbPointAffiche != 0)
	{
		glBegin(GL_LINE_STRIP) ;
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(inter->pt.table[0].x, inter->pt.table[0].y, inter->pt.table[0].z);
		for(j = 0; j < inter->nbPointAffiche ; ++j)
			glVertex3f(inter->tabPointAffiche[j].x, inter->tabPointAffiche[j].y, inter->tabPointAffiche[j].z); 

		glVertex3f(inter->pt.table[inter->pt.nb-1].x, inter->pt.table[inter->pt.nb-1].y, inter->pt.table[inter->pt.nb-1].z);

		glEnd();
	}

	if(inter->affiche)
	{
		glBegin(GL_LINE_STRIP) ;

		glColor3f(1.0, 1.0, 1.0);

		for(j = 0; j < inter->pt.nb ; ++j)
			glVertex3f(inter->pt.table[j].x, inter->pt.table[j].y, inter->pt.table[j].z);
		glEnd();
	}

	glBegin(GL_POINTS) ;

	glColor3f(0.0, 1.0, 0.0);

	for(j = 0; j < inter->points.nb ; ++j)
		glVertex3f(inter->points.table[j].x, inter->points.table[j].y, inter->points.table[j].z);
	glEnd();
	
}

CLASSE(Interpolation, Interpolation,      
	CHAMP(points, LABEL("Points ") L_table_point P_table_triplet Obligatoire Extrait)
	CHAMP(parametrage,LABEL("parametrage non uniforme") L_booleen Edite DEFAUT("1"))
	CHAMP(degre, LABEL("degré") L_entier Edite DEFAUT("2")) 
	CHAMP(nbPointAffiche, LABEL("Nombre de points à afficher: ") L_entier Affiche Edite Sauve DEFAUT("10"))
	CHAMP(affiche,LABEL("Afficher les points de controle") L_booleen Edite DEFAUT("1"))
	
	CHANGEMENT(changement)
	CHAMP_VIRTUEL(L_affiche_gl(affiche_interpolation))

	MENU("TP_Interpolation/Interpolation")
	EVENEMENT("Ctrl+I")
	)
