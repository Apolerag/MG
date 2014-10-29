#include "bezier.h"
#include <GL/gl.h>

void calcul_bezier(bezier* b)
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
