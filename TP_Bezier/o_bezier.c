#include <GL/gl.h>
#include <math.h>
#include "o_objet.h"
#include "u_table.h"
#include "t_geometrie.h"
#include "bezier.h"

static void changement(bezier* b)
{
	if ( ! (UN_CHAMP_CHANGE(b)||CREATION(b)) )
		return ;  

	if ( CREATION(b)
		|| CHAMP_CHANGE(b, nbPointAffiche) 
		|| CHAMP_CHANGE(b, pt)
		|| CHAMP_CHANGE(b,affiche)
		|| CHAMP_CHANGE(b,borneInf)
		|| CHAMP_CHANGE(b,borneSup)
		|| CHAMP_CHANGE(b, nbPointReparametre)
		|| CHAMP_CHANGE(b, afficheReparametre))
	{
		if(b->tabPointAffiche != NULL)		
			free(b->tabPointAffiche);

		if(b->tabPointReparametre != NULL)
			free(b->tabPointReparametre);

		if(b->tabPointReparametre != NULL)
			free(b->ptReparametre);

		if(b->nbPointAffiche < 0)
			b->nbPointAffiche = 10;

		if(b->nbPointReparametre < 0)
			b->nbPointReparametre = 10;

		if(b->borneSup < b->borneInf)
		{
			b->borneInf = 0;
			b->borneSup = 1;
		}
		if(b->borneSup > 1 || b->borneSup < 0)
			b->borneSup = 1;

		if(b->borneInf < 0 || b->borneInf > 1)
			b->borneInf = 0;

		if(b->affiche != 0 && b->affiche != 1)
			b->affiche = 1;

		calcul_bezier(b);

		if(b->borneInf != 0 || b->borneSup != 1)
		{
			calcul_bezier_reparametre(b);
		}
	}
}


static void affiche_bezier(bezier* b)
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

CLASSE(Bezier, bezier,      
	CHAMP(nbPointAffiche, LABEL("Nombre de points à afficher: ") L_entier Affiche Edite Sauve DEFAUT("10"))
	CHAMP(affiche,LABEL("Afficher les points de controle") L_booleen Edite DEFAUT("1"))
	CHAMP(afficheReparametre,LABEL("Afficher les points de controle de la courbe reparametrée") L_booleen Edite DEFAUT("1"))
	CHAMP(pt, LABEL("Points ") L_table_point P_table_quadruplet Obligatoire Extrait)
	CHAMP(borneInf, L_flottant Affiche Edite Sauve DEFAUT("0") ) 
	CHAMP(borneSup, L_flottant Affiche Edite Sauve DEFAUT("1") )        
	CHAMP(nbPointReparametre, LABEL("Nombre de points de la courbe reparametré: ") L_entier Affiche Edite Sauve DEFAUT("10"))
	
	CHANGEMENT(changement)
	CHAMP_VIRTUEL(L_affiche_gl(affiche_bezier))

	MENU("TP_Bezier/Bezier")
	EVENEMENT("Ctrl+CB")
	)
