#include "bezier.h"
#include <GL/gl.h>

void calcul_Bezier(Bezier* b)
{          
	int i,j,k;

	double u = (double)1/(b->nbPointAffiche + 1);

	Quadruplet* Quad;                       

	ALLOUER(b->tabPointAffiche, b->nbPointAffiche);//Allocation du tableau de res
	ALLOUER(Quad, b->pt.nb);//Allocation du tableau de Quad

	for(k = 0; k < b->nbPointAffiche; ++k)
	{
		for (j = 0; j < b->pt.nb; ++j)
		{
			Quad[j] = b->pt.table[j];
		}

		for(j = b->pt.nb-1; j > 0 ; --j)
		{
			for(i = 0; i < j ; ++i)
			{
				//Calcul
				Quad[i].x = (u * Quad[i+1].x) + (1-u) * Quad[i].x;	
				Quad[i].y = (u * Quad[i+1].y) + (1-u) * Quad[i].y;
				Quad[i].z = (u * Quad[i+1].z) + (1-u) * Quad[i].z;
				Quad[i].h = (u * Quad[i+1].h) + (1-u) * Quad[i].h;
			}
		}
		if(Quad[0].h == 0) Quad[0].h = 1;
	    b->tabPointAffiche[k].x = Quad[0].x /Quad[0].h;
	    b->tabPointAffiche[k].y = Quad[0].y /Quad[0].h;
		b->tabPointAffiche[k].z = Quad[0].z /Quad[0].h;

		u +=  (double)1/(b->nbPointAffiche + 1);
	}
	free(Quad);
}


void calcul_Bezier_reparametre(Bezier* b)
{
	int i,j,k;
	double u = 0;
	Quadruplet* Quad;                         
	Quadruplet* Sup;              

	ALLOUER(b->ptReparametre, b->pt.nb);//Allocation du tableau de res
	ALLOUER(Quad, b->pt.nb);//Allocation d'un tableau de Quadriplet
	ALLOUER(Sup, b->pt.nb);//Allocation d'un tableau de Quad
	ALLOUER(b->tabPointReparametre, b->nbPointReparametre);

	//calcul des points de controles entre 0 et borneSup
	for (j = 0; j < b->pt.nb; ++j)
	{
		Quad[j] = b->pt.table[j];
	}
	Sup[b->pt.nb-1]= Quad[0];
	for(j = b->pt.nb-1; j > 0 ; --j)
	{
		fprintf(stderr, "j-1 %d\n",j-1);
		fprintf(stderr, "b->pt.nb %d\n",b->pt.nb);
		//Sup[j] = Quad[0];

		
		for(i = 0; i < j ; ++i)
		{
			Quad[i].x = (b->borneSup * Quad[i+1].x) + (1-b->borneSup) * Quad[i].x;	
			Quad[i].y = (b->borneSup * Quad[i+1].y) + (1-b->borneSup) * Quad[i].y;
			Quad[i].z = (b->borneSup * Quad[i+1].z) + (1-b->borneSup) * Quad[i].z;
			Quad[i].h = (b->borneSup * Quad[i+1].h) + (1-b->borneSup) * Quad[i].h;
		}
		Sup[j-1]= Quad[0];
	}

	//Calcul des points de controle entre borneInf et borne Sup
	for (j = 0; j < b->pt.nb; ++j)
	{
		Quad[j] = Sup[b->pt.nb-1-j];
	}
	for(j = b->pt.nb-1; j > 0 ; --j)
	{
		b->ptReparametre[0] = Quad[0];
		for(i = 0; i < j ; ++i)
		{
			Quad[i].x = (b->borneInf/b->borneSup * Quad[i+1].x) + (1-b->borneInf/b->borneSup) * Quad[i].x;	
			Quad[i].y = (b->borneInf/b->borneSup * Quad[i+1].y) + (1-b->borneInf/b->borneSup) * Quad[i].y;
			Quad[i].z = (b->borneInf/b->borneSup * Quad[i+1].z) + (1-b->borneInf/b->borneSup) * Quad[i].z;
			Quad[i].h = (b->borneInf/b->borneSup * Quad[i+1].h) + (1-b->borneInf/b->borneSup) * Quad[i].h;
		}
	}
	for (j = 0; j < b->pt.nb; ++j)
	{
		b->ptReparametre[j] = Quad[j];
	}

	// Calcul de la courbe entre BorneInf et BorneSup
	u = (double)1/(b->nbPointReparametre + 1);
	for(k = 0; k < b->nbPointReparametre; ++k)
	{
		for (j = 0; j < b->pt.nb; ++j)
		{
			Quad[j] = b->ptReparametre[j];
		}

		for(j = b->pt.nb-1; j > 0 ; --j)
		{
			for(i = 0; i < j ; ++i)
			{
				//Calcul
				Quad[i].x = (u * Quad[i+1].x) + (1-u) * Quad[i].x;	
				Quad[i].y = (u * Quad[i+1].y) + (1-u) * Quad[i].y;
				Quad[i].z = (u * Quad[i+1].z) + (1-u) * Quad[i].z;
				Quad[i].h = (u * Quad[i+1].h) + (1-u) * Quad[i].h;
			}
		}
		if(Quad[0].h == 0) Quad[0].h = 1;
	    b->tabPointReparametre[k].x = Quad[0].x /Quad[0].h;
	    b->tabPointReparametre[k].y = Quad[0].y /Quad[0].h;
		b->tabPointReparametre[k].z = Quad[0].z /Quad[0].h;

		u +=  (double)1/(b->nbPointReparametre + 1);
	}

	free(Quad);
	free(Sup);
}
