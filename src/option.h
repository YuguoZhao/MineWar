/**
	\addtogroup	Option
	calibration data of the game.
	\ingroup GameCore
*/
/*@{*/
/***************************************************************************//**
	\file		option.h
	\brief		declaration of option type and api.
	\author		XA
	\date		2016-7-11
	\version	1.0.1
*******************************************************************************/
#ifndef _OPTION_H
#define _OPTION_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "type.h"

/**
	\enum opt_id_t
	option item index
*/
typedef enum{
	OPT_ID_ENEMY_DISPOSE_CYCLE,	/**< enemy dispose cycle */
	OPT_ID_ENEMY_MOVE_CYCLE,	/**< enemy move cycle */
	OPT_ID_BULLET_MOVE_CYCLE,	/**< bullet move cycle */
	OPT_ID_PLANT_GROW_CYCLE,	/**< plant grow cycle */
	OPT_ID_PLUG_TIMER_CYCLE,	/**< pulg timer cycle */
	OPT_ID_INITIAL_MONEY,		/**< initial money */
	OPT_ID_DISPOSE_OFFSET,		/**< dispose offset */
	OPT_ID_PLANT_PRICE,			/**< plant price */
	OPT_ID_PLANT_HARVEST,		/**< plant harvest */
	OPT_ID_MINE_PRICE_NM,		/**< normal mine price */
	OPT_ID_MINE_PRICE_AE,		/**< anti-engineering mine price */
	OPT_ID_MINE_PRICE_RS,		/**< roadside mine price */
	OPT_ID_MINE_PRICE_AA,		/**< anti-armor mine price */
	OPT_ID_MINE_PRICE_AT,		/**< anti-tank mine price */
	OPT_ID_PLUG_PRICE_TIMER,	/**< timer price */
	OPT_ID_PLUG_PRICE_REMOTE,	/**< remote control price */
	OPT_ID_GAME_SPEED,			/**< game speed */
	OPT_ID_LIMIT_MONEY,			/**< limit mode money */
	OPT_ID_QUEUE_RANDOM,		/**< random queue */
	OPT_ID_EMEMY_Q1_LEN,		/**< queue 1 length */

	OPT_ID_MAX = (OPT_ID_EMEMY_Q1_LEN+36)
}opt_id_t;

/***************************************************************************//**
	\fn			void opt_load(const char *file_name)
	\brief		load option data file.
	\param[in]	file_name :file name(full path).
*******************************************************************************/
void opt_load(const char *file_name);

/***************************************************************************//**
	\fn			void opt_save(const char *file_name)
	\brief		save option data file.
	\param[in]	file_name :file name(full path).
*******************************************************************************/
void opt_save(const char *file_name);

/***************************************************************************//**
	\fn			void opt_adjust_up(int index)
	\brief		option value adjust up. when reached max value, no action.
	\param[in]	index :item index, see #opt_id_t.
*******************************************************************************/
void opt_adjust_up(int index);

/***************************************************************************//**
	\fn			void opt_adjust_down(int index)
	\brief		option value adjust down. when reached min value, no action.
	\param[in]	index :item index, see #opt_id_t.
*******************************************************************************/
void opt_adjust_down(int index);

/***************************************************************************//**
	\fn			int opt_get_value(int index)
	\brief		get option item value.
	\param[in]	index :item index, see #opt_id_t.
	\return		option item value.
*******************************************************************************/
int opt_get_value(int index);

/***************************************************************************//**
	\fn			const char *opt_get_name(int index)
	\brief		get option item name.
	\param[in]	index :item index, see #opt_id_t.
	\return		option item name.
*******************************************************************************/
const char *opt_get_name(int index);

#ifdef __cplusplus
}
#endif
#endif //_OPTION_H
/*@}*/
