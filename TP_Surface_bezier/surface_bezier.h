#include "o_objet.h"
#include "t_geometrie.h"
#include <math.h>
#include "bezier.h"

typedef struct
{
	bezier u;
	bezier v;

} surface_bezier ; 

void calcul_surface_bezier(surface_bezier *sb);