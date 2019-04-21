/**
	\addtogroup	Landmine
	implementation of landmine and minegun.
	\ingroup GameCore
*/
/*@{*/
/***************************************************************************//**
	\file		landmine.h
	\brief		declaration of landmine type and api.
	\author		XB
	\date		2016-7-6
	\version	1.0.1
*******************************************************************************/
#ifndef _LANDMINE_H
#define _LANDMINE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "dlist.h"

/**
	\def POWER_RANGE
	power range of landmine.
*/
#define POWER_RANGE			3

/**
	\def RECYCLE_PERCENT
	recycle percent of landmine.
*/
#define RECYCLE_PERCENT		60

/**
	\def LANDMINE_EXPLOSE_STEP
	landmine explose step.
*/
#define LANDMINE_EXPLOSE_STEP	3

/**
	\def MINEGUN_LIFE
	life value of minegun.
*/
#define MINEGUN_LIFE		50

/**
	\def MINEGUN_PRICE
	price of minegun.
*/
#define MINEGUN_PRICE		(opt_get_value(OPT_ID_MINE_PRICE_RS)*4)

/**
	\def MINEGUN_GUNSHOT
	gunshot of minegun.
*/
#define MINEGUN_GUNSHOT	3

/**
	\enum landmine_id_t
	landmine id.
*/
typedef enum{
	MINE_NM = 0,	/**< normal mine */
	MINE_AE,		/**< anti-engineering mine */
	MINE_RS,		/**< roadside mine */
	MINE_AA,		/**< anti-armor mine */
	MINE_AT,		/**< anti-tank mine */
	
	MINE_MAX
} landmine_id_t;

/**
	\enum plug_t
	plug id for roadside mine.
*/
typedef enum{
	PLUG_NONE = 0,	/**< no plug */
	PLUG_TIMER,		/**< timer plug */
	PLUG_REMOTE,	/**< remote control plug */

	PLUG_MAX
} plug_t;

/**
	\struct landmine_t
	landmine data.
*/
typedef struct{
	landmine_id_t id;	/**< mine id, see #landmine_id_t */
	int x;				/**< coordinate x */
	int y;				/**< coordinate y */
	int plug;			/**< plug, see #plug_t */
	int time;			/**< time */	
	int exploded;		/**< exploded flag */
} landmine_t;

/**
	\enum minegun_id_t
	minegun id.
*/
typedef enum{
	MINEGUN_0 = 0,	/**< minegun id for land */
	MINEGUN_1,		/**< minegun id for forest */
	
	MINEGUN_MAX
} minegun_id_t;

/**
	\struct minegun_t
	minegun data.
*/
typedef struct{
	minegun_id_t id;/**< minegun id, see #minegun_id_t */
	int x;			/**< coordinate x */
	int y;			/**< coordinate y */
	int time;		/**< time to reload */
	int life;		/**< life */
	int exposed;	/**< exposed flag */
} minegun_t;

/***************************************************************************//**
	\fn			int landmine_dispose(dlist_t **list, int x, int y, int id)
	\brief		dispose landmine.
	\param[in,out]	list :landmine list.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
	\param[in]	id :landmine id, see #landmine_id_t.
	\return		0:NG/1:OK.
*******************************************************************************/
int landmine_dispose(dlist_t **list, int x, int y, int id);

/***************************************************************************//**
	\fn			void landmine_add_plug(landmine_t *landmine, plug_t plug)
	\brief		add plug to roadside mine.
	\param[in,out]	landmine :landmine.
	\param[in]	plug :plug id, see #plug_t.
*******************************************************************************/
void landmine_add_plug(landmine_t *landmine, plug_t plug);

/***************************************************************************//**
	\fn			int landmine_get_price(int id)
	\brief		get price of landmine.
	\param[in]	id :landmine id, see #landmine_id_t.
	\return		price of landmine.
*******************************************************************************/
int landmine_get_price(int id);

/***************************************************************************//**
	\fn			int landmine_get_recycle_price(int id)
	\brief		get recycle price of landmine.
	\param[in]	id :landmine id, see #landmine_id_t.
	\return		recycle price of landmine.
*******************************************************************************/
int landmine_get_recycle_price(int id);

/***************************************************************************//**
	\fn			int landmine_get_plug_price(int plug)
	\brief		get price of plug.
	\param[in]	plug :plug id, see #plug_t.
	\return		price of plug.
*******************************************************************************/
int landmine_get_plug_price(int plug);

/***************************************************************************//**
	\fn			void landmine_get_power_range(int id, 
					int range[POWER_RANGE][POWER_RANGE])
	\brief		get power range of landmine.
	\param[in]	id :landmine id, see #landmine_id_t.
	\param[out]	range :power range.
*******************************************************************************/
void landmine_get_power_range(int id, int range[POWER_RANGE][POWER_RANGE]);

/***************************************************************************//**
	\fn			int landmine_xy_cmp(void *v1, void *v2)
	\brief		compare coordinate of landmine(for dlist operation).
	\param[in]	v1 :pointer to landmine.
	\param[in]	v2 :pointer to landmine.
	\return		0:equal/1:not equal.
*******************************************************************************/
int landmine_xy_cmp(void *v1, void *v2);

/***************************************************************************//**
	\fn			int landmine_exploded_cmp(void *v1, void *v2)
	\brief		compare exploded of landmine(for dlist operation).
	\param[in]	v1 :pointer to landmine.
	\param[in]	v2 :pointer to landmine.
	\return		0:equal/1:not equal.
*******************************************************************************/
int landmine_exploded_cmp(void *v1, void *v2);

/***************************************************************************//**
	\fn			int landmine_time_cmp(void *v1, void *v2)
	\brief		compare time of landmine(for dlist operation).
	\param[in]	v1 :pointer to landmine.
	\param[in]	v2 :pointer to landmine.
	\return		0:equal/1:not equal.
*******************************************************************************/
int landmine_time_cmp(void *v1, void *v2);

/***************************************************************************//**
	\fn			int minegun_dispose(dlist_t **list, int x, int y, int id)
	\brief		dispose minegun.
	\param[in,out]	list :minegun list.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
	\param[in]	id :minegun id, see #minegun_id_t.
	\return		0:NG/1:OK.
*******************************************************************************/
int minegun_dispose(dlist_t **list, int x, int y, int id);

/***************************************************************************//**
	\fn			void minegun_reload(dlist_t *list, int x, int y)
	\brief		reload minegun.
	\param[in,out]	list :minegun list.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
*******************************************************************************/
void minegun_reload(dlist_t *list, int x, int y);

/***************************************************************************//**
	\fn			int minegun_is_in_gunshot(int mx, int my, int x, int y)
	\brief		judge if coordinate is in mineguns's gunshot.
	\param[in]	mx :coordinate x of minegun.
	\param[in]	my :coordinate y of minegun.
	\param[in]	x :coordinate x.
	\param[in]	y :coordinate y.
	\return		0:not in gunshot/1:in gunshot.
*******************************************************************************/
int minegun_is_in_gunshot(int mx, int my, int x, int y);

/***************************************************************************//**
	\fn			int minegun_xy_cmp(void *v1, void *v2)
	\brief		compare coordinate of minegun(for dlist operation).
	\param[in]	v1 :pointer to minegun.
	\param[in]	v2 :pointer to minegun.
	\return		0:equal/1:not equal.
*******************************************************************************/
int minegun_xy_cmp(void *v1, void *v2);

/***************************************************************************//**
	\fn			int minegun_destoried_cmp(void *v1, void *v2)
	\brief		compare destoried minegun(for dlist operation).
	\param[in]	v1 :pointer to minegun.
	\param[in]	v2 :no use, can be set NULL.
	\return		0:equal/1:not equal.
*******************************************************************************/
int minegun_destoried_cmp(void *v1, void *v2);

#ifdef __cplusplus
}
#endif
#endif //_LANDMINE_H
/*@}*/
