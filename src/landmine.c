#include "option.h"
#include "landmine.h"

#define PRICE_PLUG_TIMER	(opt_get_value(OPT_ID_PLUG_PRICE_TIMER))//100
#define PRICE_PLUG_REMOTE	(opt_get_value(OPT_ID_PLUG_PRICE_REMOTE))//200
#define PLUG_TIMER_TIME		(opt_get_value(OPT_ID_PLUG_TIMER_CYCLE))//5000	/*ms*/

#define MINEGUN_FIRE_INTERVAL	4000

#define TAG		"Landmine"

typedef struct{
	int range[POWER_RANGE][POWER_RANGE];
} power_range_t;

static const power_range_t landmine_power[]=
{
	{{{0,	0,	0	},{0,	10,	0	},{0,	0,	0	}}},//MINE_NM
	{{{5,	10,	5	},{10,	10,	10	},{5,	10,	5	}}},//MINE_AE,
	{{{10,	20,	10	},{20,	20,	20	},{10,	20,	10	}}},//MINE_RS,
	{{{0,	5,	0	},{5,	20,	5	},{0,	5,	0	}}},//MINE_AA,
	{{{0,	5,	0	},{5,	40,	5	},{0,	5,	0	}}},//MINE_AT,
};

static const int landmine_price[MINE_MAX]=
{
	5,	//MINE_NM = 0,
	10,	//MINE_AE,
	20,	//MINE_RS,
	20,	//MINE_AA,
	30,	//MINE_AT,
};

static const int minegun_gunshot[7][7]=
{
	{0,0,0,1,0,0,0},
	{0,1,1,1,1,1,0},
	{0,1,1,1,1,1,0},
	{1,1,1,2,1,1,1},
	{0,1,1,1,1,1,0},
	{0,1,1,1,1,1,0},
	{0,0,0,1,0,0,0},
};

int landmine_dispose(dlist_t **list, int x, int y, int id)
{
	int ret = 0;
	landmine_t landmine;
	landmine_t *landmine2;

	landmine.id = id;
	landmine.x = x;
	landmine.y = y;
	landmine.plug = PLUG_NONE;
	landmine.time = 0;
	landmine.exploded = 0;

	landmine2 = dlist_find(*list, &landmine, landmine_xy_cmp);
	
	if(landmine2 == NULL)
	{
		landmine_t *landmine3 = NEW_T(landmine_t);

		memcpy(landmine3, &landmine, sizeof(landmine_t));
		dlist_push_back(list, landmine3);
		ret = 1;
	}

	return ret;
}

void landmine_add_plug(landmine_t * landmine, plug_t plug)
{
	if(plug == PLUG_TIMER)
	{
		landmine->plug = PLUG_TIMER;
		landmine->time = PLUG_TIMER_TIME/TIME_UNIT;
	}
	else if(plug == PLUG_REMOTE)
	{
		landmine->plug = PLUG_REMOTE;
	}
	else
	{
		_LOGE(TAG, "invalid plug! plug=%d\n", plug);
	}
}

int landmine_get_price(int id)
{
	int ret = 0;

	if(id < ARRAY_SIZE(landmine_price))
	{
		//ret = landmine_price[id];
		ret = opt_get_value(OPT_ID_MINE_PRICE_NM+id);
	}
	else
	{
		_LOGE(TAG, "invalid id! id=%d\n", id);
	}
	
	return ret;
}

int landmine_get_recycle_price(int id)
{
	int ret = 0;

	if(id < ARRAY_SIZE(landmine_price))
	{
		//ret = landmine_price[id]*RECYCLE_PERCENT/100;
		ret = opt_get_value(OPT_ID_MINE_PRICE_NM+id)*RECYCLE_PERCENT/100;
	}
	else
	{
		_LOGE(TAG, "invalid id! id=%d\n", id);
	}
	
	return ret;
}

int landmine_get_plug_price(int plug)
{
	int ret = 0;

	if(plug == PLUG_REMOTE)
	{
		ret = PRICE_PLUG_REMOTE;
	}
	else if(plug == PLUG_TIMER)
	{
		ret = PRICE_PLUG_TIMER;
	}
	
	return ret;
}

void landmine_get_power_range(int id, int range[POWER_RANGE][POWER_RANGE])
{
	if(id < MINE_MAX)
	{
		memcpy(range, landmine_power[id].range, sizeof(int)*POWER_RANGE*POWER_RANGE);
	}
	else
	{
		_LOGE(TAG, "invalid id! id=%d\n", id);
	}
}

int landmine_xy_cmp(void *v1, void *v2)
{
	int ret = 1;
	landmine_t *p1 = v1;
	landmine_t *p2 = v2;

	if((p1->x == p2->x)
		&&(p1->y == p2->y))
	{
		ret = 0;
	}
	
	return ret;
}

int landmine_exploded_cmp(void *v1, void *v2)
{
	int ret = 1;
	landmine_t *p1 = v1;
	landmine_t *p2 = v2;

	if(p1->exploded == p2->exploded)
	{
		ret = 0;
	}
	
	return ret;
}

int landmine_time_cmp(void *v1, void *v2)
{
	int ret = 1;
	landmine_t *p1 = v1;
	landmine_t *p2 = v2;

	if(p1->time >= p2->time)
	{
		ret = 0;
	}
	
	return ret;
}

int minegun_dispose(dlist_t **list, int x, int y, int id)
{
	int ret = 0;
	minegun_t minegun;
	minegun_t *minegun2;

	minegun.id = id;
	minegun.x = x;
	minegun.y = y;
	minegun.time = 0;
	minegun.life = MINEGUN_LIFE+MINEGUN_LIFE*id;

	if(id == MINEGUN_0)
	{
		minegun.exposed = 1;
	}
	else
	{
		minegun.exposed = 0;
	}

	minegun2 = dlist_find(*list, &minegun, minegun_xy_cmp);
	
	if(minegun2 == NULL)
	{
		minegun_t *minegun3 = NEW_T(minegun_t);

		memcpy(minegun3, &minegun, sizeof(minegun_t));
		dlist_push_back(list, minegun3);
		ret = 1;
	}

	return ret;
}

void minegun_reload(dlist_t *list, int x, int y)
{
	minegun_t minegun;
	minegun_t *minegun2;

	minegun.x = x;
	minegun.y = y;

	minegun2 = dlist_find(list, &minegun, minegun_xy_cmp);

	if(minegun2 != NULL)
	{
		minegun2->time = MINEGUN_FIRE_INTERVAL/TIME_UNIT;
		minegun2->exposed = 1;
	}
}

int minegun_is_in_gunshot(int mx, int my, int x, int y)
{
	int ret = 0;
	int dx = x-mx;
	int dy = y-my;
	int x0;
	int y0;

	if((dx >= -MINEGUN_GUNSHOT)
		&&(dx <= MINEGUN_GUNSHOT)
		&&(dy >= -MINEGUN_GUNSHOT)
		&&(dy <= MINEGUN_GUNSHOT))
	{
		x0 = dx+MINEGUN_GUNSHOT;
		y0 = dy+MINEGUN_GUNSHOT;

		if(minegun_gunshot[y0][x0] != 0)
		{
			ret = 1;
		}
	}
	
	return ret;
}

int minegun_xy_cmp(void *v1, void *v2)
{
	int ret = 1;
	minegun_t *p1 = v1;
	minegun_t *p2 = v2;

	if((p1->x == p2->x)
		&&(p1->y == p2->y))
	{
		ret = 0;
	}
	
	return ret;
}

int minegun_destoried_cmp(void *v1, void *v2)
{
	int ret = 1;
	minegun_t *p1 = v1;

	if(p1->life <= 0)
	{
		ret = 0;
	}
	
	return ret;
}
