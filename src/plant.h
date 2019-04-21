/**
	\addtogroup	Plant
	implementation of plant data.
	\ingroup GameCore
*/
/*@{*/
/***************************************************************************//**
	\file		plant.h
	\brief		declaration of plant type and api.
	\author		XB
	\date		2016-7-11
	\version	1.0.1
*******************************************************************************/
#ifndef _PLANT_H
#define _PLANT_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
	\def PLANT_PRICE
	plant price.
*/
#define PLANT_PRICE			(opt_get_value(OPT_ID_PLANT_PRICE))//50

/**
	\def PLANT_WATER
	plant water.
*/
#define PLANT_WATER			10000000	/*ms*/

/**
	\def PLANT_GROW_TIME
	plant grow time(status change time).
*/
#define PLANT_GROW_TIME		(opt_get_value(OPT_ID_PLANT_GROW_CYCLE))//1000	/*ms*/

/**
	\enum plant_status_t
	plant status.
*/
typedef enum{
	PLANT_STATE_SEED,		/**< seed */
	PLANT_STATE_SEEDLING,	/**< seedling */
	PLANT_STATE_YOUNG,		/**< young */
	PLANT_STATE_MATURE,		/**< mature */
	
	PLANT_STATE_MAX
} plant_status_t;

/**
	\struct plant_t
	plant data.
*/
typedef struct{
	int id;					/**< id */
	int x;					/**< coornate x */
	int y;					/**< coornate y */	
	plant_status_t state;	/**< state, see #plant_status_t */
	int time;				/**< time */
	int water;				/**< water */
} plant_t;

/***************************************************************************//**
	\fn			int plant_xy_cmp(void *v1, void *v2)
	\brief		compare coordinate of plant(for dlist operation).
	\param[in]	v1 :pointer to plant.
	\param[in]	v2 :pointer to plant.
	\return		0:equal/1:not equal.
*******************************************************************************/
int plant_xy_cmp(void *v1, void *v2);

#ifdef __cplusplus
}
#endif
#endif //_PLANT_H
/*@}*/
