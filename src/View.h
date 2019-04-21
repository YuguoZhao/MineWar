/**
	\addtogroup View
	implementation of view.
	\ingroup UILib
*/
/*@{*/
/***************************************************************************//**
	\file		View.h
	\brief		declaration of view type and api.
	\author		XC
	\date		2016-7-13
	\version	1.0.1
*******************************************************************************/
#ifndef _VIEW_H
#define _VIEW_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "Type.h"
#include "Widget.h"

/**
	\def EV_SLIDE_L
	slide left.
	\def EV_SLIDE_R
	slide right.
	\def EV_SLIDE_U
	slide up.
	\def EV_SLIDE_D
	slide down.
*/
#define EV_SLIDE_L      0x1001
#define EV_SLIDE_R      0x1002
#define EV_SLIDE_U      0x1003
#define EV_SLIDE_D      0x1004

/**
	\def WGT_BTN
	widget type(button).
	\def WGT_MTX
	widget type(touch matrix).
*/
#define WGT_BTN         1
#define WGT_MTX         2

/**
	\def SLIDE_DET_NONE
	not detect slide none.
	\def SLIDE_DET_LR
	detect left-right slide.
	\def SLIDE_DET_UD
	detect up-down slide.
*/
#define SLIDE_DET_NONE  0x0
#define SLIDE_DET_LR    0x1
#define SLIDE_DET_UD    0x2

/**
	\struct Transfer_t
	transfer request.
*/
typedef struct{
    int currentViewId;	/**< current view id */
    int targetViewId;	/**< target view id */
    int type;			/**< transfer type */
    int p1;				/**< parameter 1 */
    int p2;				/**< parameter 2 */
    int p3;				/**< parameter 3 */
    int p4;				/**< parameter 4 */
} Transfer_t;

/**
	\typedef void (*fp_onCreate)(void *_self)
	onCreate.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_onCreate)(void *_self);

/**
	\typedef void (*fp_onEnter)(void *_self)
	onEnter.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_onEnter)(void *_self);

/**
	\typedef void (*fp_onExit)(void *_self)
	onExit.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_onExit)(void *_self);

/**
	\typedef void (*fp_onDraw)(void *_self)
	onDraw.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_onDraw)(void *_self);

/**
	\typedef void (*fp_onShow)(void *_self)
	onShow.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_onShow)(void *_self);

/**
	\typedef void (*fp_onHide)(void *_self)
	onHide.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_onHide)(void *_self);

/**
	\typedef void (*fp_procEvent)(void *_self)
	procEvent.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_procEvent)(void *_self);

/**
	\typedef bool (*fp_sendEvent)(void *_self, Msg_t *message)
	sendEvent.
	\param[in,out]	_self :self pointer.
	\param[in]	msg :message.
	\return		0:message not be processed/1:message be processed.
*/
typedef bool (*fp_sendEvent)(void *_self, Msg_t *msg);

/**
	\typedef void (*fp_setInputPara)(void *_self, Transfer_t* trans)
	setInputPara.
	\param[in,out]	_self :self pointer.
	\param[in]	trans :transfer request.
*/
typedef void (*fp_setInputPara)(void *_self, Transfer_t* trans);

/**
	\typedef void (*fp_setInputPara)(void *_self, Transfer_t* trans)
	setInputPara.
	\param[in,out]	_self :self pointer.
	\param[in]	trans :transfer request.
*/
typedef void (*fp_setTransfer)(void *_self, int target, int type, int p1, int p2, int p3, int p4);

/**
	\typedef void (*fp_regWidgets)(void *_self, WidgetInfo_t *array, int size)
	regWidgets.
	\param[in,out]	_self :self pointer.
	\param[in]	array :widget table.
	\param[in]	size :widget table size.
*/
typedef void (*fp_regWidgets)(void *_self, WidgetInfo_t *array, int size);

/**
	\typedef Transfer_t *(*fp_getTransfer)(void *_self)
	getTransfer.
	\param[in,out]	_self :self pointer.
	\return		transfer request.
*/
typedef Transfer_t *(*fp_getTransfer)(void *_self);

/**
	\typedef void (*fp_clearTransfer)(void *_self)
	clearTransfer.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_clearTransfer)(void *_self);

/**
	\typedef void (*fp_clearRefreshFlag)(void *_self)
	clearRefreshFlag.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_clearRefreshFlag)(void *_self);

/**
	\typedef bool (*fp_getRefreshFlag)(void *_self)
	getRefreshFlag.
	\param[in,out]	_self :self pointer.
	\return		refresh flag.
*/
typedef bool (*fp_getRefreshFlag)(void *_self);

/**
	\typedef void (*fp_setMoveDirection)(void *_self, int direction)
	setMoveDirection.
	\param[in,out]	_self :self pointer.
	\param[in]	direction :slide detect direction. \n
				SLIDE_DET_LR or SLIDE_DET_LR.
*/
typedef void (*fp_setMoveDirection)(void *_self, int direction);

/**
	\typedef void (*fp_setMoveThreshold)(int threshold)
	setMoveThreshold.
	\param[in]	threshold :slide detect threshold.
*/
typedef void (*fp_setMoveThreshold)(int threshold);

/**
	\struct View_t
	view.
*/
typedef struct{
	Widget_t super;			/**< super class object */
	Widget_t super_f;		/**< super class function */

	int mTX0;				/**< touch x */
    int mTY0;				/**< touch y */
    bool mRefreshFlag;		/**< refresh flag */
    int mMoveDirection;		/**< slide detect direction */
    Widget_t** mWidgetArray;/**< widget array */
	int mWidgetCount;		/**< widget total */
    Transfer_t mTransfer;	/**< transfer request */
    Transfer_t mInputPara;	/**< input parameter */

	fp_onCreate onCreate;	/**< onCreate */
	fp_onEnter onEnter;		/**< onEnter */
	fp_onExit onExit;		/**< onExit */
	fp_onHide onHide;		/**< onHide */
	fp_onShow onShow;		/**< onShow */
	fp_onTouch onTouchOn;	/**< onTouchOn */
	fp_onTouch onTouchOff;	/**< onTouchOff */
	fp_onTouch onTouchMove;	/**< onTouchMove */
	fp_onDraw onDraw;		/**< onDraw */
	fp_procEvent procEvent;	/**< procEvent */
	fp_sendEvent sendEvent;	/**< sendEvent */
	fp_regWidgets regWidgets;		/**< regWidgets */
	fp_setInputPara setInputPara;	/**< setInputPara */
	fp_setTransfer setTransfer;		/**< setTransfer */
	fp_getTransfer getTransfer;		/**< getTransfer */
	fp_clearTransfer clearTransfer;	/**< clearTransfer */
	fp_clearRefreshFlag clearRefreshFlag;	/**< clearRefreshFlag */
	fp_getRefreshFlag getRefreshFlag;		/**< getRefreshFlag */
	fp_setMoveDirection setMoveDirection;	/**< setMoveDirection */
	fp_setMoveThreshold setMoveThreshold;	/**< setMoveThreshold */
} View_t;

/**
	\var View
	view global object, for class function call.
*/
extern View_t View;

/***************************************************************************//**
	\fn			void void View_init(View_t *_self)
	\brief		initial view object.
	\param[out]	_self :pointer to view object.
	\remarks	this function must be called before using api.
*******************************************************************************/
void View_init(View_t *_self);

/***************************************************************************//**
	\fn			void View_initWith(View_t *_self, int vid0, 
					int x0, int y0, int w0, int h0, Msg_t *msg0)
	\brief		initial view object with data.
	\param[out]	_self :pointer to view object.
	\param[in]	vid0 :view id.
	\param[in]	x0 :coordinate x.
	\param[in]	y0 :coordinate y.
	\param[in]	w0 :width.
	\param[in]	h0 :height.
	\param[in]	msg0 :message pointer.
	\remarks	this function must be called before using api.
*******************************************************************************/
void View_initWith(View_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0);

#ifdef __cplusplus
}
#endif
#endif	//_VIEW_H
/*@}*/
