/**
	\addtogroup	Map
	map implementation of the game.
	\ingroup GameCore
*/
/*@{*/
/***************************************************************************//**
	\file		map.h
	\brief		declaration of map type and api.
	\author		XA
	\date		2016-7-7
	\version	1.0.1
*******************************************************************************/

#ifndef _MAP_H
#define _MAP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "type.h"

#define MAP_W			14	/**< width of map */
#define MAP_H			9	/**< height of map */

#define MAP_TOTAL	  	36	/**< map total */

/**
	\enum field_t
	field id.
*/
typedef enum{
	FIELD_ROAD		= 0,	/**< road */
	FIELD_LAND		= 1,	/**< land */
	FIELD_FOREST	= 2,	/**< forest */
	FIELD_HOUSE		= 3,	/**< house */
	FIELD_WATER		= 4,	/**< water */
	FIELD_ENTRANCE	= 5,	/**< entrance */
	FIELD_END		= 6,	/**< end of the road */
	FIELD_TREE		= 7,	/**< apple tree */

	LAND_MAX
} field_t;

/**
	\enum move_dir_t
	move direction.
*/
typedef enum{
	MOVE_U = -2,	/**< move up */
	MOVE_L = -1,	/**< move left */
	MOVE_R = 1,		/**< move right */
	MOVE_D = 2		/**< move down */
} move_dir_t;

/***************************************************************************//**
	\fn			void map_fill(int index, int map_data[MAP_H][MAP_W], 
					point_t *entrance, int *total)
	\brief		fill map data.
	\param[in]	index :map index, range is 0~MAP_TOTAL-1.
	\param[out]	map_data :map data, see #field_t.
	\param[out]	entrance :array for store entrances. array size must be 4.
	\param[out]	total :entrance total, range is 1~4.
*******************************************************************************/
void map_fill(int index, int map_data[MAP_H][MAP_W], point_t *entrance, int *total);

/***************************************************************************//**
	\fn			int map_is_mining_enable(int x, int y, int id, 
					int map[MAP_H][MAP_W]) 
	\brief		judge whether mining is enable or not.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
	\param[in]	id :landmine id, see #landmine_id_t.
	\param[in]	map :map data.
	\return		0:disable/1:enable
*******************************************************************************/
int map_is_mining_enable(int x, int y, int id, int map[MAP_H][MAP_W]);

/***************************************************************************//**
	\fn			int map_is_in_range(int x, int y) 
	\brief		judge whether coordinate is in map.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
	\return		0:out of map/1:in map.
*******************************************************************************/
int map_is_in_range(int x, int y);

/***************************************************************************//**
	\fn			int map_is_road_side(int x, int y, int map[MAP_H][MAP_W])
	\brief		judge whether the coordinate is roadside in map.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
	\param[in]	map :map data.
	\return		0:not roadside/1:roadside.
*******************************************************************************/
int map_is_road_side(int x, int y, int map[MAP_H][MAP_W]);

/***************************************************************************//**
	\fn			void map_load_maps(void)
	\brief		load all map files. If the map file does not exit, 
				set default map data.
*******************************************************************************/
void map_load_maps(void);

/***************************************************************************//**
	\fn			void map_load(const char *file_name, int *map)
	\brief		load map from file.
	\param[in]	file_name :map file name(full path).
	\param[out]	map :map data.
*******************************************************************************/
void map_load(const char *file_name, int *map);

/***************************************************************************//**
	\fn			void map_save(const char *file_name, int *map)
	\brief		save map data to file.
	\param[in]	file_name : map file name(full path).
	\param[in]	map : map data.
*******************************************************************************/
void map_save(const char *file_name, int *map);

/***************************************************************************//**
	\fn			void map_get(int index, int map[MAP_H][MAP_W])
	\brief		get map data.
	\param[in]	index :map index, range is 0~(MAP_TOTAL-1).
	\param[out]	map :map data.
	\warning	if the index is invalid, no process.
*******************************************************************************/
void map_get(int index, int map[MAP_H][MAP_W]);

/***************************************************************************//**
	\fn			void map_get_move_direction(int index, int dir[MAP_H][MAP_W])
	\brief		get direction data.
	\param[in]	index :map index, range is 0~MAP_TOTAL-1.
	\param[out]	dir :direction data array. see #move_dir_t.
	\warning	if the index is invalid, no process.
*******************************************************************************/
void map_get_move_direction(int index, int dir[MAP_H][MAP_W]);

#ifdef __cplusplus
}
#endif
#endif //_MAP_H
/*@}*/
