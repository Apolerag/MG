  
#include <GL/gl.h>
#include <math.h>
#include "o_objet.h"
#include "u_table.h"
#include "t_geometrie.h"



struct type_NE 
{
  Triplet t;
  Table_triplet T;
  Grille_triplet GT; 
  Quadruplet q;
  Table_quadruplet Q;
  Grille_quadruplet GQ;
  Table_flottant F; /*double*/
  double d;
  int  i;
  Booleen booleen; 
  Menu menu;
} ;



static void changement(struct type_NE *o)
{   
  printf("fonction changement appelee \n");  
  if ( ! (UN_CHAMP_CHANGE(o)||CREATION(o)) )
    return ;

  if (CHAMP_CHANGE(o, t) ||  CHAMP_CHANGE(o,i) ||
      CHAMP_CHANGE(o, booleen))
    {

      printf("On passe par ici si l'un des champs t,i ou booleen est modifie\n");


  /* Triplet t  :  t.x  t.y  t.z (double)
     T.nb nbre elements du tableau 
     T.table adresse du tableau de triplet Triplet *
     GT.nb_lignes  nombre de lignes du tableau
     GT.nb_colonnes  nombre de colonnes 
     GT.grille   Triplet **
   */
  /* idem pour Quadruplet  x y z h 
     Q.nb 
     Q.table   Quadruplet *
     GQ.nb_lignes 
     GQ.nb_colonnes  
     GQ.grille   Quadruplet **
  */  
  /* F.nb
     F.table  Flottant *  ou bien  double * 
  */
      o->q.x = 1;
      o->q.y = 12;
      o->q.z = -5;
      o->q.h = 1;  /* x,y,z coordonnees cartesiennes  h: coordonnee homogene*/  
    }

  o->T.nb = 3;
  

  
}


static void fonction_affichage(struct type_NE *o)
{
  /* lignes de codes pour affichage GL si necessaire */
  if (o->menu.index==0)
    printf("choix 1 a ete selectionne \n");
  if (o->menu.index==1)
    printf("choix 2 a ete selectionne \n");
  if (o->menu.index==2)
    printf("choix 3 a ete selectionne \n");

  

}




CLASSE(type_NE, struct type_NE,      
       CHAMP(t, L_point P_triplet Sauve Affiche) 
       CHAMP(T, L_table_point P_table_triplet   Sauve Affiche) 
       CHAMP(T.nb, L_entier  Affiche)  
       CHAMP(GT, L_grille_point P_grille_triplet Sauve Affiche)
 
       CHAMP(q, L_point P_quadruplet Sauve Affiche) 
       CHAMP(Q, L_table_point P_table_quadruplet Sauve) 
       CHAMP(GQ, L_grille_point P_grille_quadruplet Sauve)

       CHAMP(i, LABEL("entier")  L_entier Affiche Edite Sauve DEFAUT("10") )
       CHAMP(d, L_flottant Extrait Obligatoire Edite) 

       CHAMP(F, L_table_flottant P_table_flottant  Edite) 

       CHAMP(booleen, L_booleen Edite DEFAUT("0"))
       CHAMP(menu,  LABEL("exemple de menu")
	     L_solide P_option_menu E_option_menu
	     TE_TEXTE(
                      "choix 1\n"
		      "choix 2\n"
                      "choix 3\n" 
		      )
	     DEFAUT("choix 2")
	     Edite Sauve
	     )
       
       CHANGEMENT(changement)
       CHAMP_VIRTUEL(L_affiche_gl(fonction_affichage))
        
       MENU("Exemples_MG/arborescsnce/Exemple de types NE")
       EVENEMENT("Ctrl+TYPE")
       )
