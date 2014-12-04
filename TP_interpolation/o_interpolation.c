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
		|| CHAMP_CHANGE(inter, parametrage))
	{
		Table_flottant f = parametrage(&inter->points, inter->parametrage) ;
		int i;

		for (i = 0; i < f.nb; ++i)
		{
			fprintf(stderr, "%f ", f.table[i]);
		}
		fprintf(stderr, "\n ");

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
	
	if( (b->borneInf != 0 || b->borneSup != 1) && b->afficheReparametre)
	{
		glBegin(GL_LINE_STRIP) ;

		glColor3f(0.0, 1.0, 0.0);

		for(j = 0; j < b->pt.nb ; ++j)
			glVertex3f(b->ptReparametre[j].x, b->ptReparametre[j].y, b->ptReparametre[j].z);
		glEnd();

		if(b->nbPointReparametre != 0)
		{
			glBegin(GL_LINE_STRIP) ;
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(b->ptReparametre[0].x, b->ptReparametre[0].y, b->ptReparametre[0].z);
			for(j = 0; j < b->nbPointReparametre; ++j)
				glVertex3f(b->tabPointReparametre[j].x, b->tabPointReparametre[j].y, b->tabPointReparametre[j].z); 

			glVertex3f(b->ptReparametre[b->pt.nb-1].x, b->ptReparametre[b->pt.nb-1].y, b->ptReparametre[b->pt.nb-1].z);

			glEnd();
		}
		
	}

	
}

CLASSE(Interpolation, Interpolation,      
	CHAMP(points, LABEL("Points ") L_table_point P_table_triplet Obligatoire Extrait)
	CHAMP(parametrage,LABEL("parametrage non uniforme") L_booleen Edite DEFAUT("1"))
	
	CHANGEMENT(changement)
	CHAMP_VIRTUEL(L_affiche_gl(affiche_Bezier))

	MENU("TP_Interpolation/Interpolation")
	EVENEMENT("Ctrl+I")
	)
