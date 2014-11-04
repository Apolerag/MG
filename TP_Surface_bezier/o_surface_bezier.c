#include "o_surface_bezier.h"

void changement_surface_bezier(surface_bezier* sb)
{
	int i;
	if ( ! (UN_CHAMP_CHANGE(sb)||CREATION(sb)) )
		return ;  


	if ( CREATION(sb)
		|| CHAMP_CHANGE(sb, affiche)
		|| CHAMP_CHANGE(sb, G) 
		|| CHAMP_CHANGE(sb, u)
		|| CHAMP_CHANGE(sb, v))
	{
		if(sb->u < 0)
			sb->u = 10;

		if(sb->v < 0)
			sb->v = 10;

		if(sb->courbeU.grille != NULL)
		{
			for (i = 0; i < sb->courbeU.nb_lignes; ++i)
			{
				free(sb->courbeU.grille[i]);
			}
			free(sb->courbeU.grille);
		}

		if(sb->courbeV.grille != NULL)
		{
			for (i = 0; i < sb->courbeV.nb_lignes; ++i)
			{
				free(sb->courbeV.grille[i]);
			}
			free(sb->courbeV.grille);
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
		for(i = 0; i < sb->G.nb_lignes; ++i)
		{
			glBegin(GL_LINE_STRIP) ;

			glColor3f(1.0, 1.0, 0.0);

			for(j = 0; j < sb->G.nb_colonnes ; ++j)
				glVertex3f(sb->G.grille[i][j].x, sb->G.grille[i][j].y, 
					       sb->G.grille[i][j].z);
			glEnd();
		}

		for(i = 0; i < sb->G.nb_colonnes; ++i)
		{
			glBegin(GL_LINE_STRIP) ;

			glColor3f(1.0, 1.0, 0.0);

			for(j = 0; j < sb->G.nb_lignes ; ++j)
				glVertex3f(sb->G.grille[j][i].x, sb->G.grille[j][i].y, 
					       sb->G.grille[j][i].z);
			glEnd();
		}
		
	}

	for(i = 0; i < sb->courbeU.nb_lignes; ++i)
	{
		glBegin(GL_LINE_STRIP) ;

		glColor3f(1.0, 0.0, 0.0);

		for(j = 0; j < sb->courbeU.nb_colonnes ; ++j)
			glVertex3f(sb->courbeU.grille[i][j].x, 
					   sb->courbeU.grille[i][j].y, 
				       sb->courbeU.grille[i][j].z);
		glEnd();
	}

	for(i = 0; i < sb->courbeV.nb_lignes; ++i)
	{
		glBegin(GL_LINE_STRIP) ;

		glColor3f(1.0, 0.0, 0.0);

		for(j = 0; j < sb->courbeV.nb_colonnes ; ++j)
			glVertex3f(sb->courbeV.grille[i][j].x, 
					   sb->courbeV.grille[i][j].y, 
				       sb->courbeV.grille[i][j].z);
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