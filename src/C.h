/**
	\addtogroup	ColorAPI
	declaration of color.
	\ingroup GraphicLib
*/
/*@{*/
/***************************************************************************//**
	\file		c.h
	\brief		declaration of color api.
	\author		XD
	\date		2016-7-11
	\version	1.0.1
*******************************************************************************/
#ifndef _C_H
#define _C_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
	\typedef int UIColor
	color.
*/
typedef int UIColor;

/**
	\struct C_t
	color class.
*/
typedef struct{
	/**
		\fn UIColor (*RGBA)(int r, int g, int b, int a)
		get color with r, g, b, a.
		param[in]	r :red.
		param[in]	g :green.
		param[in]	b :blue.
		param[in]	a :alpha.
	*/
	UIColor (*RGBA)(int r, int g, int b, int a);
	/**
		\fn UIColor (*RGB)(int r, int g, int b)
		get color with r, g, b. alpha is set 255 default.
		param[in]	r :red.
		param[in]	g :green.
		param[in]	b :blue.
	*/
	UIColor (*RGB)(int r, int g, int b);
	/**
		\fn UIColor (*BGR)(void)
		get backgroud color.
		\return	background color.
	*/
	UIColor (*BGR)(void);
	/**
		\fn void (*setBGR)(int r, int g, int b)
		set background color.
		param[in]	r :red.
		param[in]	g :green.
		param[in]	b :blue.
	*/
	void (*setBGR)(int r, int g, int b);
} C_t;

/**
	\var C
	color global object, for class function call.
*/
extern C_t C;

/***************************************************************************//**
	\fn			void C_init(C_t *c)
	\brief		initial color object.
	\param[out]	c :pointer to color object.
	\remarks	this function must be called before using api.
*******************************************************************************/
void C_init(C_t *c);

#ifdef __cplusplus
}
#endif
#endif //_C_H
/*@}*/
