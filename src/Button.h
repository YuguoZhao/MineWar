/**
	\addtogroup Button
	implementation of button.
	\ingroup UILib
*/
/*@{*/
/***************************************************************************//**
	\file		button.h
	\brief		declaration of button.
	\author		XC
	\date		2016-7-11
	\version	1.0.1
*******************************************************************************/
#ifndef _BUTTON_H
#define _BUTTON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "Widget.h"

/**
	\def EV_KEY_UP
	key up event.
	\def EV_KEY_DOWN
	key down event.
*/
#define EV_KEY_UP   	0x1101
#define EV_KEY_DOWN 	0x1102

/**
	\struct Button_t
	button.
*/
typedef struct{
	Widget_t super;
	Widget_t super_f;
	fp_onTouch onTouchOn;
	fp_onTouch onTouchOff;
} Button_t;

/***************************************************************************//**
	\fn			void Button_initWith(Button_t *_self, int wid0, 
					int x0, int y0, int w0, int h0, Msg_t *msg0)
	\brief		initial button object with data.
	\param[out]	_self :pointer to button object.
	\param[in]	wid0 :button id.
	\param[in]	x0 :coordinate x.
	\param[in]	y0 :coordinate y.
	\param[in]	w0 :width.
	\param[in]	h0 :height.
	\param[in]	msg0 :message pointer.
	\remarks	this function must be called before using api.
*******************************************************************************/
void Button_initWith(Button_t *_self, int wid0, int x0, int y0, int w0, int h0, Msg_t *msg0);

#ifdef __cplusplus
}
#endif
#endif //_BUTTON_H
/*@}*/
