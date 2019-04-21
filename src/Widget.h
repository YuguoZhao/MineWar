/**
	\addtogroup	UILib
	declaration of UI Lib.
*/
/**
	\addtogroup Widget
	implementation of widget.
	\ingroup UILib
*/
/*@{*/
/***************************************************************************//**
	\file		Widget.h
	\brief		declaration of widget type and api.
	\author		XC
	\date		2016-7-8
	\version	1.0.1
*******************************************************************************/
#ifndef _WIDGET_H
#define _WIDGET_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "Type.h"

/**
	\def TOUCH_ON
	touch on state.
	\def TOUCH_OFF
	touch off state.
*/
#define TOUCH_ON 			1
#define TOUCH_OFF			0

/**
	\def NO_EVENT
	no event for process.
*/
#define NO_EVENT			0

/**
	\def PROPERTY_DISABLE
	property disable.
	\def PROPERTY_HIDE
	property hide.
*/
#define PROPERTY_DISABLE	0x1
#define PROPERTY_HIDE		0x2

/**
	\def WGT_DATA(id0,type0,x0,y0,w0,h0,gw0,gh0)
	widget table item.
	\param[in]	id0 :widget id.
	\param[in]	type0 :widget type.
	\param[in]	x0 :widget x coordinate.
	\param[in]	y0 :widget y coordinate.
	\param[in]	w0 :widget width.
	\param[in]	h0 :widget height.
	\param[in]	gw0 :grid width(for touch matrix).
	\param[in]	gh0 :grid height(for touch matrix).
*/
#define WGT_DATA(id0,type0,x0,y0,w0,h0,gw0,gh0) \
        {id0, type0, x0, y0, w0, h0, gw0, gh0}

/**
	\struct WidgetInfo_t
	widget table item.
*/
typedef struct{
    int wid;	/**< widget id */
    int wtype;	/**< widget type */
    int x;		/**< widget x coordinate */
    int y;		/**< widget y coordinate */
    int w;		/**< widget width */
    int h;		/**< widget height */
	int gw;		/**< grid width(for touch matrix) */
	int gh;		/**< grid height(for touch matrix) */
} WidgetInfo_t;

/**
	\typedef bool (*fp_isInRect)(void *_self, int x0, int y0)
	judge whether coordinate is in widget.
	\param[in]	_self :self pointer.
	\param[in]	x0 :coordinate x.
	\param[in]	y0 :coordinate y.
	\return		0:not in widget/1:in widget.
*/
typedef bool (*fp_isInRect)(void *_self, int x0, int y0);

/**
	\typedef void (*fp_show)(void *_self)
	show widget.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_show)(void *_self);

/**
	\typedef void (*fp_hide)(void *_self)
	hide widget.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_hide)(void *_self);

/**
	\typedef bool (*fp_isHiden)(void *_self)
	judge whether widget is hiden.
	\param[in]	_self :self pointer.
	\return		0:not hiden/1:hiden.
*/
typedef bool (*fp_isHiden)(void *_self);

/**
	\typedef void (*fp_enable)(void *_self)
	enable widget.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_enable)(void *_self);

/**
	\typedef void (*fp_disable)(void *_self)
	disable widget.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_disable)(void *_self);

/**
	\typedef bool (*fp_isDisabled)(void *_self)
	judge whether widget is disable.
	\param[in]	_self :self pointer.
	\return		0:not disabled/1:disabled.
*/
typedef bool (*fp_isDisabled)(void *_self);

/**
	\typedef void (*fp_onTouch)(void *_self, int x0, int y0)
	touch on/move/off in widget.
	\param[in,out]	_self :self pointer.
	\param[in]	x0 :coordinate x.
	\param[in]	y0 :coordinate y.
*/
typedef void (*fp_onTouch)(void *_self, int x0, int y0);

/**
	\typedef void (*fp_onTouchClear)(void *_self)
	clear touch state.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_onTouchClear)(void *_self);

/**
	\typedef void (*fp_setEvent)(void *_self, int mid, int event, int p1, int p2, int p3, int p4);
	send event to widget.
	\param[in,out]	_self :self pointer.
	\param[in]	mid :message id.
	\param[in]	event :event.
	\param[in]	p1 :paramter 1.
	\param[in]	p2 :paramter 2.
	\param[in]	p3 :paramter 3.
	\param[in]	p4 :paramter 4.
*/
typedef void (*fp_setEvent)(void *_self, int mid, int event, int p1, int p2, int p3, int p4);

/**
	\typedef Msg_t* (*fp_getEvent)(void *_self)
	get event.
	\param[in,out]	_self :self pointer.
	\return		message address.
*/
typedef Msg_t* (*fp_getEvent)(void *_self);

/**
	\typedef void (*fp_clearEvent)(void *_self)
	clear event.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_clearEvent)(void *_self);

/**
	\typedef int (*fp_getId)(void *_self)
	get widget id.
	\param[in,out]	_self :self pointer.
	\return		widget id.
*/
typedef int (*fp_getId)(void *_self);

/**
	\struct Widget_t
	widget.
*/
typedef struct{
    int mId;		/**< widget id */
    int mX;			/**< x coordinate */
    int mY;			/**< y coordinate */
    int mW;			/**< width */
    int mH;			/**< height */
    
    int mTX;		/**< touch point x */
    int mTY;		/**< touch point y */
    
    int mState;		/**< touch state */
    int mProperty;	/**< property */
    
    Msg_t *mMsg;	/**< message pointer */

	fp_isInRect isInRect;		/**< range judge api */
	fp_show show;				/**< set show api */
	fp_hide hide;				/**< set hide api */
	fp_isHiden isHiden;			/**< hiden judge api */
	fp_enable enable;			/**< enable api */
	fp_disable disable;			/**< disable api */
	fp_isDisabled isDisabled;	/**< disable judge api */
	fp_onTouch onTouchOn;		/**< touch on api */
	fp_onTouch onTouchOff;		/**< touch off api */
	fp_onTouch onTouchMove;		/**< touch move api */
	fp_onTouchClear onTouchClear;/**< touch clear api */
	fp_setEvent setEvent;		/**< set event api */
	fp_getEvent getEvent;		/**< get event api */
	fp_clearEvent clearEvent;	/**< clear event api */
	fp_getId getId;				/**< get widget id api */
} Widget_t;

/***************************************************************************//**
	\fn			void Widget_init(Widget_t *_self)
	\brief		initial widget object.
	\param[out]	_self :pointer to widget object.
	\remarks	this function must be called before using api.
*******************************************************************************/
void Widget_init(Widget_t *_self);

/***************************************************************************//**
	\fn			void Widget_initWith(Widget_t *_self, int wid0, 
					int x0, int y0, int w0, int h0, Msg_t *msg0)
	\brief		initial view object with data.
	\param[out]	_self :pointer to widget object.
	\param[in]	wid0 :widget id.
	\param[in]	x0 :coordinate x.
	\param[in]	y0 :coordinate y.
	\param[in]	w0 :width.
	\param[in]	h0 :height.
	\param[in]	msg0 :message pointer.
	\remarks	this function must be called before using api.
*******************************************************************************/
void Widget_initWith(Widget_t *_self, int wid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0);

#ifdef __cplusplus
}
#endif
#endif //_WIDGET_H
/*@}*/
