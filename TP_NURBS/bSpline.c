#include "bSpline.h"

#include <GL/gl.h>

void calcul_vecteur_nodal(bSpline * b)
{
	int i;
	int n = b->pt.nb - 1;
	int k = b->degre + 1;
	b->V.nb = 2 * k + (n - k + 1);
	ALLOUER(b->V.table, b->V.nb);	

	for (i = 0; i <= k - 1; ++i)
	{
		b->V.table[i] = 0;
	}

	for (i = k; i <= n; ++i)
	{ 
		b->V.table[i] = (double)(i - k + 1)/(n - k + 2);
	}

	for (i = n+1; i <= n+k; ++i)
	{
		b->V.table[i] = 1;
	}

}

void calcul_bSpline(bSpline* b)
{          
	int h,i,j;
	//int n = b->pt.nb - 1;
	int k = b->degre + 1;
	int r = 0;

	double u = (double)1/(b->nbPointAffiche + 1);

	Quadruplet* Quad;                       

	ALLOUER(b->tabPointAffiche, b->nbPointAffiche);//Allocation du tableau de res
	ALLOUER(Quad, b->pt.nb);//Allocation du tableau de Quad

	for(h = 0; h < b->nbPointAffiche; ++h)
	{
		for (j = 0; j < b->pt.nb; ++j)
		{
			Quad[j] = b->pt.table[j];
		}

		while(r < b->V.nb && !(b->V.table[r] < u && b->V.table[r+1] > u)  )
			r++;

		for(j = 1; j <= k-1 ; ++j)
		{
			for(i = r; i >= r-k+1+j ; --i)
			{
				//Calcul
				Quad[i].x = (u - b->V.table[i]) / (b->V.table[i+k-j] - b->V.table[i]) * Quad[i].x + 
							(b->V.table[i+k-j] - u) / (b->V.table[i+k-j] - b->V.table[i]) *  Quad[i-1].x;	
				Quad[i].y = (u - b->V.table[i]) / (b->V.table[i+k-j] - b->V.table[i]) * Quad[i].y + 
							(b->V.table[i+k-j] - u) / (b->V.table[i+k-j] - b->V.table[i]) * Quad[i-1].y;	
				Quad[i].z = (u - b->V.table[i]) / (b->V.table[i+k-j] - b->V.table[i]) * Quad[i].z + 
							(b->V.table[i+k-j] - u) / (b->V.table[i+k-j] - b->V.table[i]) * Quad[i-1].z;	
				Quad[i].h = (u - b->V.table[i]) / (b->V.table[i+k-j] - b->V.table[i]) * Quad[i].h + 
							(b->V.table[i+k-j] - u) / (b->V.table[i+k-j] - b->V.table[i]) * Quad[i-1].h;
			}
		}
		if(Quad[r].h == 0) Quad[r].h = 1;
	    b->tabPointAffiche[h].x = Quad[r].x /Quad[r].h;
	    b->tabPointAffiche[h].y = Quad[r].y /Quad[r].h;
		b->tabPointAffiche[h].z = Quad[r].z /Quad[r].h;

		u +=  (double)1/(b->nbPointAffiche + 1);
	}
	free(Quad);
}
