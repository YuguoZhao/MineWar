#include "option.h"
#include "house.h"

int house_xy_cmp(void *v1, void *v2)
{
	int ret = 1;
	house_t *p1 = v1;
	house_t *p2 = v2;

	if((p1->x == p2->x)
		&&(p1->y == p2->y))
	{
		ret = 0;
	}
	
	return ret;
}

int house_living_cmp(void *v1, void *v2)
{
	int ret = 1;
	house_t *p1 = v1;
	house_t *p2 = v2;

	if(p1->life > p2->life)
	{
		ret = 0;
	}
	
	return ret;
}

int house_demage_cmp(void *v1, void *v2)
{
	int ret = 1;
	house_t *p1 = v1;

	if(p1->life < HOUSE_LIFE)
	{
		ret = 0;
	}
	
	return ret;
}

