/**
	\addtogroup	Enemy
	implementation of enemy and bullet.
	\ingroup GameCore
*/
/*@{*/
/***************************************************************************//**
	\file		enemy.h
	\brief		declaration of enemy and bullet type and api.
	\author		XA
	\date		2016-7-6
	\version	1.0.1
*******************************************************************************/
#ifndef _ENEMY_H
#define _ENEMY_H

#include "dlist.h"
#include "map.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
	\def GUNSHOT_W
	width of gunshot.
	\def GUNSHOT_H
	height of gunshot.
	\def GUNSHOT_C
	center of gunshot.
*/
#define GUNSHOT_W		11
#define GUNSHOT_H		11
#define GUNSHOT_C		5

/**
	\def DEMAGE_DELAY
	delay of demage.
*/
#define DEMAGE_DELAY	1

/**
	\def QUEUE_MAX_LEN
	max length of enemy queue.
*/
#define QUEUE_MAX_LEN	50

/**
	\def ENEMY_DEAD_TIME
	dead time of enemy.
*/
#define ENEMY_DEAD_TIME	6

/**
	\enum enemy_id_t
	enemy id.
*/
typedef enum{
	ENEMY_SB = 0,	/**< soldier */
	ENEMY_GB,		/**< engineer */
	ENEMY_QC,		/**< car */
	ENEMY_ZJ,		/**< armor */
	ENEMY_TK,		/**< tank */

	ENEMY_MAX
} enemy_id_t;

/**
	\enum enemy_dir_t
	enemy move direction.
*/
typedef enum{
	ENEMY_DIR_R = 0,/**< right */
	ENEMY_DIR_U,	/**< up */
	ENEMY_DIR_L,	/**< left */
	ENEMY_DIR_D,	/**< down */

	ENEMY_DIR_MAX
} enemy_dir_t;

/**
	\struct enemy_t
	enemy data.
*/
typedef struct{
	enemy_id_t id;	/**< enemy id, see #enemy_id_t */
	int x;			/**< coordinate x */
	int y;			/**< coordinate y */
	int last_x;		/**< last coordinate x */
	int last_y;		/**< last coordinate y */
	int life;		/**< life */
	int time;		/**< time */
	int delay;		/**< delay */
	int firing_interval;	/**< firing interval */
	int moved;				/**< moved flag */
	enemy_dir_t direction;	/**< move direction */
	int entry;		/**< entrance */
} enemy_t;

/**
	\struct enemy_queue_item_t
	enemy queue item.
*/
typedef struct{
	enemy_id_t id;	/**< enemy id, see #enemy_id_t */
	int interval;	/**< time interval */
} enemy_queue_item_t;

/**
	\def BULLET_EXPLOSE_STEP
	bullet explose step.
*/
#define BULLET_EXPLOSE_STEP		4

/**
	\enum bullet_id_t
	bullet id.
*/
typedef enum{
	BULLET_BQ = 0,	/**< bullet of soldier and car */
	BULLET_ZJ,		/**< bullet of armor */
	BULLET_TK,		/**< bullet of tank */
	BULLET_MG,		/**< bullet of minegun */
	
	BULLET_MAX
} bullet_id_t;

/**
	\struct bullet_t
	bullet data.
*/
typedef struct{
	bullet_id_t id;	/**< bullet id, see #bullet_id_t */
	int x;			/**< current coordinate x */
	int y;			/**< current coordinate y */
	int ex;			/**< target coordinate x */
	int ey;			/**< target coordinate x */
	int time;		/**< time for exploding */
	int state;		/**< state for exploding */
} bullet_t;

/***************************************************************************//**
	\fn			void enemy_load(int index, dlist_t **list)
	\brief		load enemy queue. If index is invalid, no process.
	\param[in]	index :queue index, range is 0~(MAP_TOTAL-1).
	\param[out]	list :enemy list.
*******************************************************************************/
void enemy_load(int index, dlist_t **list);

/***************************************************************************//**
	\fn			void enemy_load_random(int index, dlist_t **list)
	\brief		load random enemy queue. If index is invalid, no process.
	\param[in]	index :queue index, range is 0~(MAP_TOTAL-1).
	\param[out]	list :enemy list.
*******************************************************************************/
void enemy_load_random(int index, dlist_t **list);

/***************************************************************************//**
	\fn			void enemy_move(enemy_t *enemy, int direction[MAP_H][MAP_W], 
					dlist_t *list)
	\brief		enemy move a step.
	\param[in,out]	enemy :enemy.
	\param[in]	direction :move direction data of the map.
	\param[in,out]	list :enemy list.
*******************************************************************************/
void enemy_move(enemy_t *enemy, int direction[MAP_H][MAP_W], dlist_t *list);

/***************************************************************************//**
	\fn			void enemy_reload(enemy_t *enemy)
	\brief		enemy reload after firing.
	\param[in,out]	enemy :enemy.
*******************************************************************************/
void enemy_reload(enemy_t *enemy);

/***************************************************************************//**
	\fn			void enemy_get_gunshot(int id, 
					int gunshot[GUNSHOT_H][GUNSHOT_W])
	\brief		get enemy gunshot.
	\param[in]	id :enemy id.
	\param[out]	gunshot :gunshot data, not 0 data is in gunshot.
*******************************************************************************/
void enemy_get_gunshot(int id, int gunshot[GUNSHOT_H][GUNSHOT_W]);

/***************************************************************************//**
	\fn			int enemy_get_bullet(int id)
	\brief		get bullet of the enemy.
	\param[in]	id :enemy id, see #enemy_id_t.
	\return		bullet id, see #bullet_id_t.
*******************************************************************************/
int enemy_get_bullet(int id);

/***************************************************************************//**
	\fn			int enemy_is_in_gunshot(enemy_t *enemy, int x, int y)
	\brief		judge if coordinate is in gunshot.
	\param[in]	enemy :enemy.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
	\return		0:not in gunshot/1:in gunshot.
*******************************************************************************/
int enemy_is_in_gunshot(enemy_t *enemy, int x, int y);

/***************************************************************************//**
	\fn			int enemy_xy_cmp(void *v1, void *v2)
	\brief		compare coordinate of enemy(for dlist operation).
	\param[in]	v1 :pointer to enemy.
	\param[in]	v2 :pointer to enemy.
	\return		0:equal/1:not equal.
*******************************************************************************/
int enemy_xy_cmp(void *v1, void *v2);

/***************************************************************************//**
	\fn			int enemy_dead_cmp(void *v1, void *v2)
	\brief		compare life equal 0(for dlist operation).
	\param[in]	v1 :pointer to enemy.
	\param[in]	v2 :pointer to enemy. no use, can be set NULL.
	\return		0:equal/1:not equal.
*******************************************************************************/
int enemy_dead_cmp(void *v1, void *v2);

/***************************************************************************//**
	\fn			int enemy_over_cmp(void *v1, void *v2)
	\brief		compare time equal ENEMY_DEAD_TIME(for dlist operation).
	\param[in]	v1 :pointer to enemy.
	\param[in]	v2 :pointer to enemy. no use, can be set NULL.
	\return		0:equal/1:not equal.
*******************************************************************************/
int enemy_over_cmp(void *v1, void *v2);

/***************************************************************************//**
	\fn			void enemy_load_queues(void)
	\brief		load all enemy queues. If the queue file does not exit,
				set default queue.
*******************************************************************************/
void enemy_load_queues(void);

/***************************************************************************//**
	\fn			void enemy_queue_load(const char *file_name, 
					enemy_queue_item_t *queue)
	\brief		load enemy queue from file.
	\param[in]	file_name :file name(full path).
	\param[out]	queue :array for store queue data.
*******************************************************************************/
void enemy_queue_load(const char *file_name, enemy_queue_item_t *queue);

/***************************************************************************//**
	\fn			void enemy_queue_save(const char *file_name, 
					enemy_queue_item_t *queue)
	\brief		save enemy queue to file.
	\param[in]	file_name :file name(full path).
	\param[in]	queue :array for store queue data.
*******************************************************************************/
void enemy_queue_save(const char *file_name, enemy_queue_item_t *queue);

/***************************************************************************//**
	\fn			void enemy_queue_get(int index, int q[QUEUE_MAX_LEN][2])
	\brief		get enemy queue.
	\param[in]	index :queue index, range is 0~MAP_TOTAL-1.
	\param[out]	q :array for store queue data.
*******************************************************************************/
void enemy_queue_get(int index, int q[QUEUE_MAX_LEN][2]);

/***************************************************************************//**
	\fn			void bullet_set_move_step(double step)
	\brief		set bullet move step.
	\param[in]	step :move step(by pixel).
*******************************************************************************/
void bullet_set_move_step(double step);

/***************************************************************************//**
	\fn			void bullet_add(dlist_t **list, int id, int sx, int sy, 
					int ex, int ey)
	\brief		add bullet to list.
	\param[in,out]	list :bullet list.
	\param[in]	id :bullet id, see #bullet_id_t.
	\param[in]	sx :start point x.
	\param[in]	sy :start point y.
	\param[in]	ex :target point x.
	\param[in]	ey :target point y.
*******************************************************************************/
void bullet_add(dlist_t **list, int id, int sx, int sy, int ex, int ey);

/***************************************************************************//**
	\fn			void bullet_move(bullet_t *bullet)
	\brief		bullet move a step.
	\param[in,out]	bullet :pointer to bullet.
*******************************************************************************/
void bullet_move(bullet_t *bullet);

/***************************************************************************//**
	\fn			int bullet_get_power(int id)
	\brief		get bullet power.
	\param[in]	id :bullet id, see #bullet_id_t.
*******************************************************************************/
int bullet_get_power(int id);

/***************************************************************************//**
	\fn			int bullet_end_cmp(void *v1, void *v2)
	\brief		compare whether bullet arrives target(for dlist operation).
	\param[in]	v1 :pointer to bullet.
	\param[in]	v2 :pointer to bullet. no use, can be set NULL.
	\return		0:equal/1:not equal.
*******************************************************************************/
int bullet_end_cmp(void *v1, void *v2);

/***************************************************************************//**
	\fn			int bullet_over_cmp(void *v1, void *v2)
	\brief		compare whether bullet explosing finishes(for dlist operation).
	\param[in]	v1 :pointer to bullet.
	\param[in]	v2 :pointer to bullet. no use, can be set NULL.
	\return		0:equal/1:not equal.
*******************************************************************************/
int bullet_over_cmp(void *v1, void *v2);

#ifdef __cplusplus
}
#endif
#endif //_ENEMY_H
/*@}*/
