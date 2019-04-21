/**
	\addtogroup TouchMatrix
	implementation of touch matrix.
	\ingroup UILib
*/
/*@{*/
/***************************************************************************//**
	\file		touchmtx.h
	\brief		declaration of touch matrix.
	\author		XC
	\date		2016-7-11
	\version	1.0.1
*******************************************************************************/
#ifndef _TOUCHMTX_H
#define _TOUCHMTX_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "Widget.h"

/**
	\def EV_MTX_UP
	matrix up event.
	\def EV_MTX_DOWN
	matrix down event.
*/
#define EV_MTX_UP   	0x1201
#define EV_MTX_DOWN 	0x1202

/**
	\struct TouchMtx_t
	touch matrix.
*/
typedef struct{
	Widget_t super;
	Widget_t super_f;

	double gw;
    double gh;
    int gx;
    int gy;
	
	fp_onTouch onTouchOn;
	fp_onTouch onTouchOff;
} TouchMtx_t;

/***************************************************************************//**
	\fn			void TouchMtx_initWith(TouchMtx_t *_self, int wid0, 
					int x0, int y0, int w0, int h0, double gw0, double gh0, 
					Msg_t *msg0)
	\brief		initial touch matrix object with data.
	\param[out]	_self :pointer to touch matrix object.
	\param[in]	wid0 :button id.
	\param[in]	x0 :coordinate x.
	\param[in]	y0 :coordinate y.
	\param[in]	w0 :width.
	\param[in]	h0 :height.
	\param[in]	gw0 :grid width.
	\param[in]	gh0 :grid height.
	\param[in]	msg0 :message pointer.
	\remarks	this function must be called before using api.
*******************************************************************************/
void TouchMtx_initWith(TouchMtx_t *_self, int wid0, 
	int x0, int y0, int w0, int h0, double gw0, double gh0, Msg_t *msg0);

#ifdef __cplusplus
}
#endif
#endif //_TOUCHMTX_H
/*@}*/
