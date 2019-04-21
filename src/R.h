/**
	\addtogroup Resource
	implementation of image resource.
	\ingroup UI
*/
/*@{*/
/***************************************************************************//**
	\file		R.h
	\brief		declaration of resource id and api.
	\author		XD/XE
	\date		2016-7-11
	\version	1.0.1
*******************************************************************************/

#ifndef _R_H
#define _R_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
	\enum res_id_t
	resource id.
*/
typedef enum{
    R_BTN_AIM_CURSOR = 0,
    R_BTN_BACK_N,
    R_BTN_BACK,
    R_BTN_CANCEL,
    R_BTN_CURSOR,
    R_BTN_DOWN,
    R_BTN_HELP,
    R_BTN_HONOR,
    R_BTN_MENU,
    R_BTN_NEXT,
    R_BTN_OFF,
    R_BTN_OK,
    R_BTN_ON,
    R_BTN_OPTIONS,
    R_BTN_PAUSE,
    R_BTN_PLAY_X2,
    R_BTN_PLAY,
    R_BTN_REPLAY,
    R_BTN_SAVE,
    R_BTN_STOP,
    R_BTN_UP,
    R_BTN_VIDEO,
    R_BULLET_0,
    R_BULLET_1,
    R_BULLET_2,
    R_BULLET_MG_0,
    R_BULLET_MG_1,
    R_BULLET_MG_2,
    R_BULLET_MG_3,
    R_ENEMY_GB_0,
    R_ENEMY_GB_1,
    R_ENEMY_GB_2,
    R_ENEMY_GB_3,
    R_ENEMY_QC_0,
    R_ENEMY_QC_1,
    R_ENEMY_QC_2,
    R_ENEMY_QC_3,
    R_ENEMY_SB_0,
    R_ENEMY_SB_1,
    R_ENEMY_SB_2,
    R_ENEMY_SB_3,
    R_ENEMY_TK_0,
    R_ENEMY_TK_1,
    R_ENEMY_TK_2,
    R_ENEMY_TK_3,
    R_ENEMY_ZJ_0,
    R_ENEMY_ZJ_1,
    R_ENEMY_ZJ_2,
    R_ENEMY_ZJ_3,
    R_ENTRANCE_L,
    R_ENTRANCE_R,
    R_ENTRANCE_U,
    R_ENTRANCE_D,
    R_EXP_0,
    R_EXP_1,
    R_EXP_2,
    R_EXP_3_0_0,
    R_EXP_3_0_1,
    R_EXP_3_0_2,
    R_EXP_3_1_0,
    R_EXP_3_1_1,
    R_EXP_3_1_2,
    R_EXP_3_2_0,
    R_EXP_3_2_1,
    R_EXP_3_2_2,
    R_EXP_4_0_0,
    R_EXP_4_0_1,
    R_EXP_4_0_2,
    R_EXP_4_1_0,
    R_EXP_4_1_1,
    R_EXP_4_1_2,
    R_EXP_4_2_0,
    R_EXP_4_2_1,
    R_EXP_4_2_2,
    R_EXP_5_0_0,
    R_EXP_5_0_1,
    R_EXP_5_0_2,
    R_EXP_5_1_0,
    R_EXP_5_1_1,
    R_EXP_5_1_2,
    R_EXP_5_2_0,
    R_EXP_5_2_1,
    R_EXP_5_2_2,
    R_EXPLOSE_0,
    R_EXPLOSE_1,
    R_EXPLOSE_2,
    R_EXPLOSE_3,
    R_EXPLOSE_4,
    R_EXPLOSE_5,
    R_EXPLOSE_6,
    R_FISH,
    R_HONOR_STAR_B_S,
    R_HONOR_STAR_B,
    R_HONOR_STAR_E_S,
    R_HONOR_STAR_E,
    R_HONOR_STAR,
    R_HOUSE_DESTORY,
    R_HOUSE_DESTORY_2,
    R_HOUSE_DESTORY_BIG,
    R_HOUSE,
    R_ICON_COIN,
    R_ICON_DING,
    R_ICON_LARGE_SHADOW,
    R_LOCK,
    R_LOGO_MINE,
    R_LOGO_WAR,
    R_LOGO,
    R_MAP_FOREST_S,
    R_MAP_FOREST,
    R_MAP_HOUSE_S,
    R_MAP_LAND_DANGER,
    R_MAP_LAND_S,
    R_MAP_LAND,
    R_MAP_ROAD_DANGER,
    R_MAP_ROAD_S,
    R_MAP_ROAD,
    R_MAP_WATER_DANGER,
    R_MAP_WATER_S,
    R_MAP_WATER,
    R_MINE_FT,
    R_MINE_FT2,
    R_MINE_FZ,
    R_MINE_FZ2,
    R_MINE_LB_R2,
    R_MINE_LB,
    R_MINE_LB2,
    R_MINE_PT,
    R_MINE_PT2,
    R_MINE_TL,
    R_MINE_TL2,
    R_MINEGUN_1_1,
    R_MINEGUN_1_2,
    R_MINEGUN_2_1,
    R_MINEGUN_2_2,
    R_MINEGUN,
    R_N_0,
    R_N_1,
    R_N_2,
    R_N_3,
    R_N_4,
    R_N_5,
    R_N_6,
    R_N_7,
    R_N_8,
    R_N_9,
    R_N_S,
    R_N_D,
    R_NEW_RECORD,
    R_PLANT_PLANTING_DRY,
    R_PLANT_PLANTING_MATURE,
    R_PLANT_PLANTING,
    R_PLANT_SEED,
    R_PLANT_SEEDLING_DRY,
    R_PLANT_SEEDLING,
    R_STAR_EMPTY,
    R_STAR_HOUSE,
    R_STAR_LANDMINE,
    R_STAR_PLANT,
    R_STAR,
    R_TOOL_AIM,
    R_TOOL_EXPLOSE,
    R_TOOL_KNIFE,
    R_TOOL_REMOTE,
    R_TOOL_SEED,
    R_TOOL_SHOVEL,
    R_TOOLBAR_KNIFE,
    R_TOOLBAR_MINE_FT,
    R_TOOLBAR_MINE_FZ,
    R_TOOLBAR_MINE_LB,
    R_TOOLBAR_MINE_PT,
    R_TOOLBAR_MINE_TL,
    R_TOOLBAR_MINEGUN,
    R_TOOLBAR_SEED,
    
    R_MAX
} res_id_t;

/***************************************************************************//**
	\fn			void R_load(int type)
	\brief		load resource.
	\param[in]	type :device type, see #dev_type_t.
*******************************************************************************/
void R_load(int type);

/***************************************************************************//**
	\fn			void R_free(void)
	\brief		free resource.
*******************************************************************************/
void R_free(void);

#ifdef __cplusplus
}
#endif
#endif //_R_H
/*@}*/
