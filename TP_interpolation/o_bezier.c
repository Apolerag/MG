#include <GL/gl.h>
#include <math.h>

#include "bezier.h"
#include "o_objet.h"
#include "sys_lin.h"
#include "t_geometrie.h"
#include "u_table.h"

static void changement(Bezier* b)
{
	if ( ! (UN_CHAMP_CHANGE(b)||CREATION(b)) )
		return ;  

	if ( CREATION(b)
		|| CHAMP_CHANGE(b, nbPointAffiche) 
		|| CHAMP_CHANGE(b, pt)
		|| CHAMP_CHANGE(b,affiche))
	{
		if(b->tabPointAffiche != NULL)		
			free(b->tabPointAffiche);

		if(b->nbPointAffiche < 0)
			b->nbPointAffiche = 10;

		if(b->affiche != 0 && b->affiche != 1)
			b->affiche = 1;

		calcul_Bezier(b);
	}
}


static void affiche_Bezier(Bezier* b)
{
	int j;
	if(b->nbPointAffiche != 0)
	{
		glBegin(GL_LINE_STRIP) ;
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(b->pt.table[0].x, b->pt.table[0].y, b->pt.table[0].z);
		for(j = 0; j < b->nbPointAffiche ; ++j)
			glVertex3f(b->tabPointAffiche[j].x, b->tabPointAffiche[j].y, b->tabPointAffiche[j].z); 

		glVertex3f(b->pt.table[b->pt.nb-1].x, b->pt.table[b->pt.nb-1].y, b->pt.table[b->pt.nb-1].z);

		glEnd();
	}

	if(b->affiche)
	{
		glBegin(GL_LINE_STRIP) ;

		glColor3f(1.0, 1.0, 1.0);

		for(j = 0; j < b->pt.nb ; ++j)
			glVertex3f(b->pt.table[j].x, b->pt.table[j].y, b->pt.table[j].z);
		glEnd();
	}
	

	
}

CLASSE(Bezier, Bezier,      
	CHAMP(nbPointAffiche, LABEL("Nombre de points à afficher: ") L_entier Affiche Edite Sauve DEFAUT("10"))
	CHAMP(affiche,LABEL("Afficher les points de controle") L_booleen Edite DEFAUT("1"))
	CHAMP(pt, LABEL("Points ") L_table_point P_table_quadruplet Obligatoire Extrait)

	CHANGEMENT(changement)
	CHAMP_VIRTUEL(L_affiche_gl(affiche_Bezier))

	MENU("TP_Bezier/Bezier")
	EVENEMENT("Ctrl+CB")
	)
