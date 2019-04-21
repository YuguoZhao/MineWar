
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DISPDRV_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DISPDRV_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef DISPDRV_EXPORTS
#define DISPDRV_API __declspec(dllexport)
#else
#define DISPDRV_API __declspec(dllimport)
#endif

/**
	\addtogroup	DispDrv
	simulator display panel driver.
*/
/*@{*/
/**
	\file		dispdrv.h
	\brief		simulator display panel driver.
	\author		y.g.zhao
	\date		2013-7-1
	\version	1.0.1
*/

#ifndef _DISPDRV_H
#define _DISPDRV_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
	\fn			DISPDRV_API int disp_drv_init(int w, int h, int bit)
	\brief		initial simulator display driver.
	\param[in]	w :Width, w > 0 and w%8 must equal 0.
	\param[in]	h :Height, h > 0.
	\param[in]	bit :color deepth, range is 1,2,4,8,16,24,32.
	\return		0: ok.\n
				-1: w or h is error(w<=0 or h<=0 or w%8!=0).\n
				-2: bit is not 1,2,4,8,16,24,32.
*/
DISPDRV_API int disp_drv_init(int w, int h, int bit);

/**
	\fn			DISPDRV_API int disp_drv_send_data(unsigned char *data)
	\brief		send screen data.
	\param[in]	data :screen data.
	\return		0: ok.\n
				-1: error.
*/
DISPDRV_API int disp_drv_send_data(unsigned char *data);

/**
	\fn			DISPDRV_API int disp_drv_get_key(void)
	\brief		get key code.
	\return		0~0xFFFE: key down.\n
				0xFFFF: key up.\n
				-1: error.
*/
DISPDRV_API int disp_drv_get_key(void);

/**
	\fn			DISPDRV_API int disp_drv_get_touch(
					unsigned char *status, int *x, int *y)
	\brief		get touch status and coordinate.
	\param[out]	status :0-No Touch,1-Touching.
	\param[out]	x :X Coordinate.
	\param[out]	y :Y Coordinate.
*/
DISPDRV_API int disp_drv_get_touch(unsigned char *status, int *x, int *y);

/**
	\fn			DISPDRV_API int disp_drv_get_touch2(
					unsigned char *status, int *x, int *y)
	\brief		get second touch point status and coordinate. for multi-touch.
	\param[out]	status :0-No Touch, 1-Touching.
	\param[out]	x :X Coordinate.
	\param[out]	y :Y Coordinate.
*/
DISPDRV_API int disp_drv_get_touch2(unsigned char *status, int *x, int *y);

/**
	\fn			DISPDRV_API int disp_drv_get_encoder(
					unsigned char *status, unsigned char *id, int *angle)
	\brief		get rotary encoder status and angle.
	\param[out]	status :0-Not rotating, 1-rotating.
	\param[out]	id :id of encoder, begin from 0,base on order.
	\param[out] angle :current angle(0-359), NOT changed angle.
*/
DISPDRV_API int disp_drv_get_encoder(unsigned char *status, unsigned char *id, int *angle);

#ifdef __cplusplus
}
#endif
#endif //_DISPDRV_H
/*@}*/

