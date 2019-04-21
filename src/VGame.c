#include "App.h"
#include "Button.h"
#include "TouchMtx.h"
#include "VGame.h"

#define	TAG					"vGame"

#define CTRL_BTN_MENU       0
#define CTRL_BTN_REPLAY     1
#define CTRL_BTN_NEXT       2
#define CTRL_MTX            3
#define CTRL_BTN_PLAY       4
#define CTRL_BTN_RETURN     5
#define CTRL_MTX_TB         6
#define CTRL_BK_MENU        7
#define CTRL_BK_REPLAY      8
#define CTRL_BK_CONTINUE    9
#define CTRL_BTN_MENU2      10
#define CTRL_BTN_REPLAY2    11

#define OPERATE_PT          0
#define OPERATE_TL          1
#define OPERATE_LB          2
#define OPERATE_FZ          3
#define OPERATE_FT          4
#define OPERATE_DIG         5
#define OPERATE_REMOTE      6
#define OPERATE_TIMER       7
#define OPERATE_PLANT       8
#define OPERATE_WATERING    9
#define OPERATE_HARVEST     10
#define OPERATE_EXPLOSE     11
#define OPERATE_MINEGUN     12
#define OPERATE_FIRE        13
#define OPERATE_MAX         14

#define OPERATE_MODE_POS_SELECT         0
#define OPERATE_MODE_OPERATING_SELECT   1
#define OPERATE_MODE_AIM                2

#define GAME_MODE_PLAY      0
#define GAME_MODE_PAUSE     1
#define GAME_MODE_OVER      2

#define TBAR_ROAD           0
#define TBAR_OTHER          1
#define TBAR_ID_TL          0
#define TBAR_ID_PT          1
#define TBAR_ID_FZ          2
#define TBAR_ID_FT          3
#define TBAR_ID_SEED        4
#define TBAR_ID_KNIFE       5
#define TBAR_ID_LB          6
#define TBAR_ID_MG          7

#define MENU_MODE_NONE      0
#define MENU_MODE_WIN       1
#define MENU_MODE_LOSE      2

#define WIDGET_HIDE(wid)	\
	_self->super.mWidgetArray[wid]->hide(_self->super.mWidgetArray[wid])
#define WIDGET_SHOW(wid)	\
	_self->super.mWidgetArray[wid]->show(_self->super.mWidgetArray[wid])

#define IS_EVENT(event0, mid0)	\
	(_self->super.super.mMsg->event == event0)	\
	&&(_self->super.super.mMsg->mid == mid0)

static void gameOver(VGame_t *_self);
static void backConfirm(VGame_t *_self);
static void backCancel(VGame_t *_self);
static void playPrepare(VGame_t *_self);
static void fieldTouchOff(VGame_t *_self);
static int getMenuMode(VGame_t *_self);
static int getOperationList(int operate[]);
static void getMenuPos(void);
static bool updateOperateIndex(int x0, int y0);

static void drawLifeBar(int x0, int y0, double len);
static void drawNumberC(int x0, int y0, int n, int color);
static void drawNumberCS(int x0, int y0, const char *tmp, int color);

static point_t cursorPos;
static point_t aimPos;
static point_t operatePos;
static int operateMode = OPERATE_MODE_POS_SELECT;
static int operateIndex = 0;
static int operateObj = 0;

static int speed = 0;

static const int operateRoad[]={
	OPERATE_TL,
	OPERATE_PT,
	OPERATE_FZ,
	OPERATE_FT
};

static const int operateLand[]={
	OPERATE_PLANT,
	OPERATE_MINEGUN
};

static const int operatePlant[]={
	OPERATE_WATERING,
	OPERATE_HARVEST
};

static const int operatePlantMature[]={
	OPERATE_HARVEST
};

static const int operateLandmine[]={
	OPERATE_DIG
};

static const int operateLandmineLB[]={
	OPERATE_REMOTE,
	//OPERATE_TIMER,
	OPERATE_DIG
};

static const int operateLandmineRemote[]={
	OPERATE_EXPLOSE
};

static const int operateLandmineRemote2[]={
	OPERATE_EXPLOSE,
	OPERATE_DIG
};

static const int operateLandmineTimer[]={
	OPERATE_DIG
};

static const int operateRoadSide[]={
	OPERATE_PLANT,
	OPERATE_LB,
	OPERATE_MINEGUN
};

static const int operateForest[]={
	OPERATE_MINEGUN
};

static const int operateMinegun[]={
	OPERATE_FIRE,
	OPERATE_DIG
};

static const int operateMinegunNoFire[]={
	OPERATE_DIG
};

static const int operateLand2[]={
	OPERATE_MINEGUN
};

static const int operateRoadSide2[]={
	OPERATE_LB,
	OPERATE_MINEGUN
};

static const int operateTree[]={
	OPERATE_WATERING,
	OPERATE_HARVEST
};

static const int operateTreeMature[]={
	OPERATE_WATERING,
	OPERATE_HARVEST
};

static const int* operateTable[]={
	operateRoad,
	operateLand,
	operatePlant,
	operatePlantMature,
	operateLandmine,
	operateLandmineLB,
	operateLandmineRemote,
	operateLandmineRemote2,
	operateLandmineTimer,
	operateRoadSide,
	operateForest,
	operateMinegun,
	operateMinegunNoFire,
	operateLand2,
	operateRoadSide2,
	operateTree,
	operateTreeMature
};

static const int operateTableLength[]={
    sizeof(operateRoad)/sizeof(int),
    sizeof(operateLand)/sizeof(int),
    sizeof(operatePlant)/sizeof(int),
    sizeof(operatePlantMature)/sizeof(int),
    sizeof(operateLandmine)/sizeof(int),
    sizeof(operateLandmineLB)/sizeof(int),
    sizeof(operateLandmineRemote)/sizeof(int),
    sizeof(operateLandmineRemote2)/sizeof(int),
    sizeof(operateLandmineTimer)/sizeof(int),
    sizeof(operateRoadSide)/sizeof(int),
    sizeof(operateForest)/sizeof(int),
    sizeof(operateMinegun)/sizeof(int),
    sizeof(operateMinegunNoFire)/sizeof(int),
    sizeof(operateLand2)/sizeof(int),
    sizeof(operateRoadSide2)/sizeof(int),
    sizeof(operateTree)/sizeof(int),
    sizeof(operateTreeMature)/sizeof(int)
};

static point_t menuPos[16];
static int menuLen = 0;

static void onCreate(VGame_t *_self)
{
    WidgetInfo_t controls[] = {
        WGT_DATA(CTRL_BTN_MENU	, WGT_BTN, L_MN_MENU_X,   L_MN_BTN_Y,   L_MN_BTN_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_BTN_REPLAY, WGT_BTN, L_MN_REPLAY_X, L_MN_BTN_Y,   L_MN_BTN_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_BTN_NEXT	, WGT_BTN, L_MN_NEXT_X,   L_MN_BTN_Y,   L_MN_BTN_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_MTX		, WGT_MTX, L_PLAY_MTX_X,  L_PLAY_MTX_Y, L_PLAY_MTX_W, L_PLAY_MTX_H, L_GRID_W, L_GRID_H),
        WGT_DATA(CTRL_BTN_PLAY	, WGT_BTN, L_BTN_PLAY_X,  L_BTN_PLAY_Y, L_GRID_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_BTN_RETURN, WGT_BTN, L_BTN_MENU2_X, L_BTN_MENU2_Y, L_GRID_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_MTX_TB	, WGT_MTX, L_PLAY_TB_X,   L_PLAY_TB_Y,  L_PLAY_TB_W, L_PLAY_TB_H, L_GRID_W, L_GRID_H),
        WGT_DATA(CTRL_BK_MENU	, WGT_BTN, L_BK_ITEM_X,   L_BK_MENU_Y,  L_BK_ITEM_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_BK_REPLAY	, WGT_BTN, L_BK_ITEM_X,   L_BK_REPLAY_Y,L_BK_ITEM_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_BK_CONTINUE,WGT_BTN, L_BK_ITEM_X,   L_BK_CONTIN_Y, L_BK_ITEM_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_BTN_MENU2	, WGT_BTN, L_MN_MENU2_X,  L_MN_BTN_Y,   L_MN_BTN_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_BTN_REPLAY2,WGT_BTN, L_MN_REPLAY2_X,L_MN_BTN_Y,   L_MN_BTN_W, L_GRID_H, 0, 0)
    };

	_self->super_f.onCreate(&_self->super);
	L_setWidgetData(controls, ARRAY_SIZE(controls));
	_self->super_f.regWidgets(&_self->super, controls, ARRAY_SIZE(controls));
	_self->mapIndex = _self->super.mInputPara.p1;
}

static void onEnter(VGame_t *_self)
{
    game_start(_self->mapIndex);
	playPrepare(_self);
	_self->backupFlag = false;
}

static void onExit(VGame_t *_self)
{
	game_end();
    
	/*if([Game getResumeFlag]){
        [Game backup:false];
		[Game saveBak];
	}
    
    [Utils enableIdleTimer];
    [MyApp setTimeInterval:TIME_INTERVAL];*/
}

static void onDraw(VGame_t *_self)
{
	int i;
	int j;
	int bmp;
	int map[MAP_H][MAP_W];
	int mapDanger[MAP_H][MAP_W];
	point_t entrances[4];
    int entryTotal;
	int direction[MAP_H][MAP_W];

	const int tbarIcons[] = {
        R_TOOLBAR_MINE_TL,
        R_TOOLBAR_MINE_PT,
        R_TOOLBAR_MINE_FZ,
        R_TOOLBAR_MINE_FT,
        R_TOOLBAR_SEED,
        R_TOOLBAR_KNIFE,
        R_TOOLBAR_MINE_LB,
        R_TOOLBAR_MINEGUN
    };

	int bmpEnemyTable[] = {
		R_ENEMY_SB_0,	//ENEMY_SB = 0,
		R_ENEMY_GB_0,	//ENEMY_GB,
		R_ENEMY_QC_0,	//ENEMY_QC,
		R_ENEMY_ZJ_0,	//ENEMY_ZJ,
		R_ENEMY_TK_0,	//ENEMY_TK,
	};

	int x0 = (int)L_x(L_PLAY_MTX_X);
	double y0 = L_y(L_PLAY_MTX_Y);
	int money;
    int num_x0;

	game_get_entrance(entrances, &entryTotal);
	
	//map
	game_get_map_data(map);
	game_get_danger_range(mapDanger);

    //GL.drawRect(L_n(L_X0), L_y(L_PLAY_MTX_Y)+0.5, L_n(L_GRID_W)*2-L_n(L_GRID_W)/8, L_n(L_GRID_W)*9, C.RGB(0, 128, 0));
	GL.drawRectFill(L_n(L_X0), L_y(L_PLAY_MTX_Y)+0.5, L_n(L_GRID_W)*2-L_n(L_GRID_W)/8, L_n(L_GRID_W)*9, C.RGB(0, 128, 0));

	for(i = 0; i < 4; i++){
        GL.drawImage(L_x(L_TB_ICON_X), L_n(L_GRID_H)*(2+i)+L_n(L_GRID_H)/2, tbarIcons[_self->tbarType*4+i]);
	}

    GL.drawImage(L_x(L_TB_ICON_X), L_n(L_GRID_H)/2+(2+_self->tbarItem%4)*L_n(L_GRID_H), R_BTN_CURSOR);

    GL.drawImage(L_x(L_TB_ICON_X), L_n(L_BTN_MENU2_Y), R_BTN_MENU);
	
	for(i = 0; i < MAP_H; i++){
		for(j = 0; j < MAP_W; j++){
			if(map[i][j] == FIELD_ROAD){
				if(mapDanger[i][j] != 0){
					bmp = R_MAP_ROAD_DANGER;
				}
				else{
					bmp = R_MAP_ROAD;
				}
			}
			else if(map[i][j] == FIELD_FOREST){
				bmp = R_MAP_FOREST;
			}
			else if(map[i][j] == FIELD_WATER){
				if(mapDanger[i][j] != 0){
					bmp = R_MAP_WATER_DANGER;
				}
				else{
					bmp = R_MAP_WATER;
				}
			}
			else{
				if(mapDanger[i][j] != 0){
					bmp = R_MAP_LAND_DANGER;
				}
				else{
					bmp = R_MAP_LAND;
				}
			}

			map[i][j] = bmp;
		}
	}
	
	game_get_direction_data(direction);
	
	for(i = 0; i < entryTotal; i++){
		if(direction[entrances[i].y][entrances[i].x] == MOVE_D){
			map[entrances[i].y][entrances[i].x] = R_ENTRANCE_D;
		}
		else if(direction[entrances[i].y][entrances[i].x] == MOVE_U){
			map[entrances[i].y][entrances[i].x] = R_ENTRANCE_U;
		}
		else if(direction[entrances[i].y][entrances[i].x] == MOVE_R){
			map[entrances[i].y][entrances[i].x] = R_ENTRANCE_R;
		}
		else if(direction[entrances[i].y][entrances[i].x] == MOVE_L){
			map[entrances[i].y][entrances[i].x] = R_ENTRANCE_L;
		}
	}
	
	//plant
	{
		plant_t *plant;
		dlist_t *p;
		
		game_get_plant_list(&p);

		while(p != NULL){
			plant = p->data;
			bmp = -1;

			if(plant->water > 0){
				if(plant->state == PLANT_STATE_SEED){
					bmp = R_PLANT_SEED;
				}
				else if(plant->state == PLANT_STATE_SEEDLING){
					bmp = R_PLANT_SEEDLING;
				}
				else if(plant->state == PLANT_STATE_YOUNG){
					bmp = R_PLANT_PLANTING;
				}
				else if(plant->state == PLANT_STATE_MATURE){
					bmp = R_PLANT_PLANTING_MATURE;
				}
			}
			else{
				if(plant->state == PLANT_STATE_SEED){
					bmp = R_PLANT_SEED;
				}
				else if(plant->state == PLANT_STATE_SEEDLING){
					bmp = R_PLANT_SEEDLING_DRY;
				}
				else if(plant->state == PLANT_STATE_YOUNG){
					bmp = R_PLANT_PLANTING_DRY;
				}
				else if(plant->state == PLANT_STATE_MATURE){
					bmp = R_PLANT_PLANTING_MATURE;
				}
			}

			if(bmp != -1){
				map[plant->y][plant->x] = bmp;
			}
			
			p = p->next;
		}
	}

	//landmine
	{
		landmine_t *landmine;
		dlist_t *p;
		
		int bmpLandmineTable[]={
			R_MINE_PT2,	//MINE_NM = 0,
			R_MINE_TL2,	//MINE_AE,
			R_MINE_LB2,	//MINE_RS,
			R_MINE_FZ2,	//MINE_AA,
			R_MINE_FT2,	//MINE_AT,
		};
		
		game_get_landmine_list(&p);

		while(p != NULL){
			landmine = p->data;

			if(MINE_RS != landmine->id){
				bmp = bmpLandmineTable[landmine->id];
			}
			else{
				if(landmine->plug == PLUG_REMOTE){
					bmp = R_MINE_LB_R2;
				}
				//else if(landmine->plug == PLUG_TIMER){
				//	bmp = R_MINE_LB_T2;
				//}
				else{
					bmp = R_MINE_LB2;
				}
			}

			map[landmine->y][landmine->x] = bmp;
			
			p = p->next;
		}
	}

	//minegun
	{
		minegun_t *minegun;
		dlist_t *p;
		
		game_get_minegun_list(&p);

		while(p != NULL){
			minegun = p->data;
			
			if(minegun->time== 0){
				bmp = R_MINEGUN_1_1+minegun->id*2;
			}
			else{
				bmp = R_MINEGUN_1_2+minegun->id*2;
			}

			map[minegun->y][minegun->x] = bmp;
			p = p->next;
		}
	}

	//enemy
	{
		enemy_t *enemy;
		dlist_t *p;
		
		game_get_enemy_list(&p);

		while(p != NULL){
			enemy = p->data;

			if(enemy->x < 0){
				break;
			}

			bmp = bmpEnemyTable[enemy->id]+enemy->direction;

			/*if(enemy->mId == ENEMY_TK){
				bmp = R_TK1+enemy.mAngle+enemy.mDirection*16;
			}
			else if(enemy->mId == ENEMY_ZJ){
				bmp = R_ZJ1+enemy.mAngle+enemy.mDirection*16;
			}
			else if(enemy->mId == ENEMY_QC){
				bmp = R_QC1+enemy.mAngle+enemy.mDirection*16;
			}*/
			
			map[enemy->y][enemy->x] = bmp;
			p = p->next;
		}
	}
	
	//house
	{
		house_t *house;
		dlist_t *p;
		
		game_get_house_list(&p);

		while(p != NULL){
			house = p->data;

			if(house->life == HOUSE_LIFE){
				bmp = R_HOUSE;
			}
			else if(house->life == 0){
				bmp = R_HOUSE_DESTORY_2;
			}
			else{
				bmp = R_HOUSE_DESTORY;
			}

			map[house->y][house->x] = bmp;
			
			p = p->next;
		}
	}

	//dead enemy
	{
		enemy_t *enemy;
		dlist_t *p;
		
		game_get_dead_enemy_list(&p);

		while(p != NULL){
			enemy = p->data;

			if(enemy->time < 3){
				bmp = bmpEnemyTable[enemy->id]+enemy->direction;
				map[enemy->y][enemy->x] = bmp;
			}
			else if((enemy->time == 3)
				||(enemy->time == 5)){
				bmp = bmpEnemyTable[enemy->id]+enemy->direction;
				map[enemy->y][enemy->x] = bmp;
			}
			
			p = p->next;
		}
	}

	//draw map, plant, landmine, minegun, enemy, house, dead enemy
	for(i = 0; i < MAP_H; i++){
		for(j = 0; j < MAP_W; j++){
			if((R_ENTRANCE_L == map[i][j])
				||(R_ENTRANCE_R == map[i][j])
				||(R_ENTRANCE_U == map[i][j])
				||(R_ENTRANCE_D == map[i][j])){
				if(mapDanger[i][j] != 0){
					bmp = R_MAP_ROAD_DANGER;
				}
				else{
					bmp = R_MAP_ROAD;
				}
				
				GL.drawImage(x0+j*L_n(L_GRID_W), y0+i*L_n(L_GRID_H), bmp);
				GL.drawImage2(x0+j*L_n(L_GRID_W), y0+i*L_n(L_GRID_H), map[i][j], 64);
			}
			else if((map[i][j] >= R_ENEMY_QC_0)
				&&(map[i][j] <= R_ENEMY_QC_3)){
				GL.drawImage(x0+j*L_n(L_GRID_W), y0+i*L_n(L_GRID_H), map[i][j]);
			}
			else if((map[i][j] >= R_ENEMY_ZJ_0)
				&&(map[i][j] <= R_ENEMY_ZJ_3)){
	            GL.drawImage(x0+j*L_n(L_GRID_W), y0+i*L_n(L_GRID_H), map[i][j]);
			}
			else if((map[i][j] >= R_ENEMY_TK_0)
				&&(map[i][j] <= R_ENEMY_TK_3)){
				GL.drawImage(x0+j*L_n(L_GRID_W), y0+i*L_n(L_GRID_H), map[i][j]);
			}
			else{
				GL.drawImage(x0+j*L_n(L_GRID_W), y0+i*L_n(L_GRID_H), map[i][j]);
			}
		}
	}

	//enemy life bar
	{
		int enemy_life[] = {
			5,	//ENEMY_SB,
			10,	//ENEMY_GB,
			15,	//ENEMY_QC,
			20,	//ENEMY_ZJ,
			40,	//ENEMY_TK,
		};
		
		dlist_t *p;
		enemy_t *enemy;
		double len = 0;
		
		game_get_enemy_list(&p);

		while(p != NULL){
			enemy = p->data;

			if(enemy->x < 0){
				break;
			}
			
			len = enemy->life*(L_n(L_GRID_W)/2)/enemy_life[enemy->id]+1;
            
            drawLifeBar(enemy->x, enemy->y, len);
			
			p = p->next;
		}
	}

	//minegun life bar
	{
		dlist_t *p;
		minegun_t *minegun;
		int len = 0;
		int life = MINEGUN_LIFE;
		
		game_get_minegun_list(&p);

		while(p != NULL){
			minegun = p->data;
			
			life = MINEGUN_LIFE+minegun->id*MINEGUN_LIFE;
			len = (int)(minegun->life*(L_n(L_GRID_W)/2)/life+1);
            
            drawLifeBar(minegun->x, minegun->y, len);
			
			p = p->next;
		}
	}
	
	//exploded landmine
	{
		landmine_t *landmine;
		dlist_t *p;
		int bmpId;

		int bmpIdTable[][3]={
			{R_EXP_0	, R_EXP_1		, R_EXP_2	 },//MINE_NM = 0,
			{R_EXP_1	, R_EXP_2		, R_EXP_3_0_0},//MINE_AE,
			{R_EXP_1	, R_EXP_2		, R_EXP_4_0_0},//MINE_RS,
			{R_EXP_1	, R_EXP_2		, R_EXP_4_0_0},//MINE_AA,
			{R_EXP_1	, R_EXP_3_0_0	, R_EXP_5_0_0},//MINE_AT,
		};
		
		game_get_exploded_mine_list(&p);

		while(p != NULL){
			landmine = p->data;

			if(landmine->time < LANDMINE_EXPLOSE_STEP){
				bmpId = bmpIdTable[landmine->id][landmine->time];

				if(bmpId < R_EXP_3_0_0){
                    GL.drawImage(x0+landmine->x*L_n(L_GRID_W), 
						landmine->y*L_n(L_GRID_H),
						bmpId);
				}
				else{
					int x1;
					int y1;

					for(i = 0; i < 3; i++){
						for(j = 0; j < 3; j++){
							x1 = landmine->x+j-1;
							y1 = landmine->y+i-1;

                            if(map_is_in_range(x1, y1)){
                                GL.drawImage(x0+x1*L_n(L_GRID_W),
									y1*L_n(L_GRID_H), bmpId+j*3+i);
							}
						}
					}
				}
			}
			
			p = p->next;
		}
	}
	
	//bullet
	{
		dlist_t *p;
		bullet_t *bullet;
		
		int bmpIdTable[][3]={
			//BULLET_BQ = 0,
			{R_EXPLOSE_0, R_EXPLOSE_1, R_EXPLOSE_2},
			//BULLET_ZJ,
			{R_EXPLOSE_1, R_EXPLOSE_2, R_EXPLOSE_4},
			//BULLET_TK,
			{R_EXPLOSE_1, R_EXPLOSE_3, R_EXPLOSE_5},
			//BULLET_MG,
			{R_EXP_1	, R_EXP_2, 	   R_EXP_4_0_0},
		};

		game_get_bullet_list(&p);
		
		while(p != NULL){
			bullet = p->data;

			if(bullet->time == 0){
				if(bullet->id != BULLET_MG){
                    GL.drawImage(x0+bullet->x-(bullet->id*4+8)/2/2, 
						bullet->y-(bullet->id*4+8)/2/2,
                    	R_BULLET_0+bullet->id);
				}
				else{
                    GL.drawImage(x0+bullet->x-(L_n(L_GRID_W)/2), 
						bullet->y-(L_n(L_GRID_W)/2),
						R_BULLET_MG_0+bullet->state);
				}
			}
			else{
				bmp = bmpIdTable[bullet->id][(bullet->time-1)%3];
				
				if(bmp < R_EXP_3_0_0){
					if(bmp >= R_EXP_0){
                        GL.drawImage(x0+((int)(bullet->x/L_n(L_GRID_W)))*L_n(L_GRID_W),
                         ((int)(bullet->y/L_n(L_GRID_H)))*L_n(L_GRID_H), bmp);
					}
					else{
                        GL.drawImage(x0+((int)(bullet->x/L_n(L_GRID_W)))*L_n(L_GRID_W),
                         ((int)(bullet->y/L_n(L_GRID_H)))*L_n(L_GRID_H), bmp);
					}
				}
				else if((bmp <= R_EXPLOSE_6)
                    &&(bmp >= R_EXPLOSE_0)){
                    GL.drawImage(x0+((int)(bullet->x/L_n(L_GRID_W)))*L_n(L_GRID_W),
                         ((int)(bullet->y/L_n(L_GRID_H)))*L_n(L_GRID_H), bmp);
                }
				else{
					int x1;
					int y1;

					for(i = 0; i < 3; i++){
						for(j = 0; j < 3; j++){
							x1 = (int)(bullet->x/L_n(L_GRID_W)+j-1);
							y1 = (int)(bullet->y/L_n(L_GRID_H)+i-1);

                            if(map_is_in_range(x1, y1)){
                                GL.drawImage(x0+x1*L_n(L_GRID_W), y1*L_n(L_GRID_H),
									bmp+j*3+i);
							}
						}
					}
				}
			}
			
			p = p->next;
		}
	}
	
	if(operateMode == OPERATE_MODE_POS_SELECT){
        GL.drawImage(x0+cursorPos.x*L_n(L_GRID_W), 
			cursorPos.y*L_n(L_GRID_H), R_BTN_CURSOR);
	}
	else if(operateMode == OPERATE_MODE_AIM){
		for(i = 0; i < 7; i++){
			for(j = 0; j < 7; j++){
				int x = cursorPos.x+j-MINEGUN_GUNSHOT;
				int y = cursorPos.y+i-MINEGUN_GUNSHOT;
				
                if(minegun_is_in_gunshot(operatePos.x, operatePos.y, x, y)
                	&&(map_is_in_range(x, y))){
                	GL.drawRect(x0+x*L_n(L_GRID_W),y*L_n(L_GRID_H),
                    	x0+x*L_n(L_GRID_W)+L_n(L_GRID_W),
                    	y*L_n(L_GRID_H)+L_n(L_GRID_H),
                    	C.RGBA(255, 0, 0, 96));
				}
			}
		}
		
        GL.drawImage(x0+operatePos.x*L_n(L_GRID_W),
			operatePos.y*L_n(L_GRID_H), R_BTN_CURSOR);
	}
	else{
		int operate[OPERATE_MAX];
		int total = 0;
		
		int bmpOperateTable[]={
			R_MINE_PT			,//OPERATE_PT = 0,
			R_MINE_TL			,//OPERATE_TL,
			R_MINE_LB			,//OPERATE_LB,
			R_MINE_FZ			,//OPERATE_FZ,
			R_MINE_FT			,//OPERATE_FT,
			R_TOOL_SHOVEL		,//OPERATE_DIG,
			R_TOOL_REMOTE		,//OPERATE_REMOTE,
			R_TOOL_REMOTE		,//OPERATE_TIMER,
			R_TOOL_SEED			,//OPERATE_PLANT,
			R_TOOL_SEED			,//OPERATE_WATERING,
			R_TOOL_KNIFE		,//OPERATE_HARVEST,
			R_TOOL_EXPLOSE		,//OPERATE_EXPLOSE,
			R_MINEGUN			,//OPERATE_MINEGUN,
			R_TOOL_AIM			,//OPERATE_FIRE,
		};

		int x1;
		int y1;
		
        GL.drawImage(x0+cursorPos.x*L_n(L_GRID_W), cursorPos.y*L_n(L_GRID_H), R_BTN_CURSOR);
		
        total = getOperationList(operate);

		if(cursorPos.x-total >= 0){
			x1 = cursorPos.x-total;

			if((cursorPos.y+1) < MAP_H){
				y1 = cursorPos.y+1;
			}
			else{
				y1 = cursorPos.y-1;
			}
		}
		else{
			x1 = cursorPos.x+1;

			if((cursorPos.y+1) < MAP_H){
				y1 = cursorPos.y+1;
			}
			else{
				y1 = cursorPos.y-1;
			}
		}
		
		for(i = 0; i < total; i++){
            GL.drawImage(x0+x1*L_n(L_GRID_W)+i*L_n(L_GRID_W),
            	y1*L_n(L_GRID_H), bmpOperateTable[operate[i]]);
		}
	}

	//money
	money = game_get_money();
	//GL.drawImage([L n:L.COIN_X), [L n:L.TBAR_Y), R_COIN);
    num_x0 = (int)((L_n(L_GRID_W)*2-L_n(L_GRID_W)/10)/2);
    drawNumberC(num_x0, (int)(L_n(L_GRID_H)*25/16),
		money, C.RGBA(255, 255, 255, 255));

	//score
	{
		int total = game_get_enemy_total();
		int killed = game_get_enemy_killed();
		char strTmp[32];
        sprintf(strTmp, "%d/%d" , killed, total);
        drawNumberCS(num_x0, (int)(L_n(L_GRID_H)*111/16),
			strTmp, C.RGBA(255, 255, 255, 255));
	}

	//play mode
	if(_self->gameMode == GAME_MODE_PLAY){
		//if(speed == 0){
            GL.drawImage(L_n(L_TB_ICON_X), L_n(L_BTN_PLAY_Y), R_BTN_PLAY);
		//}
		//else{
        //    GL.drawImage(L_n(L_TB_ICON_X) :L_n(L_BTN_PLAY_Y) :R_PLAY_X2];
		//}
	}
	else if(_self->gameMode == GAME_MODE_PAUSE){
        GL.drawImage(L_n(L_TB_ICON_X), L_n(L_BTN_PLAY_Y), R_BTN_PAUSE);

		//back confirm menu
		if(_self->backConfirm){
			int offsetY = (int)(2*L_n(L_GRID_H)+L_n(L_GRID_H)/2);
            
            GL.drawRectFill(x0+4*L_n(L_GRID_W), offsetY, x0+10*L_n(L_GRID_W), offsetY+L_n(L_GRID_H)*4, C.RGB(0, 0, 255));

            GL.drawRectFill(6*L_n(L_GRID_W)+L_n(L_GRID_W)/3, offsetY+0*L_n(L_GRID_H)+L_n(L_GRID_H)/3, 12*L_n(L_GRID_W)-L_n(L_GRID_W)/3, offsetY+1*L_n(L_GRID_H)+L_n(L_GRID_H)/3, C.RGB(0, 0, 128));
            GL.drawRectFill(6*L_n(L_GRID_W)+L_n(L_GRID_W)/3, offsetY+1*L_n(L_GRID_H)+L_n(L_GRID_H)/2, 12*L_n(L_GRID_W)-L_n(L_GRID_W)/3, offsetY+2*L_n(L_GRID_H)+L_n(L_GRID_H)/2, C.RGB(0, 0, 128));
            GL.drawRectFill(6*L_n(L_GRID_W)+L_n(L_GRID_W)/3, offsetY+2*L_n(L_GRID_H)+L_n(L_GRID_H)*2/3, 12*L_n(L_GRID_W)-L_n(L_GRID_W)/3, offsetY+3*L_n(L_GRID_H)+L_n(L_GRID_H)*2/3, C.RGB(0, 0, 128));
			
            GL.drawImage(6*L_n(L_GRID_W)+L_n(L_GRID_W)/2, offsetY+0*L_n(L_GRID_H)+L_n(L_GRID_H)/3,
				R_BTN_MENU);
            GL.drawImage(6*L_n(L_GRID_W)+L_n(L_GRID_W)/2, offsetY+1*L_n(L_GRID_H)+L_n(L_GRID_H)/2,
				R_BTN_REPLAY);
            GL.drawImage(6*L_n(L_GRID_W)+L_n(L_GRID_W)/2, offsetY+2*L_n(L_GRID_H)+L_n(L_GRID_H)*2/3,
				R_BTN_PLAY);

            GL.drawText(x0+L_n(L_GRID_W)*17/3, offsetY+L_n(L_GRID_H)*0+L_n(L_GRID_H)/3+L_n(L_GRID_H)/10, "Back to map");
            GL.drawText(x0+L_n(L_GRID_W)*17/3, offsetY+L_n(L_GRID_H)*1+L_n(L_GRID_H)/2+L_n(L_GRID_H)/10, "Replay");
            GL.drawText(x0+L_n(L_GRID_W)*17/3, offsetY+L_n(L_GRID_H)*2+L_n(L_GRID_H)*2/3+L_n(L_GRID_H)/10, "Continue");
		}
	}
	else{
		int offsetY = (int)(2*L_n(L_GRID_H));
		int offsetYScore = (int)(offsetY+L_n(L_GRID_H)/5);
		int offsetYText = (int)(offsetY+3*L_n(L_GRID_H)+L_n(L_GRID_H)/10);
		
        GL.drawImage(L_n(L_TB_ICON_X), L_n(L_BTN_PLAY_Y), R_BTN_STOP);
        GL.drawRectFill(x0+4*L_n(L_GRID_W), offsetY, x0+10*L_n(L_GRID_W), offsetY+L_n(L_GRID_H)*5, C.RGB(0, 0, 255));
		
		if(game_get_over_flag()== OVER_WIN){
			int starBmp[3];
			
            GL.drawTextC(x0+L_n(L_GRID_W)*7, offsetYText, "LEVEL CLEARED!");

			starBmp[0] = R_STAR_LANDMINE;
			
			if(game_is_plants_star()){
				starBmp[1] = R_STAR_PLANT;
			}
			else{
				starBmp[1] = R_STAR_EMPTY;
			}

			if(game_is_all_house_ok()){
				starBmp[2] = R_STAR_HOUSE;
			}
			else{
				starBmp[2] = R_STAR_EMPTY;
			}

			for(i = 0; i < 3; i++){
                GL.drawImage(x0+4*L_n(L_GRID_W)+i*L_n(L_GRID_W)*2, offsetY+L_n(L_GRID_H), starBmp[i]);
			}
		}
		else{
            GL.drawTextC(x0+L_n(L_GRID_W)*7, offsetYText, "LEVEL FAILED!");
			GL.drawImage(7*L_n(L_GRID_W), offsetY+L_n(L_GRID_H), R_HOUSE_DESTORY_BIG);
			GL.drawImage(9*L_n(L_GRID_W), offsetY+L_n(L_GRID_H), R_HOUSE_DESTORY_BIG);
		}

        GL.drawImage(x0+4*L_n(L_GRID_W), offsetY, R_ICON_DING);
        GL.drawImage(x0+9*L_n(L_GRID_W), offsetY, R_ICON_DING);
	
        if(getMenuMode(_self) == MENU_MODE_WIN){
            int keyBmpId[]={
                R_BTN_MENU,
                R_BTN_REPLAY,
                R_BTN_NEXT
            };

            for(i = 0; i < 3; i++){
                GL.drawImage(x0+4*L_n(L_GRID_W)+i*2*L_n(L_GRID_W)+L_n(L_GRID_W)/2,
					offsetY+4*L_n(L_GRID_H)+1,
                    keyBmpId[i]);
            }

			drawNumberC((int)(x0+L_n(L_GRID_W)*7), offsetYScore,
				game_get_score(), C.RGBA(255, 255, 255, 255));
		
            GL.drawRect(x0+4*L_n(L_GRID_W), offsetY+L_n(L_GRID_H)-1.5, x0+10*L_n(L_GRID_W), offsetY+L_n(L_GRID_H), C.RGB(0, 255, 0));
            GL.drawRect(x0+4*L_n(L_GRID_W), offsetY+3*L_n(L_GRID_H)-1.5, x0+10*L_n(L_GRID_W), offsetY+3*L_n(L_GRID_H), C.RGB(0, 255, 0));
            GL.drawRect(x0+4*L_n(L_GRID_W), offsetY+4*L_n(L_GRID_H)-1.5, x0+10*L_n(L_GRID_W), offsetY+4*L_n(L_GRID_H), C.RGB(0, 255, 0));
            GL.drawRect(x0+6*L_n(L_GRID_W), offsetY+4*L_n(L_GRID_H), x0+6*L_n(L_GRID_W)+1.5, offsetY+5*L_n(L_GRID_H), C.RGB(0, 255, 0));
            GL.drawRect(x0+8*L_n(L_GRID_W), offsetY+4*L_n(L_GRID_H), x0+8*L_n(L_GRID_W)+1.5, offsetY+5*L_n(L_GRID_H), C.RGB(0, 255, 0));
        }
        else{
            int keyBmpId[]={
                R_BTN_MENU,
                R_BTN_REPLAY
            };

            for(i = 0; i < 2; i++){
                GL.drawImage(x0+4*L_n(L_GRID_W)+i*3*L_n(L_GRID_W)+L_n(L_GRID_W), offsetY+4*L_n(L_GRID_H)+1, keyBmpId[i]);
            }

            drawNumberC((int)(x0+L_n(L_GRID_W)*7), offsetYScore,
					game_get_score(), C.RGBA(255, 255, 255, 255));
		
            GL.drawRect(x0+4*L_n(L_GRID_W), offsetY+L_n(L_GRID_H)-1.5, x0+10*L_n(L_GRID_W), offsetY+L_n(L_GRID_H), C.RGB(0, 255, 0));
            GL.drawRect(x0+4*L_n(L_GRID_W), offsetY+3*L_n(L_GRID_H)-1.5, x0+10*L_n(L_GRID_W), offsetY+3*L_n(L_GRID_H), C.RGB(0, 255, 0));
            GL.drawRect(x0+4*L_n(L_GRID_W), offsetY+4*L_n(L_GRID_H)-1.5, x0+10*L_n(L_GRID_W), offsetY+4*L_n(L_GRID_H), C.RGB(0, 255, 0));
            GL.drawRect(x0+7*L_n(L_GRID_W), offsetY+4*L_n(L_GRID_H), x0+7*L_n(L_GRID_W)+1.5, offsetY+5*L_n(L_GRID_H), C.RGB(0, 255, 0));
        }
    }
}

static void procEvent(VGame_t *_self)
{
    int x0;
	int y0;
	
	if(IS_EVENT(EV_KEY_UP, CTRL_BTN_MENU)){
		_self->super.setTransfer(&_self->super, -1,
				TRANS_RETURN, 0, 0, 0, 0);
	}
	else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_MENU2)){
        _self->super.setTransfer(&_self->super, -1,
				TRANS_RETURN, 0, 0, 0, 0);
	}
	else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_REPLAY)){
        game_start(_self->mapIndex);
        playPrepare(_self);
	}
	else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_REPLAY2)){
		game_start(_self->mapIndex);
        playPrepare(_self);
	}
	else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_NEXT)){
		_self->mapIndex++;

		if(_self->mapIndex >= MAP_TOTAL){
			_self->mapIndex = 0;
		}
        
        game_start(_self->mapIndex);
        playPrepare(_self);
	}
	else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_PLAY)){
		if(_self->gameMode == GAME_MODE_PLAY){
			if(speed == 0){
				_self->gameMode = GAME_MODE_PAUSE;
			}
			else{
				_self->gameMode = GAME_MODE_PAUSE;
				speed = 0;
			}
		}
		else if(_self->gameMode == GAME_MODE_PAUSE){
			_self->gameMode = GAME_MODE_PLAY;
		}
		else if(_self->gameMode == GAME_MODE_OVER){
			_self->gameMode = GAME_MODE_PLAY;
			playPrepare(_self);
		}
	}
	else if(IS_EVENT(EV_MTX_UP, CTRL_MTX_TB)){
        
        int last_item = _self->tbarItem;
        _self->tbarItem = _self->tbarType*4+_self->super.super.mMsg->p2;
	}
	else if(IS_EVENT(EV_MTX_UP, CTRL_MTX)){
		if(_self->gameMode == GAME_MODE_PLAY){
			x0 = _self->super.super.mMsg->p1;
			y0 = _self->super.super.mMsg->p2;
			
			if(operateMode == OPERATE_MODE_POS_SELECT)
			{
				cursorPos.x = x0;
				cursorPos.y = y0;
				operatePos.x = x0;
				operatePos.y = y0;
			}
			else if(operateMode == OPERATE_MODE_OPERATING_SELECT){
				getMenuPos();
                
                if(! updateOperateIndex(x0, y0)){
					operateMode = OPERATE_MODE_POS_SELECT;
                    cursorPos.x = x0;
                    cursorPos.y = y0;
                    operatePos.x = x0;
                    operatePos.y = y0;
				}
			}
			else{
				cursorPos.x = x0;
				cursorPos.y = y0;
			}

			fieldTouchOff(_self);
		}
	}
	else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_RETURN)){
		backConfirm(_self);
	}
	else if(IS_EVENT(EV_KEY_UP, CTRL_BK_MENU)){
		_self->super.setTransfer(&_self->super, -1,
				TRANS_RETURN, 0, 0, 0, 0);
	}
	else if(IS_EVENT(EV_KEY_UP, CTRL_BK_REPLAY)){
		game_start(_self->mapIndex);
        playPrepare(_self);
	}
	else if(IS_EVENT(EV_KEY_UP, CTRL_BK_CONTINUE)){
		backCancel(_self);
		//if([Game getResumeFlag]){
        //    [Game backup:false];
        //    [Game saveBak];
		//}
	}
}

static bool sendEvent(VGame_t *_self, Msg_t *msg0)
{
	if(msg0->event == EV_TIME_TICK){
		if(_self->gameMode == GAME_MODE_PLAY){
			game_tick();
		}

		if(game_get_over_flag() != OVER_NONE){
			if(_self->gameMode == GAME_MODE_PLAY){
                 record_save();
				 gameOver(_self);
			}
		}
	}
	else if(msg0->event == EV_PAUSE){
		backConfirm(_self);
	}
    else if(msg0->event == EV_RESUME){
        _self->super.mRefreshFlag = true;
    }

	return true;
}

static int getOperationList(int operate[])
{
	int i;

	for(i = 0; i < operateTableLength[operateObj]; i++){
		operate[i] = operateTable[operateObj][i];
	}

	return operateTableLength[operateObj];
}

static void getMenuPos(void)
{
	int total;
	int x0;
	int y0;
	int operate[OPERATE_MAX];
	int i;
	
    total = getOperationList(operate);
    
	if((cursorPos.x-total) >= 0){
		x0 = cursorPos.x-total;

		if((cursorPos.y+1) < MAP_H){
			y0 = cursorPos.y+1;
		}
		else{
			y0 = cursorPos.y-1;
		}
	}
	else{
		x0 = cursorPos.x+1;

		if((cursorPos.y+1) < MAP_H){
			y0 = cursorPos.y+1;
		}
		else{
			y0 = cursorPos.y-1;
		}
	}

	for(i = 0; i < operateTableLength[operateObj]; i++){
		menuPos[i].x = x0+i;
		menuPos[i].y = y0;
	}
    
    menuLen = operateTableLength[operateObj];
}

static bool updateOperateIndex(int x0, int y0)
{
	bool ret = false;
	int i;

	operateIndex = -1;
	
	for(i = 0; i < menuLen; i++){
		if((menuPos[i].x == x0)
			&&(menuPos[i].y == y0)){
			operateIndex = i;
			ret = true;
			break;
		}
	}

	return ret;
}

static void gameOver(VGame_t *_self)
{
	_LOGD(TAG, "gameOver\n");
	
	_self->gameMode = GAME_MODE_OVER;

	if(getMenuMode(_self) == MENU_MODE_WIN){
		WIDGET_SHOW(CTRL_BTN_MENU);
		WIDGET_SHOW(CTRL_BTN_REPLAY);
		WIDGET_SHOW(CTRL_BTN_NEXT);
	}
	else{
		WIDGET_SHOW(CTRL_BTN_MENU2);
		WIDGET_SHOW(CTRL_BTN_REPLAY2);
	}
	
	WIDGET_HIDE(CTRL_MTX);
	WIDGET_HIDE(CTRL_BTN_RETURN);
	WIDGET_HIDE(CTRL_MTX_TB);
	WIDGET_HIDE(CTRL_BK_MENU);
	WIDGET_HIDE(CTRL_BK_REPLAY);
	WIDGET_HIDE(CTRL_BK_CONTINUE);
}

static void backConfirm(VGame_t *_self)
{
	_LOGD(TAG, "backConfirm\n");
	
	if(_self->gameMode != GAME_MODE_OVER){
		_self->backConfirm = true;
		_self->gameMode = GAME_MODE_PAUSE;
		WIDGET_HIDE(CTRL_BTN_MENU);
		WIDGET_HIDE(CTRL_BTN_REPLAY);
		WIDGET_HIDE(CTRL_BTN_NEXT);
		WIDGET_HIDE(CTRL_MTX);
		WIDGET_HIDE(CTRL_BTN_PLAY);
		WIDGET_HIDE(CTRL_BTN_RETURN);
		WIDGET_HIDE(CTRL_MTX_TB);
		WIDGET_SHOW(CTRL_BK_MENU);
		WIDGET_SHOW(CTRL_BK_REPLAY);
		WIDGET_SHOW(CTRL_BK_CONTINUE);
		WIDGET_HIDE(CTRL_BTN_MENU2);
		WIDGET_HIDE(CTRL_BTN_REPLAY2);
	}
}

static void backCancel(VGame_t *_self)
{
	_LOGD(TAG, "backCancel\n");
	
	if(_self->gameMode != GAME_MODE_OVER){
		_self->backConfirm = false;
		_self->gameMode = GAME_MODE_PLAY;
		WIDGET_HIDE(CTRL_BTN_MENU);
		WIDGET_HIDE(CTRL_BTN_REPLAY);
		WIDGET_HIDE(CTRL_BTN_NEXT);
		WIDGET_SHOW(CTRL_MTX);
		WIDGET_SHOW(CTRL_BTN_PLAY);
		WIDGET_SHOW(CTRL_BTN_RETURN);
		WIDGET_SHOW(CTRL_MTX_TB);
		WIDGET_HIDE(CTRL_BK_MENU);
		WIDGET_HIDE(CTRL_BK_REPLAY);
		WIDGET_HIDE(CTRL_BK_CONTINUE);
		WIDGET_HIDE(CTRL_BTN_MENU2);
		WIDGET_HIDE(CTRL_BTN_REPLAY2);
	}
}

static void playPrepare(VGame_t *_self)
{
	_LOGD(TAG, "playPrepare\n");
	
	_self->gameMode = GAME_MODE_PLAY;
	operateMode = OPERATE_MODE_POS_SELECT;
	operatePos.x = MAP_W/2;
	operatePos.y = MAP_H/2;
	cursorPos.x = MAP_W/2;
	cursorPos.y = MAP_H/2;
	speed = 0;
	_self->tbarType = TBAR_ROAD;
	_self->tbarItem = TBAR_ID_TL;
	_self->backConfirm = false;
	
	WIDGET_HIDE(CTRL_BTN_MENU);
	WIDGET_HIDE(CTRL_BTN_REPLAY);
	WIDGET_HIDE(CTRL_BTN_NEXT);
	WIDGET_SHOW(CTRL_MTX);
	WIDGET_SHOW(CTRL_BTN_PLAY);
	WIDGET_SHOW(CTRL_BTN_RETURN);
	WIDGET_SHOW(CTRL_MTX_TB);
	WIDGET_HIDE(CTRL_BK_MENU);
	WIDGET_HIDE(CTRL_BK_REPLAY);
	WIDGET_HIDE(CTRL_BK_CONTINUE);
	WIDGET_HIDE(CTRL_BTN_MENU2);
	WIDGET_HIDE(CTRL_BTN_REPLAY2);
}

static void fieldTouchOff(VGame_t *_self)
{
	_LOGD(TAG, "fieldTouchOff, operateMode=%d\n", operateMode);
	
	if(operateMode == OPERATE_MODE_POS_SELECT){
        int object = game_get_object(operatePos.x, operatePos.y);
		_LOGD(TAG, "operateObj=%d\n", object);
		
		if(object != OPER_OBJ_NONE){
			operateMode = OPERATE_MODE_OPERATING_SELECT;
			operateIndex = 0;
			operateObj = object;

			if(operateObj == OPER_OBJ_ROAD){
				if(_self->tbarType == TBAR_ROAD){
					int mine_id[]={
						MINE_AE,
						MINE_NM,
						MINE_AA,
						MINE_AT
					};
					
                    game_add_landmine(operatePos.x, operatePos.y,
						mine_id[_self->tbarItem]);

					operateMode = OPERATE_MODE_POS_SELECT;
				}
				else{
					_self->tbarType = TBAR_ROAD;
					_self->tbarItem = TBAR_ID_TL;
				}
			}
			else if(operateObj == OPER_OBJ_LAND){
				if(_self->tbarType == TBAR_OTHER){
					if(_self->tbarItem == TBAR_ID_SEED){
                        game_add_plant(operatePos.x, operatePos.y);
						operateMode = OPERATE_MODE_POS_SELECT;
					}
					else if(_self->tbarItem == TBAR_ID_MG){
						game_add_minegun(operatePos.x, operatePos.y);
						operateMode = OPERATE_MODE_POS_SELECT;
					}
				}
				else{
					_self->tbarType = TBAR_OTHER;
					_self->tbarItem = TBAR_ID_SEED;
				}
			}
			else if(operateObj == OPER_OBJ_FOREST){
				if(_self->tbarType == TBAR_OTHER){
					if(_self->tbarItem == TBAR_ID_MG){
						game_add_minegun(operatePos.x, operatePos.y);
						operateMode = OPERATE_MODE_POS_SELECT;
					}
				}
				else{
					_self->tbarType = TBAR_OTHER;
					_self->tbarItem = TBAR_ID_MG;
				}
			}
			else if(operateObj == OPER_OBJ_ROAD_SIDE){
				if(_self->tbarType == TBAR_OTHER){
					if(_self->tbarItem == TBAR_ID_SEED){
						game_add_plant(operatePos.x, operatePos.y);
					}
					else if(_self->tbarItem == TBAR_ID_LB){
                        game_add_landmine(operatePos.x, operatePos.y,
							MINE_RS);
					}
					else if(_self->tbarItem == TBAR_ID_MG){
						game_add_minegun(operatePos.x, operatePos.y);
					}

					operateMode = OPERATE_MODE_POS_SELECT;
				}
				else{
					_self->tbarType = TBAR_OTHER;
					_self->tbarItem = TBAR_ID_SEED;
				}
			}
			else if(operateObj == OPER_OBJ_PLANT_MATURE){
				//||(operateObj == OPER_OBJ_PLANT)){
                game_harvest_plant(operatePos.x, operatePos.y);
				operateMode = OPERATE_MODE_POS_SELECT;
			}
			else if(operateObj == OPER_OBJ_PLANT){
				if(_self->tbarItem == TBAR_ID_KNIFE){
					game_harvest_plant(operatePos.x, operatePos.y);
				}
				else{
					game_watering_plant(operatePos.x, operatePos.y);
					_self->tbarType = TBAR_OTHER;
					_self->tbarItem = TBAR_ID_SEED;
				}
				
				operateMode = OPERATE_MODE_POS_SELECT;
			}
		}
	}
	else if(operateMode == OPERATE_MODE_OPERATING_SELECT){
		int x0 = operatePos.x;
		int y0 = operatePos.y;
		int obj = operateObj;
		int index = operateIndex;
		
		_LOGD(TAG, "operatePos.x=%d, operatePos.y=%d, operateObj=%d, operateIndex=%d\n", 
			operatePos.x, operatePos.y, operateObj, operateIndex);
		operateMode = OPERATE_MODE_POS_SELECT;

		if(operateIndex == -1){
			return;
		}
		
		if(operateTable[obj][index] == OPERATE_DIG){
			if((obj == OPER_OBJ_MINE)
				||(obj == OPER_OBJ_MINE_LB)
				||(obj == OPER_OBJ_MINE_REMOTE)
				||(obj == OPER_OBJ_MINE_REMOTE2)
				||(obj == OPER_OBJ_MINE_TIMER)){
				game_dig_landmine(x0, y0);
			}
			else if((obj == OPER_OBJ_MINEGUN)
				||(obj == OPER_OBJ_MINEGUN_NO_FIRE)){
				game_dig_minegun(x0, y0);
			}
		}
		else if(operateTable[obj][index] == OPERATE_HARVEST){
			game_harvest_plant(x0, y0);
		}
		else if(operateTable[obj][index] == OPERATE_TIMER){
			game_add_plug(x0, y0, PLUG_TIMER);
		}
		else if(operateTable[obj][index] == OPERATE_REMOTE){
            game_add_plug(x0, y0, PLUG_REMOTE);
		}
		else if(operateTable[obj][index] == OPERATE_PLANT){
			game_add_plant(x0, y0);
			_self->tbarType = TBAR_OTHER;
			_self->tbarItem = TBAR_ID_SEED;
		}
		else if(operateTable[obj][index] == OPERATE_WATERING){
			game_watering_plant(x0, y0);
		}
		else if(operateTable[obj][index] == OPERATE_EXPLOSE){
			game_explose_landmine(x0, y0);
		}
		else if(operateTable[obj][index] == OPERATE_MINEGUN){
			game_add_minegun(x0, y0);
			_self->tbarType = TBAR_OTHER;
			_self->tbarItem = TBAR_ID_MG;
		}
		else if(operateTable[obj][index] == OPERATE_FIRE){
			operateMode = OPERATE_MODE_AIM;
			aimPos.x = x0;
			aimPos.y = y0;
		}
		else{
            game_add_landmine(x0, y0, operateTable[obj][index]);

			_self->tbarType = TBAR_ROAD;

			if(operateTable[obj][index] == OPERATE_PT){
				_self->tbarItem = TBAR_ID_PT;
			}
			else if(operateTable[obj][index] == OPERATE_TL){
				_self->tbarItem = TBAR_ID_TL;
			}
			else if(operateTable[obj][index] == OPERATE_FZ){
				_self->tbarItem = TBAR_ID_FZ;
			}
			else if(operateTable[obj][index] == OPERATE_FT){
				_self->tbarItem = TBAR_ID_FT;
			}
			else if(operateTable[obj][index] == OPERATE_LB){
				_self->tbarType = TBAR_OTHER;
				_self->tbarItem = TBAR_ID_LB;
			}
		}
	}
	else if(operateMode == OPERATE_MODE_AIM){
        int object = game_get_object(operatePos.x, operatePos.y);

		_LOGD(TAG, "object=%d\n", object);
		
		if(object == OPER_OBJ_MINEGUN){
            if(minegun_is_in_gunshot(
                operatePos.x,
                operatePos.y,
                cursorPos.x,
				cursorPos.y)){
				aimPos.x = cursorPos.x;
				aimPos.y = cursorPos.y;
				
                game_minegun_fire(
					operatePos.x, operatePos.y,
					cursorPos.x, cursorPos.y
				);
			}
		}

		operateMode = OPERATE_MODE_POS_SELECT;
	}
}

static int getMenuMode(VGame_t *_self)
{
    int ret = MENU_MODE_NONE;
    
    if(_self->gameMode == GAME_MODE_OVER){
        if(game_get_over_flag() == OVER_WIN){
            ret = MENU_MODE_WIN;
        }
        else{
            ret = MENU_MODE_LOSE;
        }
    }
    
    return ret;
}

static void drawNumberC(int x0, int y0, int n, int color)
{
	char tmpStr[16];
	sprintf(tmpStr, "%d" , n); 
    drawNumberCS(x0, y0, tmpStr, color);
}

static void drawNumberCS(int x0, int y0, const char *tmp, int color)
{
    int i = 0;
	int len = strlen(tmp);
    
    while(i < len){
        if(tmp[i] == '-'){
            GL.drawImage(x0+i*L_n(L_NUMBER_W)-len*L_n(L_NUMBER_W)/2,
				y0, R_N_0+(R_N_S-R_N_0));
        }
        else if(tmp[i] == '/'){
            GL.drawImage(x0+i*L_n(L_NUMBER_W)-len*L_n(L_NUMBER_W)/2,
				y0, R_N_0+(R_N_D-R_N_0));
        }
        else{
            GL.drawImage(x0+i*L_n(L_NUMBER_W)-len*L_n(L_NUMBER_W)/2,
				y0, R_N_0+tmp[i]-0x30);
        }
        
        i++;
    }
}

static void drawLifeBar(int x0, int y0, double len)
{
    int x1 = (int)(L_x(L_PLAY_MTX_X)+x0*L_n(L_GRID_W)+L_n(L_GRID_W)/4);
    int y1 = (int)(L_y(L_PLAY_MTX_Y));
    
    GL.drawRectFill(x1, y1+y0*L_n(L_GRID_H)+L_n(L_GRID_H)-1,
		x1+L_n(L_GRID_W)/2, y1+y0*L_n(L_GRID_H)+L_n(L_GRID_H)+1, C.RGBA(255, 255, 255, 255));
    GL.drawRectFill(x1, y1+y0*L_n(L_GRID_H)+L_n(L_GRID_H)-1,
		x1+len, y1+y0*L_n(L_GRID_H)+L_n(L_GRID_H)+1, C.RGBA(255, 0, 0, 255));
}

void VGame_initWith(VGame_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0)
{
    View_initWith(&_self->super, vid0, x0, y0, w0, h0, msg0);
	View_init(&_self->super_f);
	
    _self->gameMode = GAME_MODE_PLAY;
    _self->mapIndex = 0;
    _self->tbarType = TBAR_ROAD;
    _self->tbarItem = TBAR_ID_TL;
    _self->backConfirm = false;
    _self->backupFlag = false;
    _self->tick = 0;
    
    _self->super.onCreate = onCreate;
	_self->super.onDraw = onDraw;
	_self->super.onEnter = onEnter;
	_self->super.onExit = onExit;
	_self->super.procEvent = procEvent;
	_self->super.sendEvent = sendEvent;
	
	_self->onCreate = onCreate;
	_self->onDraw = onDraw;
	_self->onEnter = onEnter;
	_self->onExit = onExit;
	_self->procEvent = procEvent;
	_self->sendEvent = sendEvent;
}

