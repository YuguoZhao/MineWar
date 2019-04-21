/**
	\addtogroup	GraphicLib
	implementation of graphic library.
*/
/**
	\addtogroup	DrawAPI
	declaration of graphic library.
	\ingroup GraphicLib
*/
/*@{*/
/***************************************************************************//**
	\file		GL.h
	\brief		declaration of graphic type and api.
	\author		XD
	\date		2016-7-11
	\version	1.0.1
*******************************************************************************/
#ifndef _GL_H
#define _GL_H

#include "c.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
	\def C_RGBA(r,g,b,a)
	get color with r, g, b, a.
	\param[in]	r :red. 0~255.
	\param[in]	g :green. 0~255.
	\param[in]	b :blue. 0~255.
	\param[in]	a :alpha. 0~255.
	\return		color, type is int.
*/
#define C_RGBA(r,g,b,a)	(((r)&0x000000FF)|(((g)&0x000000FF)<<8)|(((b)&0x000000FF)<<16)|(((a)&0x000000FF)<<24))

/**
	\def C_RGB(r,g,b)
	get color with r, g, b. (alpha is set 255 default)
	\param[in]	r :red, 0~255.
	\param[in]	g :green, 0~255.
	\param[in]	b :blue, 0~255.
	\return		color, type is int.
*/
#define C_RGB(r,g,b)	(((r)&0x000000FF)|(((g)&0x000000FF)<<8)|(((b)&0x000000FF)<<16)|(((255)&0x000000FF)<<24))

/**
	\struct GL_t
	graphic lib.
*/
typedef struct{
	/**
		\fn void (*drawImage2)(double x, double y, int id, int a)
		draw image.
		\param[in]	x :coordinate x.
		\param[in]	y :coordinate y.
		\param[in]	id :image id.
		\param[in]	a :alpha, 0~255.
	*/
	void (*drawImage2)(double x, double y, int id, int a);		/**< draw image(with alpha) api */
	/**
		\fn void (*drawImage)(double x, double y, int id)
		draw image. (alpha is set 255 default)
		\param[in]	x :coordinate x.
		\param[in]	y :coordinate y.
		\param[in]	id :image id.
	*/
	void (*drawImage)(double x, double y, int id);
	/**
		\fn void (*drawText)(double x, double y, const char *text)
		draw text. (color is set white default)
		\param[in]	x :coordinate x.
		\param[in]	y :coordinate y.
		\param[in]	text :text data.
	*/
	void (*drawText)(double x, double y, const char *text);
	/**
		\fn void (*drawText2)(double x, double y, const char *text, UIColor color)
		draw text(with color).
		\param[in]	x :coordinate x.
		\param[in]	y :coordinate y.
		\param[in]	text :text data.
		\param[in]	color :text color.
	*/
	void (*drawText2)(double x, double y, const char *text, UIColor color);
	/**
		\fn void (*drawTextC)(double x, double y, const char *text)
		draw text(align center). (color is set white default)
		\param[in]	x :coordinate x.
		\param[in]	y :coordinate y.
		\param[in]	text :text data.
	*/
	void (*drawTextC)(double x, double y, const char *text);
	/**
		\fn void (*drawTextR)(double x, double y, const char *text)
		draw text(align right). (color is set white default)
		\param[in]	x :coordinate x.
		\param[in]	y :coordinate y.
		\param[in]	text :text data.
	*/
	void (* drawTextR)(double x, double y, const char *text);			/**< draw text(align right) api */
	/**
		\fn void (*drawRectFill)(double x1, double y1, double x2, double y2, UIColor color)
		fill rectangle(no alpha).
		\param[in]	x1 :coordinate x of left-top.
		\param[in]	y1 :coordinate y of left-top.
		\param[in]	x2 :coordinate x of right-bottom.
		\param[in]	y2 :coordinate y of right-bottom.
		\param[in]	color :line color or fill color.
	*/
	void (*drawRectFill)(double x1, double y1, double x2, double y2, UIColor color);		/**< fill retangle(no alpha) api */
	/**
		\fn void (*drawRectFill2)(double x1, double y1, double x2, double y2, UIColor color)
		fill rectangle.
		\param[in]	x1 :coordinate x of left-top.
		\param[in]	y1 :coordinate y of left-top.
		\param[in]	x2 :coordinate x of right-bottom.
		\param[in]	y2 :coordinate y of right-bottom.
		\param[in]	color :line color or fill color.
	*/
	void (*drawRectFill2)(double x1, double y1, double x2, double y2, UIColor color);		/**< fill retangle api */
	/**
		\fn void (*drawRect)(double x1, double y1, double x2, double y2, UIColor color)
		draw rectangle.
		\param[in]	x1 :coordinate x of left-top.
		\param[in]	y1 :coordinate y of left-top.
		\param[in]	x2 :coordinate x of right-bottom.
		\param[in]	y2 :coordinate y of right-bottom.
		\param[in]	color :line color or fill color.
	*/
	void (*drawRect)(double x1, double y1, double x2, double y2, UIColor color);			/**< draw retangle api */

	/**
		\fn void (*addImage)(int index, const char *fileName)
		add a resource file.
		\param[in]	index :resource index, range is 0~total-1.
		\param[in]	fileName :file name.
	*/
	void (*addImage)(int index, const char *fileName);
	/**
		\fn void (*allocResArray)(int total)
		allocate resource array.
		\param[in]	total :resource total.
	*/
	void (*allocResArray)(int total);
	/**
		\fn void (*freeResArray)(void)
		free resource array.
	*/
	void (*freeResArray)(void);	/**< free resource array api */
	/**
		\fn void (*loadFont)(const char *fileName)
		load font file.
		\param[in]	fileName :file name.
	*/
	void (*loadFont)(const char *fileName);
	/**
		\fn void (*setFontSize)(int size)
		set font size.
		\param[in]	size :font size.
	*/
	void (*setFontSize)(int size);
	/**
		\fn double (*getTextWidth)(const char *text)
		get text width.
		\param[in]	text :text.
		\return		text width.
	*/
	double (*getTextWidth)(const char *text);
	/**
		\fn void (*regVram)(unsigned char *vram, int w, int h)
		register vram address and size.
		\param[in]	vram :vram buffer.
		\param[in]	w :width.
		\param[in]	h :heidht.
	*/
	void (*regVram)(unsigned char *vram, int w, int h);
}GL_t;

/**
	\var GL
	graphic lib global object, for class function call.
*/
extern GL_t GL;

/***************************************************************************//**
	\fn			void GL_init(GL_t *gl)
	\brief		initial graphic lib object.
	\param[out]	gl :pointer to graphic lib object.
	\remarks	this function must be called before using api.
*******************************************************************************/
void GL_init(GL_t *gl);

#ifdef __cplusplus
}
#endif
#endif //_GL_H
/*@}*/
