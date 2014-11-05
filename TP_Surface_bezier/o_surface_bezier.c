#include "o_surface_bezier.h"

void changement_surface_bezier(surface_bezier* sb)
{
	int i;
	if ( ! (UN_CHAMP_CHANGE(sb)||CREATION(sb)) )
		return ;  


	if ( CREATION(sb)
		|| CHAMP_CHANGE(sb, G)
		|| CHAMP_CHANGE(sb, affiche)
		|| CHAMP_CHANGE(sb, u)
		|| CHAMP_CHANGE(sb, v))
	{
		if(sb->u < 0)
			sb->u = 10;

		if(sb->v < 0)
			sb->v = 10;

		if(sb->surface.grille != NULL)
		{
			for (i = 0; i < sb->surface.nb_lignes; i++)
			{
				free(sb->surface.grille[i]);
			}
			free(sb->surface.grille);
		}

		calcul_surface_bezier(sb);
	}
}


void affiche_surface_bezier(surface_bezier* sb)
{
	int i,j;

	/* affichage de la grille de controle*/
	if(sb->affiche)
	{
		for(i = 0; i < sb->G.nb_lignes; i++)
		{
			glBegin(GL_LINE_STRIP) ;

			glColor3f(1.0, 1.0, 0.0);

			for(j = 0; j < sb->G.nb_colonnes ; j++)
				glVertex3f(sb->G.grille[i][j].x, sb->G.grille[i][j].y, 
					       sb->G.grille[i][j].z);
			glEnd();
		}

		for(i = 0; i < sb->G.nb_colonnes; i++)
		{
			glBegin(GL_LINE_STRIP) ;

			glColor3f(1.0, 1.0, 0.0);

			for(j = 0; j < sb->G.nb_lignes ; j++)
				glVertex3f(sb->G.grille[j][i].x, sb->G.grille[j][i].y, 
					       sb->G.grille[j][i].z);
			glEnd();
		}
		
	}

	/*affichage de la surface*/
	for(i = 0; i < sb->surface.nb_lignes; i++)
	{
		glBegin(GL_LINE_STRIP) ;

		glColor3f(0.0, 0.0, 1.0);

		for(j = 0; j < sb->surface.nb_colonnes ; j++)
			glVertex3f(sb->surface.grille[i][j].x, 
					   sb->surface.grille[i][j].y, 
				       sb->surface.grille[i][j].z);
		glEnd();
	}

	for(i = 0; i < sb->surface.nb_colonnes; i++)
	{
		glBegin(GL_LINE_STRIP) ;

		glColor3f(0.0, 0.0, 1.0);

		for(j = 0; j < sb->surface.nb_lignes ; j++)
			glVertex3f(sb->surface.grille[j][i].x, 
					   sb->surface.grille[j][i].y, 
				       sb->surface.grille[j][i].z);
		glEnd();
	}
}


CLASSE(Surface_Bezier, surface_bezier,      
	CHAMP(G, LABEL("Points de controle") L_grille_point P_grille_quadruplet Obligatoire Extrait)
	/*CHAMP(PointAfficheU, LABEL("Nombre de points sur la courbe U ") L_entier Affiche Edite Sauve DEFAUT("10"))*/
	CHAMP(affiche,LABEL("Afficher les points de controle") L_booleen Edite DEFAUT("1"))
	CHAMP(u, LABEL("Nombre de points u: ") L_entier Affiche Edite Sauve DEFAUT("10"))
	CHAMP(v, LABEL("Nombre de points v: ") L_entier Affiche Edite Sauve DEFAUT("10"))
	
	CHANGEMENT(changement_surface_bezier)
	CHAMP_VIRTUEL(L_affiche_gl(affiche_surface_bezier))

	MENU("TP_Bezier/Surface_Bezier")
	EVENEMENT("Ctrl+SB")
	)