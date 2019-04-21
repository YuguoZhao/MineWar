#include <math.h>
#include "option.h"
#include "map.h"
#include "utils.h"
#include "enemy.h"

#define DISPOSE_OFFSET	(opt_get_value(OPT_ID_DISPOSE_OFFSET))

static void set_default(int index);

static const int gunshot_sb[GUNSHOT_H][GUNSHOT_W]={
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,0},
	{0,0,0,0,1,2,1,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
};

static const int gunshot_gb[GUNSHOT_H][GUNSHOT_W]={
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,2,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
};

static const int gunshot_qc[GUNSHOT_H][GUNSHOT_W]={
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,0},
	{0,0,0,1,1,2,1,1,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
};

static const int gunshot_zj[GUNSHOT_H][GUNSHOT_W]={
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0},
	{0,0,1,1,1,2,1,1,1,0,0},
	{0,0,0,1,1,1,1,1,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
};

static const int gunshot_tk[GUNSHOT_H][GUNSHOT_W]={
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0},
	{0,0,1,0,1,1,1,0,1,0,0},
	{0,0,0,1,1,1,1,1,0,0,0},
	{0,0,1,1,1,1,1,1,1,0,0},
	{0,1,1,1,1,2,1,1,1,1,0},
	{0,0,1,1,1,1,1,1,1,0,0},
	{0,0,0,1,1,1,1,1,0,0,0},
	{0,0,1,0,1,1,1,0,1,0,0},
	{0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
};

static const int* gunshot_tbl[]={
	(const int*)gunshot_sb,	//ENEMY_SB,
	(const int*)gunshot_gb,	//ENEMY_GB,
	(const int*)gunshot_qc,	//ENEMY_QC,
	(const int*)gunshot_zj,	//ENEMY_ZJ,
	(const int*)gunshot_tk,	//ENEMY_TK,
};

static const int enemy_life[]={
	5,	//ENEMY_SB,
	10,	//ENEMY_GB,
	15,	//ENEMY_QC,
	20,	//ENEMY_ZJ,
	40,	//ENEMY_TK,
};

static const int enemy_firing_interval[]={
	1000,	//ENEMY_SB,
	1000,	//ENEMY_GB,
	500,	//ENEMY_QC,
	1500,	//ENEMY_ZJ,
	3000,	//ENEMY_TK,
};

static const int enemy_bullet[]={
	BULLET_BQ,	//ENEMY_SB,
	BULLET_MAX,	//ENEMY_GB,
	BULLET_BQ,	//ENEMY_QC,
	BULLET_ZJ,	//ENEMY_ZJ,
	BULLET_TK,	//ENEMY_TK,
};

static const int bullet_power[]={
	5,	//BULLET_BQ,
	25,	//BULLET_ZJ,
	50,	//BULLET_TK,
	25,	//BULLET_MG
};

static const enemy_queue_item_t enemy_q0[QUEUE_MAX_LEN]=
{
	{ENEMY_SB, 10},
	{ENEMY_GB, 10},
	{ENEMY_QC, 10},
	{ENEMY_ZJ, 10},
	{ENEMY_TK, 10},
	
	{ENEMY_SB, 500},
	{ENEMY_GB, 10},
	{ENEMY_QC, 10},
	{ENEMY_ZJ, 10},
	{ENEMY_TK, 10},

	{ENEMY_SB, 500},
	{ENEMY_GB, 10},
	{ENEMY_QC, 10},
	{ENEMY_ZJ, 10},
	{ENEMY_TK, 10},

	{ENEMY_SB, 500},
	{ENEMY_GB, 10},
	{ENEMY_QC, 10},
	{ENEMY_ZJ, 10},
	{ENEMY_TK, 10},

	{ENEMY_SB, 500},
	{ENEMY_GB, 10},
	{ENEMY_QC, 10},
	{ENEMY_ZJ, 10},
	{ENEMY_TK, 10},

	{ENEMY_SB, 500},
	{ENEMY_GB, 10},
	{ENEMY_QC, 10},
	{ENEMY_ZJ, 10},
	{ENEMY_TK, 10},

	{ENEMY_SB, 500},
	{ENEMY_GB, 10},
	{ENEMY_QC, 10},
	{ENEMY_ZJ, 10},
	{ENEMY_TK, 10},

	{ENEMY_SB, 500},
	{ENEMY_GB, 10},
	{ENEMY_QC, 10},
	{ENEMY_ZJ, 10},
	{ENEMY_TK, 10},

	{ENEMY_SB, 500},
	{ENEMY_GB, 10},
	{ENEMY_QC, 10},
	{ENEMY_ZJ, 10},
	{ENEMY_TK, 10},

	{ENEMY_SB, 500},
	{ENEMY_GB, 10},
	{ENEMY_QC, 10},
	{ENEMY_ZJ, 10},
	{ENEMY_TK, 10},
};

static enemy_queue_item_t enemy_q_tbl[MAP_TOTAL*QUEUE_MAX_LEN];

static double moveStep = 9.0;

void enemy_load(int index, dlist_t **list)
{
	if(index < MAP_TOTAL)
	{
		const enemy_queue_item_t *enemy_q = &enemy_q_tbl[index*QUEUE_MAX_LEN];
		int total = opt_get_value(OPT_ID_EMEMY_Q1_LEN+index);
		int i = 0;
		
		dlist_clear(list);
		
		for(i = 0; i < total; i++)
		{
			enemy_t *enemy = NEW_T(enemy_t);
			enemy->id = enemy_q[i].id;
			enemy->x = -100;
			enemy->y = -100;
			enemy->last_x = -100;
			enemy->last_y = -100;
			enemy->life = enemy_life[enemy->id];
			enemy->direction = ENEMY_DIR_R;
			
			if(i != 0)
			{
				enemy->time = enemy_q[i].interval;
			}
			else
			{
				enemy->time = enemy_q[i].interval+DISPOSE_OFFSET;
			}

			enemy->entry = enemy_q[i].interval%10;
			
			enemy->firing_interval = rand()%(enemy_firing_interval[enemy->id]/TIME_UNIT);
			enemy->delay = 0;
			
			dlist_push_back(list, enemy);
		}
	}
}

void enemy_load_random(int index, dlist_t **list)
{
	if(index < MAP_TOTAL)
	{
		const enemy_queue_item_t *enemy_q = &enemy_q_tbl[index*QUEUE_MAX_LEN];
		int total = opt_get_value(OPT_ID_EMEMY_Q1_LEN+index);
		int i = 0;
		int j;
		int rand_index[100];
		int temp;
		int index;

		for(i = 0; i < total; i++)
		{
			rand_index[i] = i;
		}

		for(i = 0; i < total; i++)
		{
			j = rand()%(total-i)+i;

			temp = rand_index[i];
			rand_index[i] = rand_index[j];
			rand_index[j] = temp;
		}
		
		dlist_clear(list);
		
		for(i = 0; i < total; i++)
		{
			enemy_t *enemy = NEW_T(enemy_t);
			
			index = rand_index[i];
			enemy->id = enemy_q[index].id;
			enemy->x = -100;
			enemy->y = -100;
			enemy->last_x = -100;
			enemy->last_y = -100;
			enemy->life = enemy_life[enemy->id];
			enemy->direction = ENEMY_DIR_R;
			
			if(i != 0)
			{
				enemy->time = enemy_q[i].interval;
			}
			else
			{
				enemy->time = enemy_q[i].interval+DISPOSE_OFFSET;
			}

			enemy->entry = enemy_q[i].interval%10;
			
			enemy->firing_interval = rand()%(enemy_firing_interval[enemy->id]/TIME_UNIT);
			enemy->delay = 0;
			
			dlist_push_back(list, enemy);
		}
	}
}

void enemy_move(enemy_t *enemy, int direction[MAP_H][MAP_W], dlist_t *list)
{
	int x0 = 0;
	int y0 = 0;
	enemy_t enemy2;
	enemy_t *enemy3;
	int direct = 0;

	if(enemy->delay > 0)
	{
		enemy->delay--;
		enemy->moved = 1;
		return;
	}

	if(enemy->moved != 0)
	{
		return;
	}

	direct = direction[enemy->y][enemy->x];

	if(direct == MOVE_R){
		x0 = enemy->x+1;
		y0 = enemy->y;
	}
	else if(direct == MOVE_D){
		x0 = enemy->x;
		y0 = enemy->y+1;
	}
	else if(direct == MOVE_L){
		x0 = enemy->x-1;
		y0 = enemy->y;
	}
	else if(direct == MOVE_U){
		x0 = enemy->x;
		y0 = enemy->y-1;
	}

	enemy2.x = x0;
	enemy2.y = y0;

	enemy3 = dlist_find(list, &enemy2, enemy_xy_cmp);
	
	if((direct != 0)
		&&(enemy3 == NULL))
	{
		int direct2;
		
		enemy->last_x = enemy->x;
		enemy->last_y = enemy->y;
		enemy->x = x0;
		enemy->y = y0;
		enemy->moved = 1;

		direct2 = direction[enemy->y][enemy->x];

		if((direct2 == 0)
			&&(enemy->id == ENEMY_GB)){
			enemy->id = ENEMY_SB;
			enemy->life = enemy_life[enemy->id];
            enemy->firing_interval = rand()%(enemy_firing_interval[enemy->id]/TIME_UNIT);
		}

        if(direction[enemy->y][enemy->x] == MOVE_R){
            enemy->direction = ENEMY_DIR_R;
        }
        else if(direction[enemy->y][enemy->x] == MOVE_U){
            enemy->direction = ENEMY_DIR_U;
        }
        else if(direction[enemy->y][enemy->x] == MOVE_L){
			enemy->direction = ENEMY_DIR_L;
		}
        else if(direction[enemy->y][enemy->x] == MOVE_D){
            enemy->direction = ENEMY_DIR_D;
        }
	}
	else if((direct != 0)
		&&(enemy3 != NULL))
	{
		if((enemy->id != ENEMY_GB)
			&&((enemy3->id < enemy->id)||(enemy3->id == ENEMY_GB))
			&&(enemy3->moved == 0)
			&&(enemy3->delay == 0))
		{
			if((((x0 != enemy->x)&&(y0 == enemy->y))||((x0 == enemy->x)&&(y0 != enemy->y)))
				&&((x0 != enemy->last_x)||(y0 != enemy->last_y)))
			{
				enemy_t tmp;

				memcpy(&tmp, enemy3, sizeof(enemy_t));
				
				tmp.x = enemy->x;
				tmp.y = enemy->y;
				tmp.last_x = enemy->last_x;
				tmp.last_y = enemy->last_y;
				tmp.direction = enemy->direction;
				tmp.moved = 1;

				enemy->x = enemy3->x;
				enemy->y = enemy3->y;
				enemy->last_x = enemy3->last_x;
				enemy->last_y = enemy3->last_y;
				enemy->direction = enemy3->direction;
				enemy->moved = 1;

				memcpy(enemy3, enemy, sizeof(enemy_t));
				memcpy(enemy, &tmp, sizeof(enemy_t));

				return;
			}
		}
	}
}

void enemy_reload(enemy_t *enemy)
{
	enemy->firing_interval = enemy_firing_interval[enemy->id]/TIME_UNIT;
}

void enemy_get_gunshot(int id, int gunshot[GUNSHOT_H][GUNSHOT_W])
{
	if(id < ARRAY_SIZE(gunshot_tbl))
	{
		memcpy(gunshot, gunshot_tbl[id], sizeof(int)*GUNSHOT_H*GUNSHOT_W);
	}
	else
	{
		_LOGE("Enemy", "invalid id! id=%d\n", id);
	}
}

int enemy_get_bullet(int id)
{
	int ret = 0;
	
	if(id < ARRAY_SIZE(enemy_bullet))
	{
		ret = enemy_bullet[id];
	}
	else
	{
		_LOGE("Enemy", "invalid id! id=%d\n", id);
	}

	return ret;
}

int enemy_is_in_gunshot(enemy_t *enemy, int x, int y)
{
	int ret = 0;
	int gunshot[GUNSHOT_H][GUNSHOT_W];
	int x0;
	int y0;

	x0 = x-enemy->x;
	y0 = y-enemy->y;

	if(((x0 >= -GUNSHOT_C)&&(x0 <= GUNSHOT_C))
		&&((y0 >= -GUNSHOT_C)&&(y0 <= GUNSHOT_C)))
	{
		enemy_get_gunshot(enemy->id, gunshot);
		
		if((gunshot[(y0+GUNSHOT_C)][(x0+GUNSHOT_C)] == 1)
			||(gunshot[(y0+GUNSHOT_C)][(x0+GUNSHOT_C)] == 2))
		{
			ret = 1;
		}
	}
	
	return ret;
}

int enemy_xy_cmp(void *v1, void *v2)
{
	int ret = 1;
	enemy_t *p1 = v1;
	enemy_t *p2 = v2;

	if((p1->x == p2->x)
		&&(p1->y == p2->y))
	{
		ret = 0;
	}
	
	return ret;
}

int enemy_dead_cmp(void *v1, void *v2)
{
	int ret = 1;
	enemy_t *p1 = v1;

	if(p1->life <= 0)
	{
		ret = 0;
	}
	
	return ret;
}

int enemy_over_cmp(void *v1, void *v2)
{
	int ret = 1;
	enemy_t *p1 = v1;

	if(p1->time >= ENEMY_DEAD_TIME)
	{
		ret = 0;
	}
	
	return ret;
}

void bullet_set_move_step(double step)
{
	moveStep = step;
}

void bullet_add(dlist_t **list, int id, int sx, int sy, int ex, int ey)
{
	bullet_t *bullet = NEW_T(bullet_t);

	bullet->id = id;
	bullet->x = sx;
	bullet->y = sy;
	bullet->ex = ex;
	bullet->ey = ey;
	bullet->time = 0;
	bullet->state = 0;
	
	dlist_push_back(list, bullet);
}

void bullet_move(bullet_t *bullet)
{
	if(bullet->x == bullet->ex)
	{
		if(bullet->y >= bullet->ey)
		{
			if(bullet->y-bullet->ey > moveStep)
			{
				bullet->y -= (int)moveStep;
			}
			else
			{
				bullet->y = bullet->ey;
			}
		}
		else
		{
			if(bullet->ey-bullet->y > moveStep)
			{
				bullet->y += (int)moveStep;
			}
			else
			{
				bullet->y = bullet->ey;
			}
		}
	}
	else
	{
		if((bullet->ex-bullet->x)*(bullet->ex-bullet->x)
			+(bullet->ey-bullet->y)*(bullet->ey-bullet->y)
			<= moveStep*moveStep)
		{
			bullet->x = bullet->ex;
			bullet->y = bullet->ey;
		}
		else
		{
			double r;
			double cos;
			double sin;

			r = sqrt((bullet->ex-bullet->x)*(bullet->ex-bullet->x)
				+(bullet->ey-bullet->y)*(bullet->ey-bullet->y));
			cos = (bullet->ex-bullet->x)/r;
			sin = (bullet->ey-bullet->y)/r;

			bullet->x += (int)(moveStep*cos);
			bullet->y += (int)(moveStep*sin);
		}
	}

	bullet->state++;
	bullet->state %= 4;
}

int bullet_get_power(int id)
{
	int ret = 0;
	
	if(id < ARRAY_SIZE(bullet_power))
	{
		ret = bullet_power[id];
	}
	else
	{
		_LOGE("Bullet", "invalid bullet id! id=%d\n", id);
	}
	
	return ret;
}

int bullet_end_cmp(void *v1, void *v2)
{
	int ret = 1;
	bullet_t *p1 = v1;

	if((p1->x == p1->ex)
		&&(p1->y == p1->ey))
	{
		ret = 0;
	}
	
	return ret;
}

int bullet_over_cmp(void *v1, void *v2)
{
	int ret = 1;
	bullet_t *p1 = v1;

	if(p1->time >= BULLET_EXPLOSE_STEP)
	{
		ret = 0;
	}
	
	return ret;
}

void set_default(int index)
{
	if((index >= 0)&&(index < MAP_TOTAL))
	{
		memcpy(&enemy_q_tbl[index*QUEUE_MAX_LEN], enemy_q0,
			sizeof(enemy_queue_item_t)*QUEUE_MAX_LEN
		);
	}
}

void enemy_load_queues(void)
{
	int i;
	char file_name[256];
	char path[256];
	
	for(i = 0; i < MAP_TOTAL; i++)
	{
		set_default(i);
		sprintf(file_name, "Queue%d.dat", (i+1));
		Utils_getAssetsPath(file_name, path);
		enemy_queue_load(path, &enemy_q_tbl[i*QUEUE_MAX_LEN]);
	}
}

void enemy_queue_load(const char *file_name, enemy_queue_item_t *queue)
{
	FILE* fp = NULL;
	
	fp = fopen(file_name, "rb");
	
	if(fp != NULL)	
	{
		fread(queue, sizeof(enemy_queue_item_t)*QUEUE_MAX_LEN, 1, fp);
		fclose(fp);
	}
	else
	{
		_LOGE("Enemy", "queue load failed! file=%s\n", file_name);
	}
}

void enemy_queue_save(const char *file_name, enemy_queue_item_t *queue)
{
	FILE* fp = NULL;

	fp = fopen(file_name, "wb");
	
	if(fp != NULL)
	{
		fwrite(queue, sizeof(enemy_queue_item_t)*QUEUE_MAX_LEN, 1, fp);
		fclose(fp);	
	}
	else
	{
		_LOGE("Enemy", "queue save failed! file=%s\n", file_name);
	}
}

void enemy_queue_get(int index, int q[QUEUE_MAX_LEN][2])
{
	int i;
	enemy_queue_item_t *p;

	if((index < 0) || (index >= MAP_TOTAL))
	{
		_LOGE("Enemy", "invalid index! index=%s\n", index);
		return;
	}
	
	p = &enemy_q_tbl[index*QUEUE_MAX_LEN];
	
	for(i = 0; i < QUEUE_MAX_LEN; i++){
		q[i][0] = p[i].id;
		q[i][1] = p[i].interval;
	}
}

