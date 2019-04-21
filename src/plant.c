#include "option.h"
#include "plant.h"

int plant_xy_cmp(void *v1, void *v2)
{
	int ret = 1;
	plant_t *p1 = v1;
	plant_t *p2 = v2;

	if((p1->x == p2->x)
		&&(p1->y == p2->y))
	{
		ret = 0;
	}
	
	return ret;
}
