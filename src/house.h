/**
	\addtogroup	House
	implementation of house data.
	\ingroup GameCore
*/
/*@{*/
/***************************************************************************//**
	\file		house.h
	\brief		declaration of house type and api.
	\author		XB
	\date		2016-7-11
	\version	1.0.1
*******************************************************************************/
#ifndef _HOUSE_H
#define _HOUSE_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
	\def HOUSE_LIFE
	life of house.
*/
#define HOUSE_LIFE		50

/**
	\struct house_t
	house data.
*/
typedef struct{
	int id;		/**< id */
	int x;		/**< coordinate x */
	int y;		/**< coordinate y */
	int life;	/**< life */
} house_t;

/***************************************************************************//**
	\fn			int house_xy_cmp(void *v1, void *v2)
	\brief		compare coordinate of house(for dlist operation).
	\param[in]	v1 :pointer to house.
	\param[in]	v2 :pointer to house.
	\return		0:equal/1:not equal.
*******************************************************************************/
int house_xy_cmp(void *v1, void *v2);

/***************************************************************************//**
	\fn			int house_living_cmp(void *v1, void *v2)
	\brief		compare life of house(for dlist operation).
	\param[in]	v1 :pointer to house.
	\param[in]	v2 :pointer to house.
	\return		0:equal/1:not equal.
*******************************************************************************/
int house_living_cmp(void *v1, void *v2);

/***************************************************************************//**
	\fn			int house_demage_cmp(void *v1, void *v2)
	\brief		compare demage of house(for dlist operation).
	\param[in]	v1 :pointer to house.
	\param[in]	v2 :no use, can be set NULL.
	\return		0:equal/1:not equal.
*******************************************************************************/
int house_demage_cmp(void *v1, void *v2);

#ifdef __cplusplus
}
#endif
#endif //_HOUSE_H
/*@}*/
