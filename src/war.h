/**
	\addtogroup GameCore
	implementation of the game core.
*/
/*@{*/
/***************************************************************************//**
	\file		war.h
	\brief		declaration of game type and api.
	\author		XB
	\date		2016-7-5
	\version	1.0.1
*******************************************************************************/
#ifndef _WAR_H
#define _WAR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "dlist.h"
#include "map.h"
#include "enemy.h"
#include "landmine.h"
#include "plant.h"
#include "house.h"

/**
	\def GAME_STAR_TOTAL
	star total.
*/
#define GAME_STAR_TOTAL			16

/**
	\enum over_flag_t
	over flag.
*/
typedef enum{
	OVER_NONE = 0,	/**< not over */
	OVER_WIN,		/**< game over(win) */
	OVER_LOSE,		/**< game over(lose) */

	OVER_MAX		/**< max */
} over_flag_t;

/**
	\enum operate_obj_t
	operation object of the field.
*/
typedef enum{
	OPER_OBJ_ROAD = 0,		/**< road */
	OPER_OBJ_LAND,			/**< land */
	OPER_OBJ_PLANT,			/**< plant */
	OPER_OBJ_PLANT_MATURE,	/**< mature plant */
	OPER_OBJ_MINE,			/**< mine */
	OPER_OBJ_MINE_LB,		/**< roadside mine */
	OPER_OBJ_MINE_REMOTE,	/**< remote control */
	OPER_OBJ_MINE_REMOTE2,	/**< remote control(in enemy's gunshot) */
	OPER_OBJ_MINE_TIMER,	/**< timer */
	OPER_OBJ_ROAD_SIDE,		/**< roadside */
	OPER_OBJ_FOREST,		/**< forest */
	OPER_OBJ_MINEGUN,		/**< mine gun */
	OPER_OBJ_MINEGUN_NO_FIRE,/**< mine gun(reloading) */
	OPER_OBJ_NONE,			/**< none */

	OPER_OBJ_MAX			/**< max */
}operate_obj_t;

/**
	\struct game_data_t
	game data.
*/
typedef struct{
	int money;			/**< money */
	int cost;			/**< cost */
	int plant;			/**< plant */
	int left_plant;		/**< left plant */
	int score;			/**< score */
	int killed_enemy;	/**< killed enemy */
	int max_killed_number;	/**< max killed enemy */
	int mine_nm;		/**< normal mine used */
	int mine_ae;		/**< anti-engineering mine used */
	int mine_aa;		/**< anti-armor mine used */
	int mine_at;		/**< anti-tank mine used */
	int mine_rs;		/**< roadside mine used */
	int mine_mg;		/**< mine gun used */
} game_data_t;

/**
	\struct record_t
	record data of a game.
*/
typedef struct{
	int star_victory;	/**< victory star */
	int star_plant;		/**< plant star */
	int star_house;		/**< house star */
	
	int max_killed_number;	/**< max killed enemy sum by one operating */
	int c_max_left_plant;	/**< max left plant total */
	int c_as_max_left_plant;/**< max left plant total when got all stars */
	int c_as_min_cost;		/**< min cost when got all stars */
} record_t;

/**
	\struct total_record_t
	total record data.
*/
typedef struct{
	int game;		/**< played game total */
	int win;		/**< win play game total */
	int score;		/**< total score */
	int money;		/**< total money */
	int cost;		/**< total cost */
	int plant;		/**< total plant */
	int mine_nm;	/**< total normal mine */
	int mine_ae;	/**< total anti-engineering mine */
	int mine_aa;	/**< total anti-armor mine */
	int mine_at;	/**< total anti-tank mine */
	int mine_rs;	/**< total roadside mine */
	int mine_mg;	/**< total mine gun */
} total_record_t;

/**
	\struct star_data_t
	star info data.
*/
typedef struct{
	int gotten;		/**< 0-not gotten, 1-gotten */
	int progress;	/**< current progress */
	int target;		/**< target value */
} star_data_t;

/***************************************************************************//**
	\fn			void game_start(int map)
	\brief		start game. 
	\param[in]	map :map index, range is 0~(MAP_TOTAL-1).
	\warning	If map index is invalid, no process.
*******************************************************************************/
void game_start(int map);

/***************************************************************************//**
	\fn			void game_end(void)
	\brief		cancel game.
*******************************************************************************/
void game_end(void);

/***************************************************************************//**
	\fn			void game_tick(void)
	\brief		game cycle process.
	\remark		call this function at 10ms period.
*******************************************************************************/
void game_tick(void);

/***************************************************************************//**
	\fn			void game_add_plug(int x, int y, int plug)
	\brief		add plug for roadside mine.
	\param[in]	x :coordinate x of roadside mine.
	\param[in]	y :coordinate y of roadside mine.
	\param[in]	plug :plug id, see #plug_t.
*******************************************************************************/
void game_add_plug(int x, int y, int plug);

/***************************************************************************//**
	\fn			void game_add_plant(int x, int y)
	\brief		add plant to land.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
*******************************************************************************/
void game_add_plant(int x, int y);

/***************************************************************************//**
	\fn			void game_add_landmine(int x, int y, int id)
	\brief		add landmine to the field.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
	\param[in]	id :landmine id, see #landmine_id_t.
*******************************************************************************/
void game_add_landmine(int x, int y, int id);

/***************************************************************************//**
	\fn			void game_add_minegun(int x, int y)
	\brief		add minegun to the field.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
*******************************************************************************/
void game_add_minegun(int x, int y);

/***************************************************************************//**
	\fn			void game_harvest_plant(int x, int y)
	\brief		harvest plant in land.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
*******************************************************************************/
void game_harvest_plant(int x, int y);

/***************************************************************************//**
	\fn			void game_dig_landmine(int x, int y)
	\brief		dig landmine.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
*******************************************************************************/
void game_dig_landmine(int x, int y);

/***************************************************************************//**
	\fn			void game_dig_minegun(int x, int y)
	\brief		dig minegun.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
*******************************************************************************/
void game_dig_minegun(int x, int y);

/***************************************************************************//**
	\fn			void game_watering_plant(int x, int y)
	\brief		watering plant.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
*******************************************************************************/
void game_watering_plant(int x, int y);

/***************************************************************************//**
	\fn			void game_explose_landmine(int x, int y)
	\brief		explose landmine.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
*******************************************************************************/
void game_explose_landmine(int x, int y);

/***************************************************************************//**
	\fn			int game_get_object(int x, int y)
	\brief		get operating object of the field.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
	\return		operating object, see #operate_obj_t.
*******************************************************************************/
int game_get_object(int x, int y);

/***************************************************************************//**
	\fn			int game_is_in_gunshot(int x, int y)
	\brief		judge whether the coordinate in enemy's gunshot.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
	\return		0:not in gunshot/1:in gunshot.
*******************************************************************************/
int game_is_in_gunshot(int x, int y);

/***************************************************************************//**
	\fn			void game_get_danger_range(int map[MAP_H][MAP_W])
	\brief		get danger range in the field.
	\param[out]	map :danger data. 0:safe/1:danger.
*******************************************************************************/
void game_get_danger_range(int map[MAP_H][MAP_W]);

/***************************************************************************//**
	\fn			void game_get_enemy_list(dlist_t **list)
	\brief		get enemy list.
	\param[out]	list :enemy list.
*******************************************************************************/
void game_get_enemy_list(dlist_t **list);

/***************************************************************************//**
	\fn			void game_get_dead_enemy_list(dlist_t **list)
	\brief		get dead enemy list.
	\param[out]	list :dead enemy list.
*******************************************************************************/
void game_get_dead_enemy_list(dlist_t **list);

/***************************************************************************//**
	\fn			void game_get_bullet_list(dlist_t **list)
	\brief		get bullet list.
	\param[out]	list :bullet list.
*******************************************************************************/
void game_get_bullet_list(dlist_t **list);

/***************************************************************************//**
	\fn			void game_get_landmine_list(dlist_t **list)
	\brief		get landmine list.
	\param[out]	list :landmine list.
*******************************************************************************/
void game_get_landmine_list(dlist_t **list);

/***************************************************************************//**
	\fn			void game_get_exploded_mine_list(dlist_t **list)
	\brief		get exploded landmine list.
	\param[out]	list :exploded landmine list.
*******************************************************************************/
void game_get_exploded_mine_list(dlist_t **list);

/***************************************************************************//**
	\fn			void game_get_minegun_list(dlist_t **list)
	\brief		get minegun list.
	\param[out]	list :minegun list.
*******************************************************************************/
void game_get_minegun_list(dlist_t **list);

/***************************************************************************//**
	\fn			void game_get_plant_list(dlist_t **list)
	\brief		get plant list.
	\param[out]	list :plant list.
*******************************************************************************/
void game_get_plant_list(dlist_t **list);

/***************************************************************************//**
	\fn			void game_get_house_list(dlist_t **list)
	\brief		get house list.
	\param[out]	list :house list.
*******************************************************************************/
void game_get_house_list(dlist_t **list);

/***************************************************************************//**
	\fn			int game_get_map_index(void)
	\brief		get map index of current game.
	\return		map index, range is 0~(MAP_TOTAL-1).
*******************************************************************************/
int game_get_map_index(void);

/***************************************************************************//**
	\fn			void game_get_map_data(int map[MAP_H][MAP_W])
	\brief		get map data of current game.
	\param[out]	map :map data array, see #field_t.
*******************************************************************************/
void game_get_map_data(int map[MAP_H][MAP_W]);

/***************************************************************************//**
	\fn			void game_get_direction_data(int direction[MAP_H][MAP_W])
	\brief		get move direction of current map.
	\param[out]	direction :direction data array, see #move_dir_t.
*******************************************************************************/
void game_get_direction_data(int direction[MAP_H][MAP_W]);

/***************************************************************************//**
	\fn			int game_get_money(void)
	\brief		get money.
	\return		money.
*******************************************************************************/
int game_get_money(void);

/***************************************************************************//**
	\fn			int game_get_over_flag(void)
	\brief		get over flag.
	\return		over flag, see #over_flag_t.
*******************************************************************************/
int game_get_over_flag(void);

/***************************************************************************//**
	\fn			int game_is_all_house_ok(void)
	\brief		judge whether all houses are not damaged.
	\return		0:not all OK/1:all OK.
*******************************************************************************/
int game_is_all_house_ok(void);

/***************************************************************************//**
	\fn			int game_is_plants_star(void)
	\brief		judge whether plant star is gotten.
	\return		0:not gotten/1:gotten.
*******************************************************************************/
int game_is_plants_star(void);

/***************************************************************************//**
	\fn			void game_minegun_fire(int x, int y, int tx, int ty)
	\brief		minegun fire.
	\param[in]	x :coordinate x of minegun.
	\param[in]	y :coordinate y of minegun.
	\param[in]	tx :coordinate x of target.
	\param[in]	ty :coordinate y of target.
*******************************************************************************/
void game_minegun_fire(int x, int y, int tx, int ty);

/***************************************************************************//**
	\fn			int game_get_score(void)
	\brief		get score of current game.
	\return		score.
*******************************************************************************/
int game_get_score(void);

/***************************************************************************//**
	\fn			int game_get_enemy_total(void)
	\brief		get enemy total.
	\return		enemy total.
*******************************************************************************/
int game_get_enemy_total(void);

/***************************************************************************//**
	\fn			int game_get_enemy_killed(void)
	\brief		get killed enemy total.
	\return		killed enemy total.
*******************************************************************************/
int game_get_enemy_killed(void);

/***************************************************************************//**
	\fn			void game_get_entrance(point_t *entry, int *total)
	\brief		get entrances of current map.
	\param[out]	entry :array for store entrances.
	\param[out]	total :entrance total, range is 1~4.
	\warning	paramter entry must have 4 elements.
*******************************************************************************/
void game_get_entrance(point_t *entry, int *total);

/***************************************************************************//**
	\fn			void game_get_stars(star_data_t stars[GAME_STAR_TOTAL])
	\brief		get star data.
	\param[out]	stars :array for store star data, must has GAME_STAR_TOTAL 
				elements.
*******************************************************************************/
void game_get_stars(star_data_t stars[GAME_STAR_TOTAL]);

/***************************************************************************//**
	\fn			void game_get_name(int index, char *name)
	\brief		get game name.
	\param[in]	index :map index, range is 0~(MAP_TOTAL-1).
	\param[out]	name :map name.
	\warning	if index is invalid, no process.
*******************************************************************************/
void game_get_name(int index, char *name);

/***************************************************************************//**
	\fn			void game_set_grid_size(int size)
	\brief		set grid size(for bullet coordinate).
	\param[in]	size :grid size.
*******************************************************************************/
void game_set_grid_size(int size);

/***************************************************************************//**
	\fn			void record_init(void)
	\brief		initial record.
*******************************************************************************/
void record_init(void);

/***************************************************************************//**
	\fn			void record_load(void)
	\brief		load record.
*******************************************************************************/
void record_load(void);

/***************************************************************************//**
	\fn			void record_save(void)
	\brief		save record.
*******************************************************************************/
void record_save(void);

/***************************************************************************//**
	\fn			void record_clear(void)
	\brief		clear and save record.
*******************************************************************************/
void record_clear(void);

/***************************************************************************//**
	\fn			void record_backup(void)
	\brief		backup record.
*******************************************************************************/
void record_backup(void);

/***************************************************************************//**
	\fn			int record_is_changed(void)
	\brief		judge whether record change.
	\return		0:not change/1:changed.
*******************************************************************************/
int record_is_changed(void);

/***************************************************************************//**
	\fn			void record_set(int index, record_t *record)
	\brief		set record data of a game.
	\param[in]	index :map index, range is 0~(MAP_TOTAL-1).
	\param[in]	record :record data.
	\warning	if index is invalid, no process.
*******************************************************************************/
void record_set(int index, record_t *record);

/***************************************************************************//**
	\fn			void record_get(int index, record_t *record)
	\brief		get record data of a game.
	\param[in]	index :map index, range is 0~(MAP_TOTAL-1).
	\param[out]	record :record data.
	\warning	if index is invalid, no process.
*******************************************************************************/
void record_get(int index, record_t *record);

/***************************************************************************//**
	\fn			void record_get_total_record(total_record_t *record)
	\brief		get total record data of all games.
	\param[out]	record :total record data.
*******************************************************************************/
void record_get_total_record(total_record_t *record);

#ifdef __cplusplus
}
#endif
#endif //_WAR_H
/*@}*/
