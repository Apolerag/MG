#include "o_surface_bezier.h"

void changement_surface_bezier(surface_bezier* sb)
{
	if ( ! (UN_CHAMP_CHANGE(sb)||CREATION(sb)) )
		return ;  

/*	if ( CREATION(sb)
		|| CHAMP_CHANGE(sb, u) 
		|| CHAMP_CHANGE(sb, v)
		|| CHAMP_CHANGE(sb, PointAfficheV)
		|| CHAMP_CHANGE(sb, PointAfficheU))*/
	if ( CREATION(sb)
		|| CHAMP_CHANGE(sb, u) 
		|| CHAMP_CHANGE(sb, v))
	{
		/*if(sb->PointAfficheU < 0)
			sb->PointAfficheU = 10;

		if(sb->PointAfficheV < 0)
			sb->PointAfficheV = 10;*/


	}
}

void affiche_bezier(bezier* b)
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


void affiche_surface_bezier(surface_bezier* sb)
{
	affiche_bezier(&sb->u);
	affiche_bezier(&sb->v);
}


CLASSE(Surface_Bezier, surface_bezier,      
	CHAMP(u.pt, LABEL("Points de controle de U ") L_table_point P_table_quadruplet Obligatoire Extrait)
	/*CHAMP(PointAfficheU, LABEL("Nombre de points sur la courbe U ") L_entier Affiche Edite Sauve DEFAUT("10"))*/
	CHAMP(v.pt, LABEL("Point de controle de V ") L_table_point P_table_quadruplet Obligatoire Extrait)
	/*CHAMP(PointAfficheU, LABEL("Nombre de points sur la courbe V ") L_entier Affiche Edite Sauve DEFAUT("10"))*/
	
	
	CHANGEMENT(changement_surface_bezier)
	CHAMP_VIRTUEL(L_affiche_gl(affiche_surface_bezier))

	MENU("TP_Bezier/Surface_Bezier")
	EVENEMENT("Ctrl+SB")
	)