#include "utils.h"
#include "option.h"
#include "war.h"

#define	TAG					"War"

#define	CHK_EQUAL			0
#define	CHK_NOT_EQUAL		1
#define	CHK_MORE			2
#define	CHK_LESS			3

#define PLANT_STAR			3
#define MONEY_OVER			5

#define ENEMY_DISPOSE_CYCLE		(opt_get_value(OPT_ID_ENEMY_DISPOSE_CYCLE))
#define ENEMY_MOVE_CYCLE		(opt_get_value(OPT_ID_ENEMY_MOVE_CYCLE))
#define BULLET_MOVE_CYCLE		(opt_get_value(OPT_ID_BULLET_MOVE_CYCLE))
#define INIT_MONEY				(opt_get_value(OPT_ID_INITIAL_MONEY))

static int enemy_dispose(void);
static int enemy_queue_move(void);
static void landmine_timer_count(void);
static void plant_grow(void);
static void landmine_explosion_check(void);
static void explosed_landmine_check(void);
static void dead_enemy_check(void);
static void enemy_fire_check(void);
static void over_check(void);
static void create_house(void);
static void create_enemy_queue(int map_id);

static void explose_landmine(landmine_t *landmine);
static void delete_exploded_landmine(void);
static void delete_destoried_minegun(void);
static void delete_dead_enemy(void);
static void bullet_list_move(void);
static void bullet_hit_check(void);
static void bullet_explose_check(void);
static void enemy_fire(enemy_t *enemy);
static int find_target(enemy_t *enemy, int *x, int *y);

static void update_game_record(void);
static void update_allstar_record(void);
static void update_total_record(int finished, int won);
static void update_star_progress(void);
static void update_stars(void);

static const int explosion_pri[MINE_MAX][ENEMY_MAX]=
{
//	SB,	GB,	QC,	ZJ,	TK,
	{1,	0,	1,	1,	1},//MINE_NM = 0,
	{1,	1,	1,	1,	1},//MINE_AE,
	{1,	0,	1,	1,	1},//MINE_RS,
	{0,	0,	0,	1,	1},//MINE_AA,
	{0,	0,	0,	0,	1},//MINE_AT,
};

static const int kill_enemy_score[]=
{
	5,	//ENEMY_SB,
	10,	//ENEMY_GB,
	15,	//ENEMY_QC,
	20,	//ENEMY_ZJ,
	40,	//ENEMY_TK,
};

static const int stars_target[]=
{
	1		,CHK_EQUAL	,	//[0]获得CLASSIC第一关胜利
	1		,CHK_EQUAL	,	//[1]CLASSIC某一关三星通关
	10		,CHK_EQUAL	,	//[2]获得CLASSIC前(N)关胜利
	36		,CHK_EQUAL	,	//[3]获得CLASSIC所有(N)关胜利
	10		,CHK_MORE	,	//[4]第5关剩余成熟庄稼数超过(N)
	10		,CHK_MORE	,	//[5]第15关剩余成熟庄稼数超过(N)
	4		,CHK_MORE	,	//[6]一次消灭(N)个敌人
	9		,CHK_MORE	,	//[7]一次消灭(N)个敌人
	14		,CHK_MORE	,	//[8]一次消灭(N)个敌人
	1000	,CHK_LESS	,	//[9]第6关三星过关花费低于(N)
	107		,CHK_MORE	,	//[10]全三星通过CLASSIC全部关卡
	100000	,CHK_MORE	,	//[11]庄稼总产出超过(N)万分
	100		,CHK_MORE	,	//[12]使用的总MINE_GUN数超过(N)
	200		,CHK_MORE	,	//[13]使用的LB炸弹数超过(N)
	1000000	,CHK_MORE	,	//[14]游戏总得分超过(N)
	1000	,CHK_MORE	,	//[15]游戏总得分超过(N)
};

static const char * const game_name_table[]={
    "01-Beginning",
    "02-Direct Line",
    "03-Ring",
    "04-Short Line",
    "05-Vertical Double",
    "06-Horizon Double",
    "07-Forest",
    "08-Lake Bridge",
    "09-51515",
    "10-Pulse Ring",
    "11-Pulse",
    "12-V2A",
    "13-SU",
    "14-S",
    "15-SC",
    "16-Mountain Foot",
    "17-Ts",
    "18-Stage",
    "19-Big Stage",
    "20-Rebound",
    "21-Double",
    "22-Shadow",
    "23-Two Half Ring",
    "24-Sin Wave",
    "25-Horizon Symmetry",
    "26-Vertical Symmetry",
    "27-High Pulse",
    "28-Wing",
    "29-Arrow",
    "30-Double Ring",
    "31-Leave&Back",
    "32-2x2",
    "33-Triple",
    "34-Twist",
    "35-Vortex",
    "36-X"
};

static int GRID_W = 71;

static dlist_t *enemy_list = NULL;
static dlist_t *dead_enemy_list = NULL;
static dlist_t *bullet_list = NULL;
static dlist_t *landmine_list = NULL;
static dlist_t *minegun_list = NULL;
static dlist_t *exploded_mine_list = NULL;
static dlist_t *plant_list = NULL;
static dlist_t *house_list = NULL;

static int over_flag = OVER_NONE;
static int game_money = 0;
static int map_data[MAP_H][MAP_W];
static int move_direction[MAP_H][MAP_W];
static point_t entrances[4];
static int entry_total = 0;
static unsigned int tick_counter = 0;
static int map_index = 0;
static total_record_t total_record = {0};
static record_t game_record[MAP_TOTAL];
static total_record_t total_record_bak = {0};
static record_t game_record_bak[MAP_TOTAL];
static int enemy_total = 0;
static game_data_t game_data = {0};
static int game_stars[GAME_STAR_TOTAL];
static int stars_progress[GAME_STAR_TOTAL];

void game_start(int map)
{
	if((map < 0)||(map >= MAP_TOTAL)){
		_LOGE(TAG, "invalid map index!, map=%d\n", map);
		return;
	}
	
	_LOGI(TAG, "game start, map=%d\n", map);
	
	tick_counter = 0;
	map_index = map;
	memset(&game_data, 0, sizeof(game_data_t));
	dlist_clear(&enemy_list);
	dlist_clear(&dead_enemy_list);
	dlist_clear(&bullet_list);
	dlist_clear(&landmine_list);
	dlist_clear(&minegun_list);
	dlist_clear(&exploded_mine_list);
	dlist_clear(&plant_list);
	dlist_clear(&house_list);

	game_money = INIT_MONEY;
	over_flag = OVER_NONE;
	
	map_fill(map_index, map_data, entrances, &entry_total);
	map_get_move_direction(map_index, move_direction);
	create_enemy_queue(map_index);
	create_house();
	enemy_total = dlist_get_size(enemy_list);
}

void game_end(void)
{
	_LOGD(TAG, "game end\n");
	
	dlist_clear(&enemy_list);
	dlist_clear(&dead_enemy_list);
	dlist_clear(&bullet_list);
	dlist_clear(&landmine_list);
	dlist_clear(&minegun_list);
	dlist_clear(&exploded_mine_list);
	dlist_clear(&plant_list);
	dlist_clear(&house_list);
	
	if(over_flag == OVER_NONE)
	{
		update_total_record(0, 0);
	}
}

void game_tick(void)		/* cycle=10ms */
{
	int last_killed = game_data.killed_enemy;
	int moved = 0;
	int disposed = 0;
	
	tick_counter++;

	if(tick_counter%(ENEMY_MOVE_CYCLE/TIME_UNIT) == 0)
	{
		moved = enemy_queue_move();
	}

	if(tick_counter%(ENEMY_DISPOSE_CYCLE/TIME_UNIT) == 0)
	{
		disposed = enemy_dispose();
	}

	if(moved||disposed)
	{
		landmine_explosion_check();
	}
	
	landmine_timer_count();
	plant_grow();

	if(tick_counter%(BULLET_MOVE_CYCLE/TIME_UNIT) == 0)
	{
		bullet_list_move();
	}

	enemy_fire_check();
	
	if(tick_counter%TIME_UNIT == 0)
	{
		explosed_landmine_check();
		dead_enemy_check();
		bullet_explose_check();
	}
	
	bullet_hit_check();
	delete_destoried_minegun();
	over_check();

	if(game_data.killed_enemy-last_killed > game_data.max_killed_number)
	{
		game_data.max_killed_number = game_data.killed_enemy-last_killed;
		_LOGD(TAG, "update max_killed_number, max_killed_number=%d\n", game_data.max_killed_number);
	}
}

static int enemy_dispose(void)
{
	dlist_t *p = enemy_list;
	enemy_t *enemy;
	int found = 0;
	int ret = 0;
	
	while(p != NULL)
	{
		enemy = p->data;

		if(enemy->time > 0)
		{
			enemy->time--;

			if(enemy->time == 0)	//time out
			{
				enemy_t enemy2;
				int index = enemy->entry%entry_total;

				enemy2.x = entrances[index].x;
				enemy2.y = entrances[index].y;
				
				if(NULL == dlist_find(enemy_list, &enemy2, enemy_xy_cmp))
				{
					enemy->x = entrances[index].x;
					enemy->y = entrances[index].y;
					enemy->last_x = -100;
					enemy->last_y = -100;

					ret = 1;

					if(move_direction[enemy->y][enemy->x] == MOVE_L)
					{
						enemy->direction = ENEMY_DIR_L;
					}
					else if(move_direction[enemy->y][enemy->x] == MOVE_R)
					{
						enemy->direction = ENEMY_DIR_R;
					}
					else if(move_direction[enemy->y][enemy->x] == MOVE_U)
					{
						enemy->direction = ENEMY_DIR_U;
					}
					else{
						enemy->direction = ENEMY_DIR_D;
					}
				}
				else
				{
					enemy->time = 1;
				}
			}

			found = 1;
			break;
		}
		
		p = p->next;
	}

	return ret;
}

static void landmine_timer_count(void)
{
	dlist_t *p = landmine_list;
	landmine_t *landmine;
	minegun_t *minegun;
	
	while(p != NULL)
	{
		landmine = p->data;

		if(landmine->time > 0)
		{
			landmine->time--;

			if(landmine->time == 0)	//time out
			{
				explose_landmine(landmine);
			}
			
			break;
		}
		else
		{
			landmine->time = -1;;
		}

		p = p->next;
	}

	delete_dead_enemy();
	delete_exploded_landmine();

	p = minegun_list;

	while(p != NULL)
	{
		minegun = p->data;

		if(minegun->time > 0)
		{
			minegun->time--;
		}

		p = p->next;
	}
}

static void plant_grow(void)
{
	dlist_t *p = plant_list;
	plant_t *plant;
	
	p = plant_list;
	
	while(p != NULL)
	{
		plant = p->data;

		if(plant->water > 0)
		{
			plant->water--;
			
			if(plant->time > 0)
			{
				plant->time--;

				if(plant->time == 0)	//time out
				{
					if(plant->state < PLANT_STATE_MATURE)
					{
						plant->state++;
						plant->water = 0;
						plant->time = PLANT_GROW_TIME/TIME_UNIT;
					}
				}
			}
		}
		
		p = p->next;
	}
}

static int enemy_queue_move(void)
{
	dlist_t *p = enemy_list;
	enemy_t *enemy;
	int ret = 0;

	while(p != NULL)
	{
		enemy = p->data;
		enemy->moved = 0;
		p = p->next;
	}

	p = enemy_list;
	
	while(p != NULL)
	{
		enemy = p->data;
		
		if(enemy->x < 0)
		{
			break;
		}

		ret = 1;

		enemy_move(enemy, move_direction, enemy_list);
		
		p = p->next;
	}

	return ret;
}

static void landmine_explosion_check(void)
{
	dlist_t *p = enemy_list;
	landmine_t *landmine;
	enemy_t *enemy2;
	enemy_t enemy;
	
	p = landmine_list;
	
	while(p != NULL)
	{
		landmine = p->data;

		enemy.x = landmine->x;
		enemy.y = landmine->y;

		enemy2 = dlist_find(enemy_list, &enemy, enemy_xy_cmp);

		if(enemy2 != NULL)
		{
			if(0 != explosion_pri[landmine->id][enemy2->id])
			{
				explose_landmine(landmine);
			}
			else
			{
				if(/*(landmine->id == LANDMINE_NM)
					&&*/(enemy2->id == ENEMY_GB))
				{
					landmine->exploded = 1;
				}
			}
		}

		p = p->next;
	}

	delete_dead_enemy();
	delete_exploded_landmine();
}

static void explosed_landmine_check(void)
{
	dlist_t *p = exploded_mine_list;
	landmine_t *landmine;
	
	while(p != NULL)
	{
		landmine = p->data;

		if(landmine->time < LANDMINE_EXPLOSE_STEP)
		{
			landmine->time++;
		}

		p = p->next;
	}
}

static void dead_enemy_check(void)
{
	dlist_t *p = dead_enemy_list;
	enemy_t *enemy;
	
	while(p != NULL)
	{
		enemy = p->data;

		if(enemy->time < ENEMY_DEAD_TIME)
		{
			enemy->time++;
		}

		p = p->next;
	}
}

static void update_game_record(void)
{
	if(game_data.left_plant > game_record[map_index].c_max_left_plant)
	{
		game_record[map_index].c_max_left_plant = game_data.left_plant;
	}
}

static void update_allstar_record(void)
{
	if(game_data.left_plant > game_record[map_index].c_as_max_left_plant)
	{
		game_record[map_index].c_as_max_left_plant = game_data.left_plant;
	}

	if(game_data.cost < game_record[map_index].c_as_min_cost)
	{
		game_record[map_index].c_as_min_cost = game_data.cost;
	}
}

static void update_total_record(int finished, int won)
{
	_LOGD(TAG, "update_total_record, finished=%d, won=%d\n", finished, won);

	if(finished)
	{
		total_record.game++;
		
		if(won)
		{
			total_record.win++;
		}
	}
	
	total_record.cost += game_data.cost;
	total_record.plant += game_data.plant;
	total_record.money += game_data.money;
	total_record.score += game_data.score;
	total_record.mine_nm += game_data.mine_nm;
	total_record.mine_ae += game_data.mine_ae;
	total_record.mine_rs += game_data.mine_rs;
	total_record.mine_aa += game_data.mine_aa;
	total_record.mine_at += game_data.mine_at;
	total_record.mine_mg += game_data.mine_mg;
}

static void over_check(void)
{
	int last_over_flag = over_flag;
	
	if(game_record[map_index].max_killed_number < game_data.max_killed_number)
	{
		_LOGD(TAG, "update record max_killed_number, max_killed_number=%d\n", game_data.max_killed_number);
		game_record[map_index].max_killed_number = game_data.max_killed_number;
	}
	
	if(enemy_list == NULL)
	{
		if(dead_enemy_list == NULL)
		{
			if(over_flag != OVER_WIN)
			{
				record_t record;
				int all_star = 1;

				memcpy(&record, &game_record[map_index], sizeof(record_t));
				
				record.star_victory = 1;
				
				if(game_is_plants_star())
				{
					record.star_plant = 1;
				}
				else
				{
					all_star = 0;
				}

				if(game_is_all_house_ok())
				{
					record.star_house = 1;
				}
				else
				{
					all_star = 0;
				}

				game_data.left_plant = dlist_get_size(plant_list);

				update_game_record();

				if(all_star)
				{
					update_allstar_record();
				}
				
				if(0 != memcmp(&game_record[map_index], &record, sizeof(record_t)))
				{
					game_record[map_index].star_victory |= record.star_victory;
					game_record[map_index].star_plant |= record.star_plant;
					game_record[map_index].star_house |= record.star_house;
				}

				update_total_record(1, 1);
			}
			
			over_flag = OVER_WIN;
			_LOGD(TAG, "over win\n");
		}
	}
	else
	{
		house_t house;

		house.life = 0;
		
		if(NULL == dlist_find(house_list, &house, house_living_cmp))
		{
			if(over_flag != OVER_LOSE)
			{
				update_total_record(1, 0);
			}

			over_flag = OVER_LOSE;
			_LOGD(TAG, "over lose(normal)\n");
		}
		else
		{
			over_flag = OVER_NONE;
			
			if((plant_list == NULL)&&(landmine_list == NULL)
                &&(minegun_list == NULL)&&(game_money < MONEY_OVER)){
				over_flag = OVER_LOSE;
				_LOGD(TAG, "over lose(no money)\n");
			}

			if((last_over_flag != OVER_LOSE)
				&&(over_flag == OVER_LOSE)){
                update_game_record();
				update_total_record(1, 0);
			}
		}
	}
}

static void enemy_fire_check(void)
{
	dlist_t *p = enemy_list;
	enemy_t *enemy;

	while(p != NULL)
	{
		enemy = p->data;

		if(enemy->x < 0)
		{
			break;
		}
		
		if(enemy->firing_interval > 0)
		{
			enemy->firing_interval--;
		}
		else
		{
			enemy_fire(enemy);
		}
		
		p = p->next;
	}
}

static void delete_exploded_landmine(void)
{
	landmine_t landmine;
	
	landmine.exploded = 1;
	landmine.time = LANDMINE_EXPLOSE_STEP;

	while(0 != dlist_del(&landmine_list, &landmine, landmine_exploded_cmp))
	{
	}

	while(0 != dlist_del(&exploded_mine_list, &landmine, landmine_time_cmp))
	{
	}
}

static void delete_destoried_minegun(void)
{
	while(0 != dlist_del(&minegun_list, NULL, minegun_destoried_cmp))
	{
	}
}

static void delete_dead_enemy(void)
{
	enemy_t *enemy2;

	enemy2 = dlist_find(enemy_list, NULL, enemy_dead_cmp);
	
	while(enemy2 != NULL)
	{
		enemy_t *enemy3 = NEW_T(enemy_t);
		_LOGD(TAG, "delete dead enemy, x=%d, y=%d, id=%d\n",
			enemy2->x, enemy2->y, enemy2->id);
		memcpy(enemy3, enemy2, sizeof(enemy_t));
		enemy3->time = 0;
		game_data.score += kill_enemy_score[enemy2->id];
		game_data.killed_enemy++;
		dlist_push_back(&dead_enemy_list, enemy3);
		dlist_del(&enemy_list, NULL, enemy_dead_cmp);
		
		enemy2 = dlist_find(enemy_list, NULL, enemy_dead_cmp);
	}
	
	while(dlist_del(&dead_enemy_list, NULL, enemy_over_cmp))
	{
	}
}

static void bullet_list_move(void)
{
	dlist_t *p = bullet_list;
	bullet_t *bullet;

	while(p != NULL)
	{
		bullet = p->data;
		bullet_move(bullet);
		p = p->next;
	}
}

static void bullet_hit_check(void)
{
	bullet_t *bullet2;
	int power;
	house_t house;
	house_t *house2;
	plant_t plant;
	minegun_t minegun;
	minegun_t *minegun2;
	int x;
	int y;

	bullet2 = dlist_find(bullet_list, NULL, bullet_end_cmp);

	while(bullet2 != NULL)
	{
		if(bullet2->time < BULLET_EXPLOSE_STEP)
		{
			return;
		}

		x = bullet2->x/GRID_W;
		y = bullet2->y/GRID_W;

		_LOGD(TAG, "bullet hit, x=%d, y=%d, id=%d\n", x, y, bullet2->id);
		
		power = bullet_get_power(bullet2->id);

		if(bullet2->id < BULLET_MG)
		{
			house.x = x;
			house.y = y;
			house2 = dlist_find(house_list, &house, house_xy_cmp);
			
			minegun.x = x;
			minegun.y = y;
			minegun2 = dlist_find(minegun_list, &minegun, minegun_xy_cmp);
			
			if(house2 != NULL)
			{
				if(house2->life > power)
				{
					house2->life -= power;
				}
				else
				{
					house2->life = 0;
				}
			}
			else if(minegun2 != NULL)
			{
				if(minegun2->life > power)
				{
					minegun2->life -= power;
				}
				else
				{
					minegun2->life = 0;
				}
			}
			else
			{
				plant.x = x;
				plant.y = y;
				
				dlist_del(&plant_list, &plant, plant_xy_cmp);
			}
		}
		else
		{
			int i;
			int j;
			int power_range[POWER_RANGE][POWER_RANGE];
			int x0 = x;
			int y0 = y;
			
			landmine_get_power_range(MINE_RS, power_range);
			
			for(i = 0; i < POWER_RANGE; i++)
				for(j = 0; j < POWER_RANGE; j++)
			{
				x = x0+j-1;
				y = y0+i-1;
				
				if(map_is_in_range(x, y))
				{
					enemy_t enemy;
					enemy_t *enemy2;
					
					enemy.x = x;
					enemy.y = y;
					
					enemy2 = dlist_find(enemy_list, &enemy, enemy_xy_cmp);

					if(NULL != enemy2)
					{
						enemy2->life -= power_range[i][j];

						if(power_range[i][j] > 0)
						{
							enemy2->delay = DEMAGE_DELAY;
						}
					}
				}
			}
		}
		
		dlist_del(&bullet_list, NULL, bullet_over_cmp);
		
		bullet2 = dlist_find(bullet_list, NULL, bullet_end_cmp);
	}
}

static void bullet_explose_check(void)
{
	dlist_t *p = bullet_list;
	bullet_t *bullet;

	while(p != NULL)
	{
		bullet = p->data;
		
		if((bullet_end_cmp(bullet, NULL)== 0)
			&&(bullet->time < BULLET_EXPLOSE_STEP))
		{
			bullet->time++;
		}

		p = p->next;
	}
}

static void enemy_fire(enemy_t *enemy)
{
	int x = 0;
	int y = 0;
	
	if(find_target(enemy, &x, &y))
	{
		int bullet_id = enemy_get_bullet(enemy->id);

		_LOGD(TAG, "enemy fire, x=%d, y=%d, id=%d\n", x, y, enemy->id);
		
		bullet_add(&bullet_list, bullet_id, 
			enemy->x*GRID_W+GRID_W/2, enemy->y*GRID_W+GRID_W/2, 
			x*GRID_W+GRID_W/2, y*GRID_W+GRID_W/2
		);

		enemy_reload(enemy);
	}
}

static int find_target(enemy_t *enemy, int *x, int *y)
{
	int ret = 0;
	int i;
	int j;
	int gunshot[GUNSHOT_H][GUNSHOT_W];
	int found = 0;
	int x0 = 0;
	int y0 = 0;
	house_t *house;
	plant_t *plant;
	minegun_t *minegun;
	int map[MAP_H][MAP_W];
	dlist_t *p;
	int count = 0;
	point_t target[MAP_W*MAP_H];

	memset(map, 0, sizeof(map));

	p = house_list;
	
	while(p != NULL)
	{
		house = p->data;

		if(house->life > 0)
		{
			map[house->y][house->x] = 1;
		}
		
		p = p->next;
	}

	p = minegun_list;
	
	while(p != NULL)
	{
		minegun = p->data;

		if((minegun->life > 0)
			&&(minegun->exposed != 0))
		{
			map[minegun->y][minegun->x] = 2;
		}
		
		p = p->next;
	}

	p = plant_list;
	
	while(p != NULL)
	{
		plant = p->data;
		
		if(plant->state != PLANT_STATE_SEED)
		{
			map[plant->y][plant->x] = 3;
		}
		
		p = p->next;
	}

	enemy_get_gunshot(enemy->id, gunshot);

	for(i = 0; (i < GUNSHOT_H)&&(! found); i++)
	{
		for(j = 0; (j < GUNSHOT_W)&&(! found); j++)
		{
			if(gunshot[i][j] != 1)
			{
				continue;
			}
			
			x0 = enemy->x-GUNSHOT_C+j;
			y0 = enemy->y-GUNSHOT_C+i;

			if(! map_is_in_range(x0, y0))
			{
				continue;
			}
			
			if(map[y0][x0] != 0)
			{
				target[count].x = x0;
				target[count].y = y0;
				count++;
			}
		}
	}

	if(count > 0)
	{
		int index = rand()%count;
		_LOGD(TAG, "find target, count=%d, x=%d, y=%d\n", 
			count, target[index].x, target[index].y);
		
		*x = target[index].x;
		*y = target[index].y;
		ret = 1;
	}
	
	return ret;
}

static void explose_landmine(landmine_t *landmine)
{
	int i;
	int j;
	int x;
	int y;
	int power_range[POWER_RANGE][POWER_RANGE];
	landmine_t *landmine3 = NEW_T(landmine_t);

	_LOGD(TAG, "explose landmine, x=%d, y=%d, id=%d\n", 
		landmine->x, landmine->y, landmine->id);

	landmine_get_power_range(landmine->id, power_range);
	landmine->exploded = 1;

	if(landmine->id == MINE_NM)
	{
		game_data.mine_nm++;
	}
	else if(landmine->id == MINE_AE)
	{
		game_data.mine_ae++;
	}
	else if(landmine->id == MINE_RS)
	{
		game_data.mine_rs++;
	}
	else if(landmine->id == MINE_AA)
	{
		game_data.mine_aa++;
	}
	else if(landmine->id == MINE_AT)
	{
		game_data.mine_at++;
	}
	
	memcpy(landmine3, landmine, sizeof(landmine_t));
	landmine3->time = 0;
	
	dlist_push_back(&exploded_mine_list, landmine3);

	for(i = 0; i < POWER_RANGE; i++)
		for(j = 0; j < POWER_RANGE; j++)
	{
		x = landmine->x+j-1;
		y = landmine->y+i-1;

		if(map_is_in_range(x, y))
		{
			enemy_t enemy;
			enemy_t *enemy2;
			
			enemy.x = x;
			enemy.y = y;
			
			enemy2 = dlist_find(enemy_list, &enemy, enemy_xy_cmp);

			if(NULL != enemy2)
			{
				enemy2->life -= power_range[i][j];

				if(power_range[i][j] > 0)
				{
					enemy2->delay = DEMAGE_DELAY;
				}
			}
		}
	}

	if(landmine->id == MINE_RS)
	{
		static const int offset[4][2]= 
		{
			{-1, 0},
			{0, -1},
			{0, +1},
			{+1, 0},
		};

		landmine_t *landmine2;
		landmine_t landmine3;

		for(i = 0; i < 4; i++)
		{
			landmine3.x = landmine->x+offset[i][0];
			landmine3.y = landmine->y+offset[i][1];
			landmine2 = dlist_find(landmine_list, &landmine3, landmine_xy_cmp);
			
			if((landmine2 != NULL)
				&&(map_is_in_range(landmine3.x, landmine3.y)))
			{
				if((landmine2->id == MINE_RS)
					&&(landmine2->exploded == 0))
				{
					explose_landmine(landmine2);
				}
			}
		}
	}
}

static void create_house(void)
{
	int i;
	int j;

	for(i = 0; i < MAP_H; i++)
	{
		for(j = 0; j < MAP_W; j++)
		{
			if(map_data[i][j] == FIELD_HOUSE)
			{
				house_t *house = NEW_T(house_t);

				house->x = j;
				house->y = i;
				house->life = HOUSE_LIFE;
				
				dlist_push_back(&house_list, house);
			}
		}
	}
}

static void create_enemy_queue(int map_id)
{
	if(opt_get_value(OPT_ID_QUEUE_RANDOM) == 0)
	{
		enemy_load(map_id, &enemy_list);
	}
	else
	{
		enemy_load_random(map_id, &enemy_list);
	}
}

int game_is_in_gunshot(int x, int y)
{
	int ret = 0;
	dlist_t *p = enemy_list;
	enemy_t *enemy;
	
	while(p != NULL)
	{
		enemy = p->data;

		if(enemy_is_in_gunshot(enemy, x, y))
		{
			ret = 1;
			break;
		}
		
		p = p->next;
	}
	
	return ret;
}

void game_get_danger_range(int map[MAP_H][MAP_W])
{
	int gunshot[GUNSHOT_H][GUNSHOT_W];
	int x;
	int y;
	int i;
	int j;
	dlist_t *p = enemy_list;
	enemy_t *enemy;

	memset(map, 0, sizeof(int)*MAP_H*MAP_W);

	while(p != NULL)
	{
		enemy = p->data;

		if(enemy->x < 0)
		{
			break;
		}
		
		enemy_get_gunshot(enemy->id, gunshot);
		
		for(i = 0; i < GUNSHOT_H; i++)
		{
			for(j = 0; j < GUNSHOT_W; j++)
			{
				x = enemy->x-GUNSHOT_C+j;
				y = enemy->y-GUNSHOT_C+i;

				if(map_is_in_range(x, y))
				{
					if((gunshot[i][j] == 1)
						||(gunshot[i][j] == 2))
					{
						map[y][x] = 1;
					}
				}
			}
		}

		p = p->next;
	}
}

void game_add_plant(int x, int y)
{
	if(game_money >= PLANT_PRICE)
	{
		plant_t *plant;

		_LOGD(TAG, "add plant, x=%d, y=%d\n", x, y);
		
		plant = NEW_T(plant_t);
		plant->id = 0;
		plant->x = x;
		plant->y = y;
		plant->water = PLANT_WATER/TIME_UNIT;
		plant->time = PLANT_GROW_TIME/TIME_UNIT;
		plant->state = PLANT_STATE_SEED;
		
		dlist_push_back(&plant_list, plant);
		
		game_money -= PLANT_PRICE;
		game_data.cost += PLANT_PRICE;
	}
	else
	{
		_LOGI(TAG, "add plant, no enough money!\n");
	}
}

void game_add_plug(int x, int y, int plug)
{
	int plug_price = landmine_get_plug_price(plug);

	if(game_money >= plug_price)
	{
		landmine_t landmine;
		landmine_t *landmine2;
		
		landmine.x = x;
		landmine.y = y;
		
		landmine2 = dlist_find(landmine_list, &landmine, landmine_xy_cmp);

		if(landmine2 != NULL)
		{
			if(landmine2->plug == PLUG_NONE)
			{
				_LOGD(TAG, "add plug, x=%d, y=%d\n", x, y);
				landmine_add_plug(landmine2, plug);
				game_money -= plug_price;
				game_data.cost += plug_price;
			}
		}
	}
	else
	{
		_LOGI(TAG, "add plug, no enough money!\n");
	}
}

void game_add_landmine(int x, int y, int id)
{
	int landmine_price = landmine_get_price(id);
	
	if((id < MINE_MAX)
		&&(game_money >= landmine_price))
	{
		if(map_is_mining_enable(x, y, id, map_data))
		{
			if(landmine_dispose(&landmine_list, x, y, id))
			{
				_LOGD(TAG, "add landmine, x=%d, y=%d, id=%d\n", x, y, id);
				game_money -= landmine_price;
				game_data.cost += landmine_price;
			}
		}
	}
	else
	{
		_LOGI(TAG, "add landmine, no enough money!\n");
	}
}

void game_add_minegun(int x, int y)
{
	int price = MINEGUN_PRICE;
	
	if(game_money >= price)
	{
		if(map_data[y][x] == FIELD_LAND)
		{
			if(minegun_dispose(&minegun_list, x, y, MINEGUN_0))
			{
				_LOGD(TAG, "add minegun, x=%d, y=%d, id=%d\n", x, y, MINEGUN_0);
				game_money -= price;
				game_data.cost += price;
			}
		}
		else if(map_data[y][x] == FIELD_FOREST)
		{
			if(minegun_dispose(&minegun_list, x, y, MINEGUN_1))
			{
				_LOGD(TAG, "add minegun, x=%d, y=%d, id=%d\n", x, y, MINEGUN_1);
				game_money -= price;
				game_data.cost += price;
			}
		}
	}
	else
	{
		_LOGI(TAG, "add minegun, no enough money!\n");
	}
}

void game_dig_landmine(int x, int y)
{
	landmine_t mine;
	landmine_t *mine2;
	
	mine.x = x;
	mine.y = y;

	mine2 = dlist_find(landmine_list, &mine, landmine_xy_cmp);

	if(mine2 != NULL)
	{
		_LOGD(TAG, "dig landmine, x=%d, y=%d, id=%d\n", x, y, mine2->id);
		
		game_money += landmine_get_recycle_price(mine2->id);
		game_money += (landmine_get_plug_price(mine2->plug)*RECYCLE_PERCENT/100);
		
		dlist_del(&landmine_list, &mine, landmine_xy_cmp);
	}
}

void game_dig_minegun(int x, int y)
{
	minegun_t mg;
	minegun_t *mg2;
	
	mg.x = x;
	mg.y = y;

	mg2 = dlist_find(minegun_list, &mg, minegun_xy_cmp);

	if(mg2 != NULL)
	{
		_LOGD(TAG, "dig minegun, x=%d, y=%d, id=%d\n", x, y, mg2->id);
		
		game_money += (MINEGUN_PRICE*RECYCLE_PERCENT/100);
		dlist_del(&minegun_list, &mg, minegun_xy_cmp);
	}
}

void game_harvest_plant(int x, int y)
{
	plant_t plant;
	plant_t *plant2;

	int harvest[]=
	{
		0,	//PLANT_STATE_SEED
		1,	//PLANT_STATE_SEEDLING
		2,	//PLANT_STATE_YOUNG
		5	//PLANT_STATE_MATURE
	};
	
	plant.x = x;
	plant.y = y;

	plant2 = dlist_find(plant_list, &plant, plant_xy_cmp);

	if(plant2 != NULL)
	{
		_LOGD(TAG, "harvest plant, x=%d, y=%d, id=%d\n", x, y, plant2->id);
		game_money += (opt_get_value(OPT_ID_PLANT_PRICE)*harvest[plant2->state]);
		game_data.money += (opt_get_value(OPT_ID_PLANT_PRICE)*harvest[plant2->state]);
		game_data.plant++;
		dlist_del(&plant_list, &plant, landmine_xy_cmp);
	}
}

void game_watering_plant(int x, int y)
{
	plant_t plant;
	plant_t *plant2;
	
	plant.x = x;
	plant.y = y;

	plant2 = dlist_find(plant_list, &plant, plant_xy_cmp);

	if(plant2 != NULL)
	{
		_LOGD(TAG, "watering plant, x=%d, y=%d, id=%d\n", x, y, plant2->id);
		plant2->water = PLANT_WATER/TIME_UNIT;
	}
}

void game_explose_landmine(int x, int y)
{
	int last_killed = game_data.killed_enemy;
	landmine_t landmine;
	landmine_t *landmine2;
	
	landmine.x = x;
	landmine.y = y;

	landmine2 = dlist_find(landmine_list, &landmine, landmine_xy_cmp);

	if(landmine2 != NULL)
	{
		_LOGD(TAG, "explose landmine, x=%d, y=%d, id=%d\n", x, y, landmine2->id);
		explose_landmine(landmine2);
		delete_dead_enemy();
		delete_exploded_landmine();
	}
	
	if(game_data.killed_enemy-last_killed > game_data.max_killed_number)
	{
		game_data.max_killed_number = game_data.killed_enemy-last_killed;
	}
}

int game_get_object(int x, int y)
{
	int ret = OPER_OBJ_NONE;
	plant_t plant;
	plant_t *plant2;
	landmine_t landmine;
	landmine_t *landmine2;
	minegun_t minegun;
	minegun_t *minegun2;
	
	plant.x = x;
	plant.y = y;
	landmine.x = x;
	landmine.y = y;
	minegun.x = x;
	minegun.y = y;

	landmine2 = dlist_find(landmine_list, &landmine, landmine_xy_cmp);
	plant2 = dlist_find(plant_list, &plant, plant_xy_cmp);
	minegun2 = dlist_find(minegun_list, &minegun, minegun_xy_cmp);
	
	if(NULL != plant2)
	{
		if(! game_is_in_gunshot(x, y))
		{
			if(plant2->state == PLANT_STATE_MATURE)
			{
				ret = OPER_OBJ_PLANT_MATURE;
			}
			else
			{
				ret = OPER_OBJ_PLANT;
			}
		}
	}
	else if(NULL != landmine2)
	{
		if(! game_is_in_gunshot(x, y))
		{
			if(landmine2->plug == PLUG_REMOTE)
			{
				ret = OPER_OBJ_MINE_REMOTE2;
			}
			else if(landmine2->plug == PLUG_TIMER)
			{
				ret = OPER_OBJ_MINE_TIMER;
			}
			else if(landmine2->id == MINE_RS)
			{
				ret = OPER_OBJ_MINE_LB;
			}
			else
			{
				ret = OPER_OBJ_MINE;
			}
		}
		else
		{
			if(landmine2->plug == PLUG_REMOTE)
			{
				ret = OPER_OBJ_MINE_REMOTE;
			}
		}
	}
	else if(NULL != minegun2)
	{
		if(minegun2->time == 0)
		{
			ret = OPER_OBJ_MINEGUN;
		}
		else
		{
			ret = OPER_OBJ_MINEGUN_NO_FIRE;
		}
	}
	else if(map_data[y][x] == FIELD_ROAD)
	{
		if(! game_is_in_gunshot(x, y))
		{
			ret = OPER_OBJ_ROAD;
		}
	}
	else if(map_data[y][x] == FIELD_LAND)
	{
		if(! game_is_in_gunshot(x, y))
		{
			if(map_is_road_side(x, y, map_data))
			{
				ret = OPER_OBJ_ROAD_SIDE;
			}
			else
			{
				ret = OPER_OBJ_LAND;
			}	
		}
	}
	else if(map_data[y][x] == FIELD_FOREST)
	{
		ret = OPER_OBJ_FOREST;
	}

	_LOGD(TAG, "get object, x=%d, y=%d, ret=%d\n", x, y, ret);
	
	return ret;
}

void game_get_enemy_list(dlist_t **list)
{
	*list = enemy_list;
}

void game_get_dead_enemy_list(dlist_t **list)
{
	*list = dead_enemy_list;
}

void game_get_bullet_list(dlist_t **list)
{
	*list = bullet_list;
}

void game_get_landmine_list(dlist_t **list)
{
	*list = landmine_list;
}

void game_get_exploded_mine_list(dlist_t **list)
{
	*list = exploded_mine_list;
}

void game_get_minegun_list(dlist_t **list)
{
	*list = minegun_list;
}

void game_get_plant_list(dlist_t **list)
{
	*list = plant_list;
}

void game_get_house_list(dlist_t **list)
{
	*list = house_list;
}

int game_get_map_index(void)
{
	return map_index;
}

void game_get_map_data(int map[MAP_H][MAP_W])
{
	memcpy(map, map_data, sizeof(map_data));
}

void game_get_direction_data(int direction[MAP_H][MAP_W])
{
	memcpy(direction, move_direction, sizeof(move_direction));
}

int game_get_money(void)
{
	return game_money;
}

int game_get_over_flag(void)
{
	return over_flag;
}

int game_is_plants_star(void)
{
	int ret = 0;
	dlist_t *p = plant_list;
	plant_t *plant;
	int count = 0;
	
	while(p != NULL)
	{
		plant = p->data;

		if(plant->state >= PLANT_STATE_MATURE)
		{
			count++;
		}
		
		p = p->next;
	}

	if(count >= PLANT_STAR)
	{
		ret = 1;
	}

	return ret;
}

int game_is_all_house_ok(void)
{
	int ret = 0;
	
	if(NULL == dlist_find(house_list, NULL, house_demage_cmp))
	{
		ret = 1;
	}

	return ret;
}

void game_minegun_fire(int x, int y, int tx, int ty)
{
	if(game_money >= opt_get_value(OPT_ID_MINE_PRICE_RS)*2)
	{
		_LOGD(TAG, "minegun fire, x=%d, y=%d\n", x, y);
		
		bullet_add(&bullet_list, BULLET_MG, 
			x*GRID_W+GRID_W/2, y*GRID_W+GRID_W/2, 
			tx*GRID_W+GRID_W/2, ty*GRID_W+GRID_W/2
		);

		minegun_reload(minegun_list, x, y);
		game_money -= opt_get_value(OPT_ID_MINE_PRICE_RS)*2;
		game_data.cost += opt_get_value(OPT_ID_MINE_PRICE_RS)*2;
		game_data.mine_mg++;
	}
	else
	{
		_LOGI(TAG, "minegun fire, no enough money!\n");
	}
}

int game_get_score(void)
{
	return game_data.score;
}

int game_get_enemy_total(void)
{
	return enemy_total;
}

int game_get_enemy_killed(void)
{
	return game_data.killed_enemy;
}

void game_get_entrance(point_t *entry, int *total)
{
	memcpy(entry, entrances, sizeof(point_t)*4);
	*total = entry_total;
}

void game_get_stars(star_data_t stars[GAME_STAR_TOTAL])
{
	int i;
	
	update_stars();

	for(i = 0; i < GAME_STAR_TOTAL; i++)
	{
		stars[i].gotten = game_stars[i];
		stars[i].target = stars_target[i*2];
		stars[i].progress = stars_progress[i];
	}
}

void game_get_name(int index, char *name)
{
	if(index < MAP_TOTAL)
	{
		strcpy(name, game_name_table[index]);
	}
	else
	{
		_LOGE(TAG, "invalid index! index=%d\n", index);
	}
}

#define MAX_VALUE		1000000

void record_init(void)
{
	int i;
	
	memset(game_record, 0, sizeof(game_record));
	memset(&total_record, 0, sizeof(total_record));
	
	for(i = 0; i < MAP_TOTAL; i++)
	{
		game_record[i].c_as_min_cost = MAX_VALUE;
	}
}

void record_load(void)
{
	FILE* fp = NULL;
	char filePath[1024];

	record_init();
	Utils_getDocPath("GameRecord.dat", filePath);
	fp = fopen(filePath, "rb");
	
	if(fp == NULL)	
	{
		_LOGE(TAG, "record load failed!\n");
		return;
	}

	fread(&total_record, sizeof(total_record), 1, fp);
	fread(game_record, sizeof(game_record), 1, fp);
	fclose(fp);
}

void record_save(void)
{
	FILE* fp = NULL;
	char filePath[1024];

	Utils_getDocPath("GameRecord.dat", filePath);
	fp = fopen(filePath, "wb");
	
	if(fp == NULL)
	{
		_LOGE(TAG, "record save failed!\n");
		return;
	}

	fwrite(&total_record, sizeof(total_record), 1, fp);
	fwrite(game_record, sizeof(game_record), 1, fp);
	fclose(fp);
}

void record_clear(void)
{
	record_init();
	record_save();
}

void record_backup(void)
{
	memcpy(game_record_bak, game_record, 
		sizeof(game_record_bak));
	memcpy(&total_record_bak, &total_record, 
		sizeof(total_record_bak));
}

int record_is_changed(void)
{
	int ret = 0;
	
	if(0 != memcmp(game_record_bak, game_record, 
		sizeof(game_record_bak)))
	{
		ret = 1;
	}
	
	if(0 != memcmp(&total_record_bak, &total_record, 
		sizeof(total_record_bak)))
	{
		ret = 1;
	}

	return ret;
}

void record_set(int index, record_t *record)
{
	if(index < ARRAY_SIZE(game_record))
	{
		memcpy(&game_record[index], record, sizeof(record_t));
	}
	else
	{
		_LOGE(TAG, "invalid index! index=%d\n", index);
	}
}

void record_get(int index, record_t *record)
{
	if(index < ARRAY_SIZE(game_record))
	{
		memcpy(record, &game_record[index], sizeof(record_t));
	}
	else
	{
		_LOGE(TAG, "invalid index! index=%d\n", index);
	}
}

void record_get_total_record(total_record_t *record)
{
	memcpy(record, &total_record, sizeof(total_record_t));
}

static void update_star_progress(void)
{
	int i;
	int count;
	int max;
	//star 0
	stars_progress[0] = 0;
	
	if(game_record[0].star_victory != 0)
	{
		stars_progress[0] = 1;
	}

	//star 1
	stars_progress[1] = 0;
	
	for(i = 0; i < MAP_TOTAL; i++)
	{
		if((game_record[i].star_victory != 0)
			&&(game_record[i].star_house != 0)
			&&(game_record[i].star_plant != 0))
		{
			stars_progress[1] = 1;
			break;
		}
	}
	//star 2
	count = 0;

	for(i = 0; i < 10; i++)
	{
		if(game_record[i].star_victory == 1)
		{
			count++;
		}
	}

	stars_progress[2] = count;
	//star 3
	count = 0;
	
	for(i = 0; i < MAP_TOTAL; i++)
	{
		if(game_record[i].star_victory == 1)
		{
			count++;
		}
	}

	stars_progress[3] = count;
	//star 4
	stars_progress[4] = game_record[4].c_max_left_plant;
	//star 5
	stars_progress[5] = game_record[14].c_max_left_plant;
	//star 6
	max = 0;
	
	for(i = 0; i < MAP_TOTAL; i++)
	{
		if(game_record[i].max_killed_number > max)
		{
			max = game_record[i].max_killed_number;
		}
	}

	stars_progress[6] = max;
	//star 7
	stars_progress[7] = max;
	//star 8
	stars_progress[8] = max;
	//star 9
	stars_progress[9] = game_record[5].c_as_min_cost;
	//star 10
	count = 0;
	
	for(i = 0; i < MAP_TOTAL; i++)
	{
		if(game_record[i].star_victory == 1)
		{
			count++;
		}

		if(game_record[i].star_house == 1)
		{
			count++;
		}

		if(game_record[i].star_plant == 1)
		{
			count++;
		}
	}

	stars_progress[10] = count;
	//star 11
	stars_progress[11] = total_record.money;
	//star 12
	stars_progress[12] = total_record.mine_mg;
	//star 13
	stars_progress[13] = total_record.mine_rs;
	//star 14
	stars_progress[14] = total_record.score;
	//star 15
	stars_progress[15] = total_record.win;
}

static void update_stars(void)
{
	int i;

	update_star_progress();

	for(i = 0; i < GAME_STAR_TOTAL; i++)
	{
		game_stars[i] = 0;
		
		if(stars_target[i*2+1] == CHK_EQUAL)
		{
			if(stars_progress[i] == stars_target[i*2])
			{
				game_stars[i] = 1;
			}
		}
		else if(stars_target[i*2+1] == CHK_NOT_EQUAL)
		{
			if(stars_progress[i] != stars_target[i*2]){
				game_stars[i] = 1;
			}
		}
		else if(stars_target[i*2+1] == CHK_MORE)
		{
			if(stars_progress[i] > stars_target[i*2])
			{
				game_stars[i] = 1;
			}
		}
		else if(stars_target[i*2+1] == CHK_LESS)
		{
			if(stars_progress[i] < stars_target[i*2])
			{
				game_stars[i] = 1;
			}
		}
	}
}

void game_set_grid_size(int size)
{
	GRID_W = size;
}
