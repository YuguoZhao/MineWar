/**
	\mainpage Mine War Project
	Mine War is a mini game for software development training.\n
	This is the interface definition of software modules.\n
	The interface includes macros, types(enum/struct/pointer) 
	and API functions.\n
	\n
	All rights reserved, 2016.
*/
/**
	\addtogroup AppFramework
	declaration of application framework.
*/
/*@{*/
/***************************************************************************//**
	\file		app.h
	\brief		declaration of application framework.
	\author		XA
	\date		2016-7-12
	\version	1.0.1
*******************************************************************************/
#ifndef _APP_H
#define _APP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "type.h"
#include "vopening.h"
#include "vgame.h"
#include "vmap.h"
#include "vhelp.h"
#include "vhonor.h"
#include "vcal.h"
#include "vqedit.h"
#include "vmedit.h"
#include "vstat.h"
#include "gl.h"
#include "l.h"
#include "r.h"
#include "c.h"
#include "utils.h"
#include "option.h"
#include "war.h"

//Event ID
#define EV_TIME_TICK        0x0001	/**< tick event(period=10ms) */
#define EV_PAUSE            0x0002	/**< pause event(app to backend) */
#define EV_RESUME           0x0003	/**< resume event(app to frontend) */

//View ID
#define VID_OPENING     	0		/**< opening view */
#define VID_GAME        	1		/**< game view */
#define VID_HELP     	  	2		/**< help view */
#define VID_HONOR       	3		/**< honor view */
#define VID_MAP         	4		/**< map view */
#define VID_CAL		    	5		/**< calibration view */
#define VID_MEDIT       	6		/**< map edit view */
#define VID_QEDIT       	7		/**< queue edit view */
#define VID_STAT	       	8		/**< statistics view */
#define VID_MAX         	9		/**< view id max */

/**
	\enum dev_type_t
	device type.
*/
typedef enum{
    DEV_3X_IPHONE6P = 0,/**< iPhone 6 Plus */
    DEV_2X_IPHONE6,		/**< iPhone 6 */
    DEV_2X_IPHONE5,		/**< iPhone 5 */
    DEV_2X_IPHONE4,		/**< iPhone 4 */
    DEV_1X_IPAD,		/**< iPhone iPad */
    DEV_2X_IPAD,		/**< iPhone iPad2 */
    
    RES_MAX
} dev_type_t;

/***************************************************************************//**
	\fn			void App_startup(void)
	\brief		app startup.
*******************************************************************************/
void App_startup(void);

/***************************************************************************//**
	\fn			void App_exit(void)
	\brief		app exit.
*******************************************************************************/
void App_exit(void);

/***************************************************************************//**
	\fn			void App_touchesBegan(int x, int y)
	\brief		touch begin process.
	\param[in]	x :coordinate x of touch point.
	\param[in]	y :coordinate y of touch point.
*******************************************************************************/
void App_touchesBegan(int x, int y);

/***************************************************************************//**
	\fn			void App_touchesEnded(int x, int y)
	\brief		touch end process.
	\param[in]	x :coordinate x of touch point.
	\param[in]	y :coordinate y of touch point.
*******************************************************************************/
void App_touchesEnded(int x, int y);

/***************************************************************************//**
	\fn			void App_touchesMoved(int x, int y)
	\brief		touch move process.
	\param[in]	x :coordinate x of touch point.
	\param[in]	y :coordinate y of touch point.
*******************************************************************************/
void App_touchesMoved(int x, int y);

/***************************************************************************//**
	\fn			void App_draw(void)
	\brief		draw app ui. for cycle process.
*******************************************************************************/
void App_draw(void);

/***************************************************************************//**
	\fn			void App_sendEvent(int event)
	\brief		send event to ui.
	\param[in]	event :event.
*******************************************************************************/
void App_sendEvent(int event);

/***************************************************************************//**
	\fn			int App_getDevType(void)
	\brief		get device type.
	\return		device type, see #dev_type_t.
*******************************************************************************/
int App_getDevType(void);

/***************************************************************************//**
	\fn			bool App_isCalEnable(void)
	\brief		judge whether calibration is enable.
	\return		true:enable/false:disable.
*******************************************************************************/
bool App_isCalEnable(void);

#ifdef __cplusplus
}
#endif
#endif //_APP_H
/*@}*/
