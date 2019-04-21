/**
	\addtogroup UI
	implementation of UI layout data.
*/
/**
	\addtogroup Layout
	declaration of layout.
	\ingroup UI
*/
/*@{*/
/***************************************************************************//**
	\file		L.h
	\brief		declaration of layout id and api.
	\author		XD/XE
	\date		2016-7-8
	\version	1.0.1
*******************************************************************************/
#ifndef _L_H
#define _L_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "Widget.h"

/**
	\enum layout_id_t
	index of layout data(coordinate or size).
*/
typedef enum{
    L_SCR_W 		= 0,
    L_SCR_H 		,
    L_SCR_X0 		,
    L_SCR_Y0 		,
    L_X0 			,
    L_Y0 			,
    L_GRID_W 		,
    L_GRID_H 		,
    L_PLAY_MTX_X	,
    L_PLAY_MTX_Y	,
    L_PLAY_MTX_W	,
    L_PLAY_MTX_H	,
    L_LOGO_W 		,
    L_LOGO_MINE_W 	,
    L_LOGO_WAR_W 	,
    L_ICON_W_L      ,
    L_ICON_W_S      ,
    L_ICON_HO_X 	,
    L_ICON_HO_Y 	,
    L_ICON_A_X      ,
    L_ICON_A_Y      ,
    L_ICON_TEXT_Y	,
    L_ICON_OFFSET   ,
    L_MAP_PAGE_W	,
    L_MAP_PAGE_H	,
    L_MAP_PAGE_X2	,
    L_MAP_PAGE_Y	,
    L_MQ_EDIT_W		,
    L_MQ_EDIT_X		,
    L_MQ_EDIT_Y2	,
    L_ENTER_X		,
    L_ENTER_Y		,
    L_ENTER_W		,
    L_ENTER_H		,
    L_TITLE_X		,
    L_TEXT_Y		,
    L_HONOR_X		,
    L_HONOR_Y		,
    L_HONOR_W		,
    L_HONOR_H		,
    L_MN_MENU_X		,
    L_MN_REPLAY_X	,
    L_MN_NEXT_X		,
    L_MN_BTN_Y		,
    L_MN_BTN_W		,
    L_NUMBER_W		,
    L_BTN_PLAY_X	,
    L_BTN_PLAY_Y	,
    L_BACK_X		,
    L_BACK_Y		,
    L_PLAY_TB_X		,
    L_PLAY_TB_Y		,
    L_PLAY_TB_W		,
    L_PLAY_TB_H		,
    L_TB_ICON_X     ,
    L_TB_ICON_Y     ,
    L_BTN_MENU2_X   ,
    L_BTN_MENU2_Y	,
    L_BTN_SAVE2_X	,
    L_BTN_SAVE2_Y	,
    L_BK_ITEM_X		,
    L_BK_ITEM_W		,
    L_BK_MENU_Y		,
    L_BK_REPLAY_Y	,
    L_BK_CONTIN_Y	,
    L_MN_MENU2_X	,
    L_MN_REPLAY2_X	,
    L_CAL_ADJ_UP_X	,
    L_CAL_ADJ_DN_X	,
    L_CAL_ADJ_H		,
    L_CAL_EID_X     ,
    L_CAL_Q_X		,
    L_CAL_L_DN_X	,
    L_CAL_L_UP_X	,
    L_CAL_ITEM_Y	,
    L_CAL_ITEM_Y2	,
    L_LOCK_S_OX     ,
    L_ME_TB_X       ,
    L_ME_TB_Y       ,
    L_ME_TB_W		,
    L_ME_TB_H		,
    L_ME_SAVE_X     ,
    L_ME_SAVE_Y     ,
    L_LIST_X		,
    L_LIST_Y		,
    
    L_MAX
} layout_id_t;

/**
	\enum layout_type_t
	layout type(for diffrent device).
*/
typedef enum{
    LAYOUT_IPHONE6 	= 0,
    LAYOUT_IPHONE6P ,
    LAYOUT_IPHONE5 	,
    LAYOUT_IPHONE4 	,
    LAYOUT_IPAD 	,
    LAYOUT_IPADPRO 	,
    
    LAYOUT_MAX
} layout_type_t;

/***************************************************************************//**
	\fn			double L_n(int index)
	\brief		get layout data.
	\param[in]	index :index of data, see #layout_id_t.
	\return		layout data.
*******************************************************************************/
double L_n(int index);

/***************************************************************************//**
	\fn			double L_x(int index)
	\brief		get layout x.
	\param[in]	index :index of data, see #layout_id_t.
	\return		layout x coordinate.
*******************************************************************************/
double L_x(int index);

/***************************************************************************//**
	\fn			double L_y(int index)
	\brief		get layout y.
	\param[in]	index :index of data, see #layout_id_t.
	\return		layout y coordinate.
*******************************************************************************/
double L_y(int index);

/***************************************************************************//**
	\fn			void L_setDensity(int layout0, int density0)
	\brief		set layout type and density.
	\param[in]	layout0 :layout type, see #layout_type_t.
	\param[in]	density0 :density, range is 1,2,3.
*******************************************************************************/
void L_setDensity(int layout0, int density0);

/***************************************************************************//**
	\fn			void L_setWidgetData(WidgetInfo_t *array, int size)
	\brief		set layout type and density.
	\param[in,out]	array :widget data array.
	\param[in]	size :size of widget array.
*******************************************************************************/
void L_setWidgetData(WidgetInfo_t *array, int size);

#ifdef __cplusplus
}
#endif
#endif	//_L_H
/*@}*/
