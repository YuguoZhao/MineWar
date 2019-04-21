/**
	\addtogroup ViewStack
	declaration of view stack.
	\ingroup UILib
*/
/*@{*/
/***************************************************************************//**
	\file		ViewStack.h
	\brief		declaration of view stack type and api.
	\author		XC
	\date		2016-7-13
	\version	1.0.1
*******************************************************************************/
#ifndef _VIEWSTACK_H
#define _VIEWSTACK_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "View.h"

/**
	\def TRANS_NONE
	no transfer.
	\def TRANS_CALL
	call transfer. \n
	current view will be covered and specified view will become top view.
	\def TRANS_RETURN
	return transfer. \n
	current view will return and the covered view will become top view again.
	\def TRANS_CHANGE
	change transfer. \n
	current view will be replaced by specified view.
*/
#define TRANS_NONE      0
#define TRANS_CALL      1
#define TRANS_RETURN    2
#define TRANS_CHANGE    3

#define STACK_SIZE		32

/**
	\typedef void (*fp_regView)(void *_self, int vid, View_t* view)
	register view api.
	\param[in,out]	_self :self pointer.
	\param[in]	vid :view id.
	\param[in]	view :view object address.
*/
typedef void (*fp_regView)(void *_self, int vid, View_t* view);

/**
	\typedef void (*fp_setInPara)(void *_self, int vid, Transfer_t* trans)
	set input parameter api.
	\param[in,out]	_self :self pointer.
	\param[in]	vid :view id.
	\param[in]	trans :transfer parameter address.
*/
typedef void (*fp_setInPara)(void *_self, int vid, Transfer_t* trans);

/**
	\typedef void (*fp_push1stView)(void *_self, int vid)
	push first view into stack.
	\param[in,out]	_self :self pointer.
	\param[in]	vid :view id.
*/
typedef void (*fp_push1stView)(void *_self, int vid);

/**
	\typedef void (*fp_callView)(void *_self, int vid)
	call view.
	\param[in,out]	_self :self pointer.
	\param[in]	vid :view id.
*/
typedef void (*fp_callView)(void *_self, int vid);

/**
	\typedef void (*fp_returnView)(void *_self)
	return view.
	\param[in,out]	_self :self pointer.
*/
typedef void (*fp_returnView)(void *_self);

/**
	\typedef void (*fp_changeView)(void *_self, int vid)
	change view.
	\param[in,out]	_self :self pointer.
	\param[in]	vid :view id.
*/
typedef void (*fp_changeView)(void *_self, int vid);

/**
	\typedef View_t* (*fp_getTopView)(void *_self)
	get top view.
	\param[in,out]	_self :self pointer.
	\return		pointer to top view.
*/
typedef View_t* (*fp_getTopView)(void *_self);

/**
	\typedef View_t* (*fp_transfer)(void *_self)
	do transfer.
	\param[in,out]	_self :self pointer.
	\return		pointer to top view.
*/
typedef  View_t* (*fp_transfer)(void *_self);

/**
	\struct ViewStack_t
	view stack.
*/
typedef struct{
	View_t* mStack[STACK_SIZE];
	View_t* mIndex[STACK_SIZE];
	int mSp;
	
	fp_regView regView;			/**< register view api */
	fp_setInPara setInputPara;	/**< set input parameter api */
	fp_push1stView push1stView;	/**< push first view api */
	fp_callView callView;		/**< call view api */
	fp_returnView returnView;	/**< return view api */
	fp_changeView changeView;	/**< change view api */
	fp_getTopView getTopView;	/**< get top view api */
	fp_transfer transfer;		/**< do transfer api */
} ViewStack_t;

/***************************************************************************//**
	\fn			void ViewStack_init(ViewStack_t *_self)
	\brief		initial view stack object.
	\param[out]	_self :pointer to view stack object.
	\remarks	this function must be called before using api.
*******************************************************************************/
void ViewStack_init(ViewStack_t *_self);

#ifdef __cplusplus
}
#endif
#endif	//_VIEWSTACK_H
/*@}*/